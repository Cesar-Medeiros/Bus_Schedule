#include "Driver.h"

Driver::Driver(string textLine){

  // INITIALISATION CODE GOES IN HERE
  
}

//////////////
// get methods
//////////////

unsigned int Driver::getId() const{
  return id;
}

string Driver::getName() const{
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

vector<Shift> Driver::getShifts() const{
  return shifts;
}

void Driver::setId(unsigned int id) {
	this->id = id;
}

void Driver::setName(string name) {
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

