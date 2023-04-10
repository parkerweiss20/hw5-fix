#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool scheduleHelper(size_t worker, size_t shift, size_t maxShifts, size_t dailyNeed, vector<size_t>& shifts, 
	const AvailabilityMatrix& avail, DailySchedule& sched);

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.empty()){
        return false;
    }
    sched.clear();
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> shifts(avail[0].size(), 0);

    return scheduleHelper(0, 0, maxShifts, dailyNeed, shifts, avail, sched);
}

bool scheduleHelper(size_t worker, size_t shift, size_t maxShifts, size_t dailyNeed, vector<size_t>& shifts, 
	const AvailabilityMatrix& avail, DailySchedule& sched){
	if(worker == avail.size()){
		return true;
	}
	for(size_t x = 0; x < avail[0].size(); x++){
		if(avail[worker][x] == 1 && shifts[x] < maxShifts){
			sched[worker][shift] = x;
			shifts[x]++;
				
			size_t nextShift = (shift + 1) % dailyNeed;
			size_t nextWorker = worker + ((shift + 1) / dailyNeed);

			if(scheduleHelper(nextWorker, nextShift, maxShifts, dailyNeed, shifts, avail, sched)){
				return true;
			}
				
			shifts[x]--;
			sched[worker][shift] = INVALID_ID;
		}
	}
	return false;
}
