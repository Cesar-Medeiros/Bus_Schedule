
#include "Header.h"
#include <utility>
#include <set>

int verifyShift(const Driver &driver, const Shift &shift, unsigned int &index);
void insertBusOrdered(std::vector<Bus> &bus, Bus busTemp);


void readShift(std::vector<Driver> &drivers, std::multiset<Shift> &shifts, std::string fileName) {

	std::fstream busFile;
	busFile.open(fileName, std::ios::in);

	if (!busFile.is_open())
		return;

	busFile.peek(); //Para posteriormente testar se e o ficheiro esta vazio

	while (!busFile.eof()) { // <--- Com a condicao anterior a flag eof fica se o ficheiro estiver vazio 

		unsigned int busLineId;
		unsigned int driverId;
		unsigned int busOrderNumber;
		unsigned int startTime;
		unsigned int endTime;
		char separationChar;

		busFile >> busLineId >> separationChar >> driverId >> separationChar >> busOrderNumber >> separationChar >> startTime >> separationChar  >> endTime;


		bool found;
		size_t indexDriver;

		for (indexDriver = 0; indexDriver < drivers.size(); indexDriver++) {

			if (drivers.at(indexDriver).getId() == driverId) {
				found = true;
				break;

			}
		}


		busFile >> separationChar >> startTime >> separationChar >> endTime >> separationChar;

		Shift shift1(busLineId, -1, busOrderNumber, startTime, endTime);
		Shift shift2(busLineId, driverId, busOrderNumber, startTime, endTime);

		uint indexInsert;
		verifyShift(drivers.at(indexDriver), shift2, indexInsert);
		
		std::multiset<Shift>::iterator it;
		it = shifts.find(shift1);
		shifts.erase(it);
		shifts.insert(shift2);

		drivers.at(indexDriver).insert(indexInsert, shift2);
		drivers.at(indexDriver).addMinutes(endTime - startTime);

		busFile.peek(); //Para ativar a flag de eof se acabar o ficheiro
	}

	busFile.close();
}

void writeBus(const std::vector<Bus> &bus, std::string fileName) {

	std::fstream busFile;
	busFile.open(fileName, std::ios::out);

	if (!busFile.is_open()) {
		//Fazer alguma coisa antes		
		return;
	}

	for (unsigned int i = 0; i < bus.size(); i++) {
		busFile << bus.at(i).getBusOrderInLine() << " ; " << bus.at(i).getDriverId() << " ; " << bus.at(i).getLineId() << " ; ";

		for (unsigned int j = 0; j < bus.at(i).getSchedule().size(); j++) {
			busFile << "[" << bus.at(i).getSchedule().at(j).getStartTime() << " , " << bus.at(i).getSchedule().at(j).getEndTime() << "]";

			if (j + 1 != bus.at(i).getSchedule().size())
				busFile << ",";
		}
		busFile << std::endl;
	}

}
void insertBusOrdered(std::vector<Bus> &bus, Bus busTemp) {
	if (bus.empty())
		bus.push_back(busTemp);

	else {
		size_t busSize = bus.size();
		for (size_t i = 0; i < busSize; i++) {

			if (i + 1 == bus.size())
				bus.push_back(busTemp);

			else {

				if (busTemp.getBusOrderInLine() < bus.at(i + 1).getBusOrderInLine()) {
					bus.insert(bus.begin() + i, busTemp);
					break;
				}

			}
		}
	}
}


