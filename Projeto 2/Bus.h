#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "Shift.h"



class Bus{
 private:
  unsigned int orderInLine;
  unsigned int driverId;
  unsigned int lineId;
  std::vector<Shift> schedule;

 public:
	 Bus() {  };
  Bus(unsigned int id, unsigned int driver, unsigned int line, std::vector<Shift> schedule = std::vector<Shift>());

  // get methods
  unsigned int getId() const; //Same as getBusOrderInLine(); //Used for template function
  unsigned int getBusOrderInLine() const;
  unsigned int getDriverId() const;
  unsigned int getLineId() const;
  std::vector<Shift> getSchedule() const;

  // set methods
    unsigned int setDriverId() const;
    unsigned int setLineId() const;


  // other methods

	void Bus::insert(unsigned int index, Shift shift);
};

