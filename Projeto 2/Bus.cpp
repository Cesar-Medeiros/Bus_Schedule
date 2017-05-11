#include "Bus.h"
#include <utility>


Bus::Bus(unsigned int id, unsigned int driver, unsigned int line, std::vector<Shift> schedule){
	orderInLine = id;
	driverId = driver;
	lineId = line;
	this->schedule = schedule;
}

////////////////////////////////
// get methods
///////////////////////////////
unsigned int Bus::getBusOrderInLine() const{ 
  return orderInLine;
}

unsigned int Bus::getId() const {//same as the one above
	return orderInLine;
}

unsigned int Bus::getDriverId() const{
  return driverId;
}

unsigned int Bus::getLineId() const{
  return lineId;
}

std::vector<Shift> Bus::getSchedule() const{
  return schedule;
}

int Bus::insertShift(Shift shift) {
	if (shift.startTime > 10079 || shift.endTime > 10079)
		return 1;

	if (shift.startTime > shift.endTime)
		return 2;

	if (schedule.empty())
		schedule.push_back(shift);
	else if (shift.endTime < schedule.at(0).startTime)
		schedule.insert(schedule.begin(), shift);
	else {

		for (size_t i = 0; i < schedule.size() - 1; i++) {
			if (shift.endTime < schedule.at(i + 1).startTime) {
				schedule.insert(schedule.begin() + i, shift);
				return 0;
			}
		}

		if (shift.startTime > schedule.at(schedule.size() - 1).endTime)
			schedule.push_back(shift);
		else
			return 3;
	}

}
//////////////////////////////
// metodos set
/////////////////////////////

////////////////////////////
// outher methods
///////////////////////////
