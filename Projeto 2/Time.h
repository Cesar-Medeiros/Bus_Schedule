#pragma once
#include <iostream>

class Time {

private:
	unsigned int hour;
	unsigned int min;
	unsigned int sizew;

public:
	Time(unsigned int hour, unsigned int min, unsigned int sizew);
	Time();
	unsigned int getHour();
	unsigned int getMin();
	void setw(unsigned int sizew);
	friend std::ostream& operator<<(std::ostream& out, const Time& value);

};