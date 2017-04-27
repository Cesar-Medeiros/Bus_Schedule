#include "Header.h"

void writeDrivers(const std::vector<Driver> &drivers, std::string fileName) {

	std::fstream condutoresFile;
	condutoresFile.open(fileName, std::ios::out);

	for (uint i = 0; i < drivers.size(); i++) {
		
		condutoresFile << drivers.at(i).getId() << " ; " << drivers.at(i).getName() << " ; ";
		condutoresFile << drivers.at(i).getMaxHours() << " ; ";
		condutoresFile << drivers.at(i).getMaxWeekWorkingTime() << " ; ";
		condutoresFile << drivers.at(i).getMinRestTime();
		condutoresFile << std::endl;
	}
	condutoresFile.close();
}
