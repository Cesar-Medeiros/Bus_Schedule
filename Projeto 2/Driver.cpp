#include "Driver.h"

Driver::Driver(unsigned int id, std::string name, unsigned int maxHours, unsigned int maxWeekWorkingTime, unsigned int minRestTime, std::vector<Shift> shifts){
	this->id = id;
	this->name = name;
	this->maxHours = maxHours;
	this->maxWeekWorkingTime = maxWeekWorkingTime;
	this->minRestTime = minRestTime;
	this->shifts = shifts;
	this->minutesUntilNow = 0;
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

unsigned int  Driver::getMinutesUntilNow()const {
	return minutesUntilNow;
}


//Set methods
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

void Driver::insert(unsigned int index, Shift shift) {
	shifts.insert(shifts.begin() + index, shift);
}

void Driver::setZeroMinutesUntilNow() {
	this->minutesUntilNow = 0;
}

void Driver::addMinutes(unsigned int add) {
	this->minutesUntilNow += add;
}