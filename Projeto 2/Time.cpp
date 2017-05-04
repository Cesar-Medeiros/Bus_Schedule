#include "Time.h"
#include <string>

void printCentered(std::ostream& out, const std::string info, const unsigned int sizew);

Time::Time() {
	hour = 0;
	min = 0;
	this->sizew = 5;
}

Time::Time(unsigned int hour, unsigned int min, unsigned int sizew) {
	this->hour = hour;
	this->min = min;
	this->sizew = sizew;
}

unsigned int Time::getHour() {
	return hour;
}
unsigned int Time::getMin() {
	return min;
}
void Time::setw(unsigned int sizew) {

	this->sizew = sizew;

}

std::ostream& operator<<(std::ostream& out, const Time& value) {

	std::string minStr = (value.min < 10) ? ("0" + std::to_string(value.min)) : std::to_string(value.min);
	std::string hourStr = (value.hour < 10) ? ("0" + std::to_string(value.hour)) : std::to_string(value.hour);

	std::string time = hourStr + ":" + minStr;

	printCentered(out, time, value.sizew);

	return out;
}


