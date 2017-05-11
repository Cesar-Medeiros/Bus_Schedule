#include "Line.h"


Line::Line(std::string textLIne){

  // INITIALISATION CODE GOES IN HERE
  

}

Line::Line(unsigned int id, unsigned int freq, std::vector<std::string> busStopList, std::vector<int> timesList) {
	
	this->id = id;
	this->freq = freq;
	this->busStopList = busStopList;
	this->timesList = timesList;
}

////////////////
// get methods
////////////////

unsigned int Line::getId() const{
  return id;
}

unsigned int Line::getFreq() const {
	return freq;
}

std::vector<std::string> Line::getBusStops() const{
  return busStopList;
}

std::vector<int> Line::getTimings() const{
  return timesList;
}


std::string Line::getBusStop(unsigned int index) const {
	return busStopList.at(index);
}

unsigned int Line::getTiming(unsigned int index) const {
	return timesList.at(index);	
}


void Line::setId(unsigned int id) {
	this->id = id;
}

void Line::setFreq(unsigned int freq) {
	this->freq = freq;
}

void Line::setBusStops(std::vector<std::string> busStopList) {
	this->busStopList = busStopList;
}

void Line::setTimings(std::vector<int> timesList) {
	this->timesList = timesList;
}

void Line::setBusStops(std::string busStop, unsigned int index) {
	busStopList.at(index) = busStop;
}

void Line::setTimings(int time, unsigned int index) {
	timesList.at(index) = time;
}

unsigned int Line::timeLine() {

	unsigned int time = 0;
	for (unsigned int i = 0; i < timesList.size(); i++) {
		time += timesList.at(i);
	}

	return time;
}