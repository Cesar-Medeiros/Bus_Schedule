#include "Header.h"
void freeBuses(const std::multiset<Shift> &shifts, int line, int numberOfBus);
void driverVisualize(const Driver &driver, bool displayShift = true);
void busManager(const std::multiset<Shift> &shifts, const std::vector<Driver> &drivers) {

	do {

		std::cout << "\n\n";
		std::cout << " |                 Autocarros             |\n";
		std::cout << " |----------------------------------------|\n";
		std::cout << " |    (1)  Visuzalizar autocarros livres  |\n";
		std::cout << " |    (2)  Condutores sem servico completo|\n";
		std::cout << " |    (0)  Menu principal                 |\n\n";

		bool validNumber;

		do {

			validNumber = true;

			int option = readOption(); //Le a opcao e faz os devidos testes para prevenir input invalido


			switch (option)
			{
			case 0: //Unica maneira de sair
				return;

			case 1:
			{
				unsigned int busLineId, orderBus;
				readNum("Introduza o numero da linha: ", busLineId);
				readNum("Introduza o numero do autocarro: ", orderBus);
				freeBuses(shifts, busLineId, orderBus);
				
				break;
			}

			case 2:
			{
				for (unsigned int i = 0; i < drivers.size();i++) {
					if (drivers.at(i).getMaxWeekWorkingTime() * 60 > drivers.at(i).getMinutesUntilNow()) {
						driverVisualize(drivers.at(i));
						std::cout << "\n";
						std::cout << "---------------------------\n\n";
					}

				}
			}
				break;

			/*case 3:{
				std::multiset<Shift> shiftTemp = shifts;

				unsigned int busLineId, orderBus;
				readNum("Introduza o numero da linha: ", busLineId);
				readNum("Introduza o numero do autocarro: ", orderBus);

				std::multiset<Shift>::iterator it;
				it = shiftTemp.begin();
				while (it != shiftTemp.end())
				{
					if (!(it->getBusLineId() == busLineId && it->getBusOrderNumber() == orderBus && it->getDriverId() == -1))
					{
						it = shiftTemp.erase(it);
					}
					else
					{
						++it;
					}
				}
				
				freeBuses(shiftTemp, busLineId, orderBus);
				break;
			}*/


			default:
				validNumber = false;
				break;
			}



		} while (!validNumber);



	} while (true);
}

