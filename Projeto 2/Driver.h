#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Shift.h"
class Shift;
class Driver {
private:

	unsigned int id;
	std::string name;
	unsigned int maxHours;        // maximum duration of a shift
	unsigned int maxWeekWorkingTime;  // maximum number of hours of work in a week
	unsigned int minRestTime;     // minimum number of rest hours between shifts
	std::vector<Shift> shifts;         // assigned shifts

public:
	Driver(unsigned int id, std::string name, unsigned int maxHours, unsigned int maxWeekWorkingTime, unsigned int minRestTime, std::vector<Shift> shifts);
	Driver() {
	};

	// get methods
	unsigned int getId() const;
	std::string getName() const;
	unsigned int getShiftMaxDuration() const;
	unsigned int getMaxHours() const;
	unsigned int getMaxWeekWorkingTime() const;
	unsigned int getMinRestTime() const;
	std::vector<Shift> getShifts() const;

	// set methods

	void setId(unsigned int id);
	void setName(std::string name);
	void setMaxHours(unsigned int maxHours);
	void setMaxWeekWorkingTime(unsigned int maxWeekWorkingTime);
	void setMinRestTime(unsigned int minRestTime);
	void setShifts(std::vector<Shift> shifts);
	
	void insert(unsigned int index, Shift shift);

};
