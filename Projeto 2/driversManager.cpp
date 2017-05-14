#include "Header.h"

unsigned int addDriver(const std::string &fileName, std::vector<Driver> &drivers);
void changeDriver(const std::string &fileName, std::vector<Driver> &drivers);
void removeDriver(const std::string &fileName, std::vector<Driver> &drivers);


void driversManager(std::string fileName, std::vector<Driver> &drivers) {

	do {

		std::cout << "\n\n |          Gestao de condutores          |\n";
		std::cout << " |----------------------------------------|\n";
		std::cout << " |     (1)  Criar novo condutor           |\n";
		std::cout << " |     (2)  Editar condutor               |\n";
		std::cout << " |     (3)  Remover condutor              |\n";
		std::cout << " |     (0)  Menu principal                |\n\n";


		bool validNumber;

		do {
			validNumber = true;
			int option = readOption();

			switch (option)
			{
			case 0:
				return; //Unica maneira sair

			case 1:
				addDriver(fileName, drivers); break;

			case 2:
				changeDriver(fileName, drivers); break;

			case 3:
				removeDriver(fileName, drivers); break;

			default:
				validNumber = false;
				break;
			}

		} while (!validNumber);

		char openFile;
		ask_YN("Abrir o ficheiro (S ou N)? ", openFile);
		if (toupper(openFile) == 'S') {
			writeDrivers(drivers, fileName);
			openNotepad(fileName);
		}


	} while (true);
}

