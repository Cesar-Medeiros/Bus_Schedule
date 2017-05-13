#include "Company.h"


Company::Company(std::string name, std::string fileDrivers, std::string fileLines, std::string fileBus){
	this->name = name;
	this->fileDrivers = fileBus;
	this->fileLines = fileLines;
	this->fileBus = fileBus;
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
