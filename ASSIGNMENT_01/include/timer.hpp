#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>  //provides high_resolution_clock
using namespace std;

class Timer{
public:
    //calling start() records "now" into start_
    void start(){
        start_ =chrono::high_resolution_clock::now();
    }
    //calling end() records "now" into end_
    void stop(){
        end_ = chrono::high_resolution_clock::now();
    }
    //difference in end_ and start_ and conversion to milliseconds for precision
    double elapsedMs() const{
        return chrono::duration<double, milli>(end_-start_).count();
    }
private:
   chrono::high_resolution_clock::time_point start_;
   chrono::high_resolution_clock::time_point end_;
};

#endif