#include "Header.h"
#include <set>

void driverVisualize(const Driver &driver);
int verifyShift(const Driver &driver, const Shift &shift, unsigned int &index);
void insertBusOrdered(std::vector<Bus> &bus, Bus busTemp);



unsigned int timeShift() {

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


		if (std::cin.fail() || weekDay == -1 || hour >= 24 || min >= 60) {
			invalidInput = true;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}

		if (invalidInput) {
			colorCout('!');
			std::cout << "Invalid Input\n\n";
		}

	} while (invalidInput);

	return weekDay * 24 * 60 + hour * 60 + min;
}

void addShift(Driver &driver, Bus &bus) {

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
		unsigned int startTime = timeShift();

		std::cout << "Fim do servico: " << std::endl;
		unsigned int endTime = timeShift();

		Shift shift(busLineId, driver.getId(), busNumber, startTime, endTime);

		uint indexInsertion;

		int errorCode = verifyShift(driver, shift, indexInsertion);

		switch (errorCode) {
		case 0:
			bus.insert(indexInsertion, shift);
			driver.insert(indexInsertion, shift);
			break;

		case 1:
			colorCout('!');
			std::cout << "Foi ultrapassada a duracao maxima de um turno" << std::endl;
			break;

		case 2:
			colorCout('!');
			std::cout << "Foram ultrapassadas as horas de trabalho maximas por semana" << std::endl;
			break;

		case 3:
			colorCout('!');
			std::cout << "Nao foi respeitado o tempo minimo de descanso entre turnos" << std::endl;
			break;
		case 4:
			colorCout('!');
			std::cout << "Tempo inicial do turno superior ao tempo final" << std::endl;
			break;
		}


		char answer;
		ask_YN("Deseja introduzir mais algum turno(S/N): ", answer);

		if (toupper(answer) == 'N')
			finish = true;

	}
}

void createShift(const std::string &fileName, std::vector<Driver> &drivers, std::vector<Bus> &bus) {


	unsigned int driverIndex = ask_TestID(drivers);

	if (driverIndex == -1) {

		char answer;
		ask_YN("Deseja adicionar um condutor(S / N) ? " , answer);

		if (toupper(answer) == 'N')
			return;

		else
			driverIndex = addDriver(fileName, drivers);
	}

	Bus busTemp;

	//Turnos Existentes
	addShift(drivers.at(driverIndex), busTemp);


	//Inserir por ordem crescente os autocarros
	insertBusOrdered(bus, busTemp);

	writeBus(bus, "bus.txt"); //Depois e' so' acrescentar um parametro com o nome do ficheiro de condutores

	driverVisualize(drivers.at(driverIndex));

}

int verifyShift(const Driver &driver, const Shift &shift, unsigned int &index) {

	int duration = (shift.getEndTime() - shift.getStartTime());
	
	if (duration < 0)
		return 4;

	else if (duration > driver.getMaxHours()*60)
		return 1;

	else if (duration > driver.getMaxWeekWorkingTime()*60) 
		return 2;

	else {
		unsigned int i = 0;
		index = i;
		for (i; i < driver.getShifts().size(); i++) {

			if (shift.getEndTime() + driver.getMinRestTime() * 60 < driver.getShifts().at(i).getStartTime()) {
				if (i == 0 || shift.getStartTime() > driver.getMinRestTime() + driver.getShifts().at(i - 1).getEndTime()) {
					index = i;
					return 0;
				}
			}

			if (i + 1 == driver.getShifts().size()) {
				if (shift.getStartTime() > driver.getShifts().at(i).getEndTime() + driver.getMinRestTime() * 60) {
					index = i + 1;
					return 0;
				}
				else return 3;
			}

			

		}


		return 0;

	}



}


void deleteShift();
void editShift();
