
#include "Header.h"
#include <utility>
#include <set>

int verifyShift(const Driver &driver, const Shift &shift, unsigned int &index);


void readShift(std::vector<Driver> &drivers, std::multiset<Shift> &shifts, std::string fileName) {

	std::fstream shiftFile;
	shiftFile.open(fileName, std::ios::in);

	if (!shiftFile.is_open())
		return;

	shiftFile.peek(); //Para posteriormente testar se e o ficheiro esta vazio

	while (!shiftFile.eof()) { // <--- Com a condicao anterior a flag eof fica se o ficheiro estiver vazio 

		unsigned int busLineId;
		unsigned int driverId;
		unsigned int busOrderNumber;
		unsigned int startTime;
		unsigned int endTime;
		char separationChar;

		shiftFile >> busLineId >> separationChar >> driverId >> separationChar >> busOrderNumber >> separationChar >> startTime >> separationChar  >> endTime;


		bool found;
		size_t indexDriver;

		for (indexDriver = 0; indexDriver < drivers.size(); indexDriver++) {

			if (drivers.at(indexDriver).getId() == driverId) {
				found = true;
				break;

			}
		}

		Shift shift1(busLineId, -1, busOrderNumber, startTime, endTime);
		Shift shift2(busLineId, driverId, busOrderNumber, startTime, endTime);

		uint indexInsert;
		verifyShift(drivers.at(indexDriver), shift2, indexInsert);
		
		std::multiset<Shift>::iterator it;
		it = shifts.find(shift1);
		shifts.erase(it);
		shifts.insert(shift2);

		drivers.at(indexDriver).insert(indexInsert, shift2);

		shiftFile.get();
		shiftFile.peek(); //Para ativar a flag de eof se acabar o ficheiro
	}

	shiftFile.close();
}

void writeShift(const std::multiset<Shift> shifts, std::string fileName) {

	std::fstream shiftsFile;
	shiftsFile.open(fileName, std::ios::out);

	if (!shiftsFile.is_open()) {
		//Fazer alguma coisa antes
		return;
	}

	
	std::multiset<Shift>::iterator it;
	for (it = shifts.begin(); it != shifts.end(); ++it) {
		if(it->getDriverId() != -1){
			shiftsFile << it->getBusLineId() << " ; " << it->getDriverId() << " ; " << it->getBusOrderNumber() << " ; " << it->getStartTime() << " ; " << it->getEndTime();
			shiftsFile << std::endl;
		}
		
	}
	

}


