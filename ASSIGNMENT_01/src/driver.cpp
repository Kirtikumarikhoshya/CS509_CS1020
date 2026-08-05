#include <iostream>
#include <iomanip>
#include <functional>
#include "matrix_io.hpp"
#include "gemm.hpp"
#include "timer.hpp"
using namespace std;

static void printMatrix(const Matrix& M){
    for (int i=0;i< M.rows; ++i){
        for(int j=0;j< M.cols; ++j){
            cout << M.at(i,j);
            if (j+1 < M.cols) cout<< ' ';
        }
        cout <<'\n';
    }
}

static void printUsage(const char* prog){
    cerr << "usage: " << prog << "<path-to-gemm-input-file>\n"
        << "Example: " << prog << "tests/gemm/gemm_test_01.txt\n";
}


struct TimedResult{
    Matrix result;
    double elapsedMs;
    int runs;
};

static TimedResult runTimed(const function<Matrix(const Matrix&, const Matrix&)>& algo, const Matrix& A, const Matrix& B){
 Timer timer;
 timer.start();
 Matrix result= algo(A, B);
 timer.stop();
 double elapsedMs = timer.elapsedMs();

 int runs = 1;
 const double MIN_RELIABLE_MS = 5.0;
 if (elapsedMs < MIN_RELIABLE_MS){
    runs=100;

    long long sinkAccumalator=0;

    Timer repeatTimer;
    repeatTimer.start();
    for(int r=0; r < runs; ++r){
        Matrix tmp = algo(A,B);
        if(!tmp.data.empty()) sinkAccumalator += tmp.data[0];   
    }
    repeatTimer.stop();
    elapsedMs = repeatTimer.elapsedMs()/runs;
    if(sinkAccumalator == 0x7fffffffffffffffLL){
        cerr<< "unreachable\n";
    }
 }
 return TimedResult{ result, elapsedMs, runs};
}


static void printTimedOutput(const string& algorithmLabel, const TimedResult& tr){
    cout << "Algorithm: " << algorithmLabel << "\n";
    cout << "Result matrix: \n";
    printMatrix(tr.result);
    cout << fixed << setprecision(4);
    cout <<"Execution time: " << tr.elapsedMs << "ms";
   
    if(tr.runs >1){
    cout << "(averaged over" << tr.runs << "runs)";
     }
}

//to check equivalnce of matrices
static bool matricesEqual(const Matrix& X, const Matrix& Y){
    if( X.rows != Y.rows || X.cols !=Y.cols) return false;
    return X.data == Y.data;
}


int main(int argc, char* argv[]){
 if (argc !=2) {
    printUsage(argv[0]);
    return 1;
 }  

 const string inputPath = argv[1];

 GemmInput input;
 try {
    input = readGemmInput(inputPath);
 }
 catch(const InputError& e){
    cerr<<"Error:" <<e.what() << '\n' ;
    return 1;
 }
 catch(const exception& e){
    cerr << "Unexpected error while reading input: " << e.what() << '\n';
    return 1;
 }

 TimedResult simple = runTimed(gemmSimple, input.A, input.B);
 TimedResult blocking = runTimed(gemmBlocking , input.A, input.B);

 printTimedOutput("GEMM Simple", simple);
 cout << '\n';
 printTimedOutput("GEMM Blocking" ,blocking);

 cout<< '\n';

 if (matricesEqual(simple.result, blocking.result)){
 cout << "Correctness check: PASS(RESULTS MATCH)\n";
 }else{
 cout << "Correctness check :FAIL(RESULTS NOT MATCHED)\n";
}

cout << "Block size used: " <<  BLOCK_SIZE << "\n";

return 0;
}