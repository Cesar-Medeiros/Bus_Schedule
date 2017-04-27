#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Shift.h"


using namespace std;

class Driver{

 private:

  unsigned int id;
  string name;
  unsigned int maxHours;        // maximum duration of a shift
  unsigned int maxWeekWorkingTime;  // maximum number of hours of work in a week
  unsigned int minRestTime;     // minimum number of rest hours between shifts
  vector<Shift> shifts;         // assigned shifts

 public:
  Driver(string textLine);
  Driver() {};

  // get methods
  unsigned int getId() const;
  string getName() const;
  unsigned int getShiftMaxDuration() const;
  unsigned int getMaxHours() const;
  unsigned int getMaxWeekWorkingTime() const;
  unsigned int getMinRestTime() const;
  vector<Shift> getShifts() const;


  // set methods

  void setId(unsigned int id);
  void setName(string name);
  void setMaxHours(unsigned int maxHours);
  void setMaxWeekWorkingTime(unsigned int maxWeekWorkingTime);
  void setMinRestTime(unsigned int minRestTime);


  // outher methods

};
