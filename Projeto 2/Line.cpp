#include "Line.h"


Line::Line(string textLIne){

  // INITIALISATION CODE GOES IN HERE
  

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

vector<string> Line::getBusStops() const{
  return busStopList;
}

vector<int> Line::getTimings() const{
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

void Line::setBusStops(vector<string> busStopList) {
	this->busStopList = busStopList;
}

void Line::setTimings(vector<int> timesList) {
	this->timesList = timesList;
}

void Line::setBusStops(string busStop, unsigned int index) {
	busStopList.at(index) = busStop;
}

void Line::setTimings(int time, unsigned int index) {
	timesList.at(index) = time;
}
