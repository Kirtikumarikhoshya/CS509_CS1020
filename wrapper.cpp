#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Main navigation menu
static void displayMainMenu() {
    cout << "\n==================================================\n";
    cout << "           PG SOFTWARE LAB - MAIN WRAPPER         \n";
    cout << "==================================================\n";
    cout << " 1. Assignment 01: GEMM & Graph Representation (CSR)\n";
    cout << " 2. Assignment 02: Shortest Paths (Bellman-Ford & Floyd-Warshall)\n";
    cout << " 3. Assignment 03: Minimum Spanning Tree (Kruskal & Prim)\n";
    cout << " 4. Exit\n";
    cout << "--------------------------------------------------\n";
    cout << " Enter choice (1-4): ";
}

// Assignment 01 Submenu
static void handleAssignment01() {
    while (true) {
        cout << "\n--- ASSIGNMENT 01 MENU ---\n";
        cout << " 1. Run GEMM (Dense Matrix Multiplication)\n";
        cout << " 2. Run CSR Representation & Traversal\n";
        cout << " 3. Back to Main Menu\n";
        cout << " Enter choice (1-3): ";

        string choice;
        if (!getline(cin, choice) || choice.empty()) continue;

        if (choice == "1") {
            string testPath;
            cout << "Enter GEMM test file path [Default: ASSIGNMENT_01/gemm/gemm_test_01.txt]: ";
            getline(cin, testPath);
            if (testPath.empty()) testPath = "ASSIGNMENT_01/gemm/gemm_test_01.txt";

            string cmd = ".\\ASSIGNMENT_01\\src\\driver.exe " + testPath;
            cout << "\n[Executing]: " << cmd << "\n";
            int ret = system(cmd.c_str());
            if (ret != 0) {
                // Fallback if binary is located in bin/
                string fallbackCmd = ".\\ASSIGNMENT_01\\bin\\driver.exe " + testPath;
                system(fallbackCmd.c_str());
            }
        } 
        else if (choice == "2") {
            string testPath;
            cout << "Enter CSR test file path [Default: ASSIGNMENT_01/csr_test/csr_test_01.txt]: ";
            getline(cin, testPath);
            if (testPath.empty()) testPath = "ASSIGNMENT_01/csr_test/csr_test_01.txt";

            string cmd = ".\\ASSIGNMENT_01\\src\\csr_runner.exe " + testPath;
            cout << "\n[Executing]: " << cmd << "\n";
            int ret = system(cmd.c_str());
            if (ret != 0) {
                string fallbackCmd = ".\\ASSIGNMENT_01\\bin\\csr_runner.exe " + testPath;
                system(fallbackCmd.c_str());
            }
        } 
        else if (choice == "3") {
            break;
        } 
        else {
            cout << "Invalid choice! Please select 1, 2, or 3.\n";
        }
    }
}

// Assignment 02 Submenu
static void handleAssignment02() {
    while (true) {
        cout << "\n--- ASSIGNMENT 02 MENU ---\n";
        cout << " 1. Run Bellman-Ford (Single-Source Shortest Path)\n";
        cout << " 2. Run Floyd-Warshall (All-Pairs Shortest Path)\n";
        cout << " 3. Back to Main Menu\n";
        cout << " Enter choice (1-3): ";

        string choice;
        if (!getline(cin, choice) || choice.empty()) continue;

        if (choice == "1") {
            string testPath;
            cout << "Enter Bellman-Ford test file path [Default: ASSIGNMENT_02/tests/bf_10.txt]: ";
            getline(cin, testPath);
            if (testPath.empty()) testPath = "ASSIGNMENT_02/tests/bf_10.txt";

            string cmd = ".\\ASSIGNMENT_02\\bin\\bf_driver.exe " + testPath;
            cout << "\n[Executing]: " << cmd << "\n";
            int ret = system(cmd.c_str());
            if (ret != 0) {
                cerr << "Error: Execution failed. Please ensure ASSIGNMENT_02/bin/bf_driver.exe is compiled.\n";
            }
        } 
        else if (choice == "2") {
            string testPath;
            cout << "Enter Floyd-Warshall test file path [Default: ASSIGNMENT_02/tests/fw_10.txt]: ";
            getline(cin, testPath);
            if (testPath.empty()) testPath = "ASSIGNMENT_02/tests/fw_10.txt";

            string cmd = ".\\ASSIGNMENT_02\\bin\\fw_driver.exe " + testPath;
            cout << "\n[Executing]: " << cmd << "\n";
            int ret = system(cmd.c_str());
            if (ret != 0) {
                cerr << "Error: Execution failed. Please ensure ASSIGNMENT_02/bin/fw_driver.exe is compiled.\n";
            }
        } 
        else if (choice == "3") {
            break;
        } 
        else {
            cout << "Invalid choice! Please select 1, 2, or 3.\n";
        }
    }
}

// Assignment 03 Submenu
static void handleAssignment03() {
    while (true) {
        cout << "\n--- ASSIGNMENT 03 MENU ---\n";
        cout << " 1. Run Kruskal's MST\n";
        cout << " 2. Run Prim's MST\n";
        cout << " 3. Run Both Algorithms (Kruskal & Prim Comparison)\n";
        cout << " 4. Back to Main Menu\n";
        cout << " Enter choice (1-4): ";

        string choice;
        if (!getline(cin, choice) || choice.empty()) continue;

        if (choice == "1" || choice == "2" || choice == "3") {
            string testPath;
            cout << "Enter MST graph test path [Default: ASSIGNMENT_03/tests/mst_10.txt]: ";
            getline(cin, testPath);
            if (testPath.empty()) testPath = "ASSIGNMENT_03/tests/mst_10.txt";

            string mode = "both";
            if (choice == "1") mode = "kruskal";
            if (choice == "2") mode = "prim";

            string cmd = ".\\ASSIGNMENT_03\\bin\\mst_driver.exe " + testPath + " " + mode;
            cout << "\n[Executing]: " << cmd << "\n";
            int ret = system(cmd.c_str());
            if (ret != 0) {
                cerr << "Error: Execution failed. Please ensure ASSIGNMENT_03/bin/mst_driver.exe is compiled.\n";
            }
        } 
        else if (choice == "4") {
            break;
        } 
        else {
            cout << "Invalid choice! Please select 1-4.\n";
        }
    }
}

int main() {
    string selection;

    while (true) {
        displayMainMenu();
        if (!getline(cin, selection) || selection.empty()) {
            continue;
        }

        if (selection == "1") {
            handleAssignment01();
        } 
        else if (selection == "2") {
            handleAssignment02();
        } 
        else if (selection == "3") {
            handleAssignment03();
        } 
        else if (selection == "4") {
            cout << "\nExiting PG Software Lab Unified Wrapper. Goodbye!\n";
            break;
        } 
        else {
            cout << "\nInvalid choice! Please enter a number between 1 and 4.\n";
        }
    }

    return 0;
}