//
// Created by yangwei on 5/1/19.
//

#ifndef RADAR_TCP_TIMER_BASED_ON_PTIME_H
#define RADAR_TCP_TIMER_BASED_ON_PTIME_H
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
using namespace boost::gregorian;
namespace timer_myself {
template <typename clock=boost::posix_time::microsec_clock>
    class timer_based_on_ptime {
    public:
        timer_based_on_ptime();

        void restart();

        time_duration elapsed();

        ~timer_based_on_ptime();

    private:
        ptime start_time;
    };
}


#endif //RADAR_TCP_TIMER_BASED_ON_PTIME_H
