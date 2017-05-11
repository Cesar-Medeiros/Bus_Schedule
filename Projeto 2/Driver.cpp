#include "Driver.h"

Driver::Driver(unsigned int id, std::string name, unsigned int maxHours, unsigned int maxWeekWorkingTime, unsigned int minRestTime, std::vector<Shift> shifts){
	this->id = id;
	this->name = name;
	this->maxHours = maxHours;
	this->maxWeekWorkingTime = maxWeekWorkingTime;
	this->minRestTime = minRestTime;
	this->shifts = shifts;
}

//////////////
// get methods
//////////////

unsigned int Driver::getId() const{
  return id;
}

std::string Driver::getName() const{
  return name;
}

unsigned int Driver::getShiftMaxDuration() const{
  return maxHours;
}

unsigned int Driver::getMaxWeekWorkingTime() const{
  return maxWeekWorkingTime;
}

unsigned int Driver::getMaxHours() const {
	return maxHours;
}

unsigned int Driver::getMinRestTime() const{
  return minRestTime;
}

std::vector<Shift> Driver::getShifts() const{
  return shifts;
}

void Driver::setId(unsigned int id) {
	this->id = id;
}

void Driver::setName(std::string name) {
	this->name = name;
}

void Driver::setMaxHours(unsigned int maxHours) {
	this->maxHours = maxHours;
}

void Driver::setMaxWeekWorkingTime(unsigned int maxWeekWorkingTime) {
	this->maxWeekWorkingTime = maxWeekWorkingTime;
}

void Driver::setMinRestTime(unsigned int minRestTime) {
	this->minRestTime = minRestTime;
}

void Driver::setShifts(std::vector<Shift> shifts) {
	this->shifts = shifts;
}

int Driver::insertShift(Shift shift) {
	if (shift.startTime > 10079 || shift.endTime > 10079)
		return 1;

	if (shift.startTime > shift.endTime)
		return 2;
	
	if (shifts.empty())
		shifts.push_back(shift);
	else if (shift.endTime < shifts.at(0).startTime)
		shifts.insert(shifts.begin(), shift);
	else {

		for (size_t i = 0; i < shifts.size()-1; i++) {
			if (shift.endTime < shifts.at(i+1).startTime) {
				shifts.insert(shifts.begin() + i, shift);
				return 0;
			}
		}

		if (shift.startTime > shifts.at(shifts.size() - 1).endTime)
			shifts.push_back(shift);
		else
		return 3;
	}

}