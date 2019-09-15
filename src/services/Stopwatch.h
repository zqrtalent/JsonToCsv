#ifndef STOPWATCH_H_INCLUDED
#define STOPWATCH_H_INCLUDED

#include <iostream>
#include <chrono>
using namespace std;

class Stopwatch{
public:
    Stopwatch(){}
    virtual ~Stopwatch(){}

    void Start(){
        _start = std::chrono::high_resolution_clock::now();
        _inProgress = true;
    }

    bool Stop(){
        if(!_inProgress)
            return false;
        _end = std::chrono::high_resolution_clock::now();
        _inProgress = false;

        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);
        _totalMicroseconds = microseconds.count();
        return true;
    }

    unsigned long TotalMicroseconds() const{
        return _totalMicroseconds;
    }

    double TotalSeconds() const{
        return (_totalMicroseconds / 1000000.0);
    }

private:
    bool _inProgress;
    chrono::steady_clock::time_point _start;
    chrono::steady_clock::time_point _end;
    unsigned long _totalMicroseconds;
};
#endif //STOPWATCH_H_INCLUDED