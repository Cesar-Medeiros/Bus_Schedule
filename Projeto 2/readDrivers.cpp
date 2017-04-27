#include "Header.h"

void readDrivers(std::vector<Driver> &drivers, std::string fileName) {
	std::fstream DriversFile(fileName);
	

	DriversFile.peek();

	while (!DriversFile.eof()) {
		char comma;

		int id;
		std::string name;
		unsigned int maxHours;
		unsigned int maxWeekWorkingTime;
		unsigned int minRestTime;


		DriversFile >> id >> comma;

		if (DriversFile.eof()) break; //Se a linha terminar com /n
		
		


		getline(DriversFile, name, ';');
		name = name.substr(1, name.length() - 2); //Ver outra maneira mais simples de cortar o nome!!!
		DriversFile >> maxHours >> comma >> maxWeekWorkingTime >> comma >> minRestTime;

		//Gravar tudo em Drivers

		Driver driver;
		driver.setId(id);
		driver.setName(name);
		driver.setMaxHours(maxHours);
		driver.setMaxWeekWorkingTime(maxWeekWorkingTime);
		driver.setMinRestTime(minRestTime);

		drivers.push_back(driver);
	}

}