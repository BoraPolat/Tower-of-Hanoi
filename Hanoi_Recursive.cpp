#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// n is set at runtime via user input; arrays are allocated dynamically afterwards.
// tower_size = n + 1, the extra slot holds the sentinel value (999).
int n, tower_size, move_count;
int *A, *B, *C;

// Global log file: opened once in main(), written alongside every cout.
ofstream log_file;

// Writes a line to both the terminal and the log file.
void print(const string& line) {
    cout    << line << "\n";
    log_file << line << "\n";
}

// Allocates towers of size tower_size and fills them:
// A gets disks 1..n, B and C are marked empty (-1).
// A sentinel value of 999 is placed at index n to act as a boundary guard.
void initialization() {
    tower_size = n + 1;
    A = new int[tower_size];
    B = new int[tower_size];
    C = new int[tower_size];

    print("Initialization is being done...");
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
        B[i] = -1;
        C[i] = -1;
    }
    A[n] = 999; // Sentinel
    B[n] = 999;
    C[n] = 999;
}

// Verifies that each tower remains sorted (smaller disks on top).
// Returns 1 if all towers are valid, 0 if a violation is found.
int check() {
    for (int i = 0; i < n; i++) {
        if (A[i] > A[i + 1] && A[i + 1] != -1) {
            print("!!! Hanoi rule violated.");
            return 0;
        }
        if (B[i] > B[i + 1] && B[i + 1] != -1) {
            print("!!! Hanoi rule violated.");
            return 0;
        }
        if (C[i] > C[i + 1] && C[i + 1] != -1) {
            print("!!! Hanoi rule violated.");
            return 0;
        }
    }
    return 1;
}

// Prints the current state of all three towers side by side.
// Empty slots are shown as "|   |" and occupied slots show the disk number.
void display() {
    print("  A             B             C  ");
    for (int i = 0; i < n; i++) {
        string row = "";

        row += (A[i] == -1) ? "|   |" : "| " + to_string(A[i]) + " |";
        row += "         ";
        row += (B[i] == -1) ? "|   |" : "| " + to_string(B[i]) + " |";
        row += "         ";
        row += (C[i] == -1) ? "|   |" : "| " + to_string(C[i]) + " |";

        print(row);
    }
    print("---------------------------------");
}

// Resolves the pointer address of src/dest to a human-readable tower label
// and prints the move in "X --> Y" format.
void naming(int src[], int dest[]) {
    char src_name  = '?';
    char dest_name = '?';

    if      (src  == A) src_name  = 'A';
    else if (src  == B) src_name  = 'B';
    else if (src  == C) src_name  = 'C';

    if      (dest == A) dest_name = 'A';
    else if (dest == B) dest_name = 'B';
    else if (dest == C) dest_name = 'C';

    string move = "";
    move += src_name;
    move += " --> ";
    move += dest_name;
    print(move);
}

// Moves the top disk from src to dest.
// Finds the lowest free slot in dest, then removes the first disk from src.
// Calls check() after every move to validate tower ordering.
void pop_and_push(int src[], int dest[]) {
    naming(src, dest);
    if (src == dest) return;

    int available = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (dest[i] == -1) {
            available = i;
            break;
        }
    }
    if (available == -1) return; // Destination tower is full

    for (int i = 0; i < n; i++) {
        if (src[i] != -1) {
            dest[available] = src[i];
            src[i] = -1;
            break;
        }
    }
    check();
}

// Returns the value of the topmost disk on a tower.
// Returns 999 if the tower is empty, meaning any disk may be placed on it.
int get_top(int arr[]) {
    for (int i = 0; i < n; i++) {
        if (arr[i] != -1) return arr[i];
    }
    return 999;
}

// Iterative Tower of Hanoi using the standard cyclic move pattern.
// For odd n  the cycle order is A<->C, A<->B, B<->C (disks end on C).
// For even n the cycle order is A<->B, A<->C, B<->C (disks end on C).

void hanoi(int disks, int src[], int dest[], int aux[]) {
    if (disks == 0) return;

    hanoi(disks - 1, src, aux, dest);   // move n-1 disks to auxiliary
    pop_and_push(src, dest);             // move the largest disk to destination
    display();
    hanoi(disks - 1, aux, dest, src);   // move n-1 disks on top of destination
}

int main() {
    // Prompt the user for the number of disks before anything else runs.
    cout << "Enter the number of disks: ";
    cin >> n;

    // Open log file in truncate mode so each run starts with a clean file.
    log_file.open("hanoi_recursive_output.txt", ios::trunc);

    initialization();
    display();
    
    hanoi(n, A, C, B);
    move_count = pow(2, n) - 1;
    print("Hanoi is solved! Total Moves: " + to_string(move_count));

    log_file.close();

    // Release dynamically allocated memory.
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}