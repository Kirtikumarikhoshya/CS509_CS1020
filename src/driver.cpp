#include <iostream>
#include <iomanip>
#include "matrix_io.hpp"
#include "gemm.hpp"
#include "timer.hpp"
using namespace std;

static void printMatrix(const Matrix& M){
    for (int i=0;i< M.rows; ++i){
        for(int j=0;j< M.cols; ++j){
            cout<< M.at(i,j);
            if (j+1 < M.cols) cout<< '';
        }
        cout <<'\n';
    }
}

static void printUsage(const char* prog){
    cerr << "usage: " << prog << "<path-to-gemm-input-file>\n"
        << "Example: " << prog << "tests/gemm/gemm_test_01.txt\n";
}

int main(int argc, char* argv[]){
 if (argc !=2) {
    printUsage(argv[0]);
    return 1;
 }  

 const string inputPath =argv[1];

 GemmInput input;
 try{
    input = readGemmInput(inputPath);
 }
 catch(const InputError& e){
    cerr<<"Error:" <<e.what() << '\n'
    return 1;
 }

 Timer timer;
 timer.start();
 Matrix C = gemmSimple(input.A, input.B);
 timer.stop();
 double elapsedMs = timer.elapsedMs();

 int runs = 1;
 const double MIN_RELIABLE_MS = 5.0;
 if (elapsdMs < MIN_RELIABLE_MS){
    runs=100;

    long long sinkAccumalator=0;

    Timer repeatTimer;
    repeatTimer.start();
    for(int r=0; r < runs; ++r){
        Matrix tmp = gemmSimple(input.A, input.B);
        if(!tmp.data.empty()) sinkAccumlator += tmp.data[0];   
    }
    repeatTimer.stop();
    elapsedMs = repeatTimer.elapsedMs()/runs
    if(sinkAccumaltor == 0x7fffffffffffffffLL){
        cerr<< "unreachable\n";
    }
 }


 cout<< "Algorithm: GEMM Simple\n":
 cout<< "Result Matrix:\n";
 printMatrix(c);
 cout<< fixed <<setprecision(4);
 cout<<"Execution time: " <<elapsedMs <<"ms";
 if (runs>1){
    cout << "(averaged over" << runs << "runs)";
 }

 cout<< '\n'

 return 0;
}