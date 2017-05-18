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

void Bus::setBusOrderInLine(unsigned int orderInLine) {
	this->orderInLine = orderInLine;
}

void Bus::insert(unsigned int index, Shift shift) {
	schedule.insert(schedule.begin() + index, shift);
}
//////////////////////////////
// metodos set
/////////////////////////////

////////////////////////////
// outher methods
///////////////////////////
