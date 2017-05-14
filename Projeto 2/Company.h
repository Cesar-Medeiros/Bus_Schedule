#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Line.h"
#include "Driver.h"
#include "Bus.h"



class Company{
 private:
 
 std::string name;

 std::vector<Driver> drivers;
 std::vector<Line> lines;
 std::vector<Bus> bus;

 std::string fileDrivers;
 std::string fileLines;
 std::string fileBus;

 public:
	 Company(std::string name, std::string fileDrivers, std::string fileLines, std::string fileBus);
  // metodos get
	 std::string getName() const;
  // metodos set
  // outros metodos
  void distribuiServico(); // funcao que implementa a afectacao de servico

  std::vector<Line> * pointerLines();

  std::vector<Driver> * pointerDrivers();

  std::vector<Bus> * pointerBus();

};
