#include "Header.h"
#include <set>

void driverVisualize(const Driver &driver);
unsigned int addDriver(const std::string &fileName, std::vector<Driver> &drivers);



unsigned int timeService() {

	std::string dayName;
	unsigned int hour, min;

	unsigned int weekDay;
	bool invalidInput;
	do {
		invalidInput = false;
		char dots;
		std::cin >> dayName >> hour >> dots >> min;

		bool invalidDayName = false;


		if (dayName == "Seg")
			weekDay = 0;
		else if (dayName == "Ter")
			weekDay = 1;
		else if (dayName == "Qua")
			weekDay = 2;
		else if (dayName == "Qui")
			weekDay = 3;
		else if (dayName == "Sex")
			weekDay = 4;
		else if (dayName == "Sab")
			weekDay = 5;
		else if (dayName == "Dom")
			weekDay = 6;
		else weekDay = -1;


		if (std::cin.fail() || weekDay == -1 || hour >= 24 || min >= 60){
			invalidInput = true;
			std::cin.clear();
			std::cin.ignore(10000,'\n');
		}

		if (invalidInput) {
			colorCout('!');
			std::cout << "Invalid Input\n\n";
		}

	} while (invalidInput);

	return weekDay * 24 * 60 + hour * 60 + min;
}

void createShiftReal(Driver &driver, Bus &bus) {

	bool finish = false;

	unsigned int busLineId, busNumber;

	readNum("Introduza o numero da linha: ", busLineId);
	readNum("Introduza o numero do autocarro: ", busNumber);

	
	bus = Bus(busNumber, driver.getId(), busLineId);


	while (!finish) {

		std::cout << std::endl;
		colorCout('?');
		std::cout << "Introduza o tempo no formato Dia hh:mm (Ex: Seg 8:00): " << std::endl;

		std::cout << "Inicio do servico: " << std::endl;
		unsigned int startTime = timeService();

		std::cout << "Fim do servico: " << std::endl;
		unsigned int endTime = timeService();

		Shift shift(busLineId, driver.getId(), busNumber, startTime, endTime);
		int errorCode = driver.insertShift(shift);
		
		switch(errorCode){
		case 1: 
			colorCout('!');
			std::cout << "Fora da gama\n\n";
			break;

		case 2:
			colorCout('!');
			std::cout << "Tempo inicial maior que tempo final\n\n";
			break;

		case 3:
			colorCout('!');
			std::cout << "Nao foi possivel inserir este turno\n\n";
			break;

		default:
			bus.insertShift(shift);


		}
		
		bool invalidInput;
		
		do{
			invalidInput = false;
			finish = false;

			char answer;
			colorCout('?');
			std::cout << "Deseja introduzir mais algum turno(S/N): ";
			std::cin >> answer;

			if (toupper(answer) == 'N')
				finish = true;
			else if (toupper(answer) != 'S')
				bool invalidInput = true;

		} while (invalidInput == true);



	}
	
	

}


void createShift(const std::string &fileName, std::vector<Driver> &drivers, std::vector<Bus> &bus) {
	

	unsigned int driverIndex = ask_TestID(drivers);
	
	if (driverIndex == -1) {

		char answer;
		do {
			colorCout('?');
			std::cout << "Deseja adicionar um condutor (S/N) ?";
			std::cin >> answer;

			char bufferContent;
			std::cin.get(bufferContent);
			if (bufferContent != '\n') {
				std::cin.ignore(1000, '\n');
				answer = 0;
				colorCout('!');
				std::cout << "Invalid Input" << std::endl;
			}

		} while (toupper(answer) != 'N' && toupper(answer) != 'S');

		if (toupper(answer) == 'N')
			return;

		else 
			driverIndex = addDriver(fileName, drivers);
		
	}

	Bus busTemp;

	//Turnos Existentes
	createShiftReal(drivers.at(driverIndex), busTemp);
	
	if (bus.empty())
		bus.push_back(busTemp);

	else {

		for (size_t i = 0; i < bus.size() - 1; i++) {
			if (busTemp.getBusOrderInLine() < bus.at(i + 1).getBusOrderInLine()) {
				bus.insert(bus.begin() + i, busTemp);
				break;
			}
		}
	}

	writeBus(bus, "bus.txt");

	driverVisualize(drivers.at(driverIndex));

}



void verifyShift();
void deleteShift();
void editShift();
