#include "Company.h"


Company::Company(std::string name, std::string fileDrivers, std::string fileLines, std::string fileShift){
	this->name = name;
	this->fileDrivers = fileDrivers;
	this->fileLines = fileLines;
	this->fileShift = fileShift;
}

////////////////////////////////
// metodos get
///////////////////////////////
std::string Company::getName() const{
  return name;
}

//////////////////////////////
// metodos set
/////////////////////////////

////////////////////////////
// outros metodos
///////////////////////////
void Company::distribuiServico(){
}

std::vector<Line> * Company::pointerLines() {
	return &lines;
}

std::vector<Driver> * Company::pointerDrivers() {
	return &drivers;
}

std::vector<Bus> * Company::pointerBus() {
	return &bus;
}

std::multiset<Shift> * Company::pointerShift() {
	return &shifts;
}