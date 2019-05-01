//
// Created by yangwei on 5/1/19.
//
#include <thread>
#include "timer_based_on_ptime.h"
template <typename clock>
timer_myself::timer_based_on_ptime<clock>::timer_based_on_ptime() {
    restart();
    std::cout<<to_simple_string(clock::local_time())<<std::endl;
    //std::cout<<to_simple_string(ptime(date(clock::local_time().date()),hours(10)+minutes(10)))<<std::endl;
}
template <typename clock>
void timer_myself::timer_based_on_ptime<clock>::restart() {
    start_time=clock::local_time();
}
template <typename clock>
time_duration timer_myself::timer_based_on_ptime<clock>::elapsed() {
    return clock::local_time()-start_time;
}
template <typename clock>
timer_myself::timer_based_on_ptime<clock>::~timer_based_on_ptime() {
    std::cout<<elapsed()<<std::endl;
}
int main(){
    timer_myself::timer_based_on_ptime<boost::posix_time::microsec_clock> p;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<p.elapsed()<<std::endl;
    return 0;
}