#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

static void showMenu(){
    cout<< " 1. Run GEMM \n";
    cout<< "2. Run CSR \n";
    cout<< "3. Exit \n";
    cout<< " Enter choice (1-3)";

}

// int main(){
//     int choice;
//     while(true){
//         showMenu();
//         if(!(cin >> choice)){
//             cin.clear();
//             cin.ignore(1000,'\n');
//             continue;
//         }

//         if (choice ==1){
//             string testFile;
//             cout << "enter gemm test file path";
//             getline(cin, testFile);
            

//             string cmd = ".\\ASSIGNMENT_01\\src\\driver.exe " + testFile;
//             // string cmd = " .\\ASSIGNMENT_01\\src\\driver.exe" + testFile;
//             int ret = system(cmd.c_str());
//             if (ret != 0){
//                 cerr << "execution failes";

//             }

//         }

//         else if (choice == 2){
//             string testFile;
//             cout << "enter CSR test file path";
//            getline(cin,testFile);
            

//            string cmd = ".\\ASSIGNMENT_01\\src\\csr_runner.exe " + testFile;
//             // string cmd = " \\ASSIGNMENT_01\\srC\\csr_runner.exe "+ testFile;
//             int ret = system(cmd.c_str());
//             if (ret != 0){
//                 cerr << "execution fails";

//             }
//         }

//         else if (choice == 3){
//             cout << " exiting wrapper menu ";
//             break;
//         }
//         else{
//             cout << "Invalid selection";
    
//         }
//     }
//     return 0;
// }

int main() {
    string choiceStr; //string to take choices from the user
    while (true) {
        showMenu();
        if (!getline(cin, choiceStr) || choiceStr.empty()) {
            continue;
        }
        //choice 1 to run the GEMM test files
        if (choiceStr == "1") {
            string testFile;
            cout << "\nEnter GEMM test file path [e.g., ASSIGNMENT_01/gemm/gemm_test_01.txt]: ";
            getline(cin,testFile);

            //getline used to get the correct paths
            string cmd = ".\\ASSIGNMENT_01\\src\\driver.exe " + testFile;
            cout << "Executing: " << cmd << endl;
            int ret = system(cmd.c_str());
            if (ret != 0) {
                cerr << "executiin failed";
            }
        } 

        //choice 2 for CSR 
        else if (choiceStr == "2") {
            string testFile;
            cout << "\nEnter CSR test file path [e.g., ASSIGNMENT_01/csr_test/csr_test_01.txt]: ";
            getline(cin,testFile);

    
            string cmd = ".\\ASSIGNMENT_01\\src\\csr_runner.exe " + testFile;
            cout << "Executing: " << cmd << endl;
            int ret = system(cmd.c_str());
            if (ret != 0) {
                cerr << "execution failed";
            }
        } 

        //exit for wrapper as 2 test available till now
        else if (choiceStr == "3") {
            cout << "Exit wrapper menu...\n";
            break;
        } 
        else {
            cout << "invalid choice\n";
        }
    }
    return 0;
}