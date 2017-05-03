#include "Header.h"

void menu(std::vector<Line> &lines, std::vector<Driver> &drivers, const std::string &linesFile, const std::string &driversFile) {



	do {


		//Menu display

		std::cout << "\n\n |             Menu Principal             |\n";
		std::cout << " |----------------------------------------|\n";
		std::cout << " |     (1)  Gestao de Linhas              |\n";
		std::cout << " |     (2)  Gestao de Condutores          |\n";
		std::cout << " |     (3)  Visualizacao de informacao    |\n";
		std::cout << " |     (4)  Abrir ficheiro linhas         |\n";
		std::cout << " |     (5)  Abrir ficheiro condutores     |\n";
		std::cout << " |     (0)  Sair                          |\n\n";
		//=================================================================================================================

		bool validNumber;


		do {

			validNumber = true;

			int option = readOption();


			switch (option) {
			case 1: linesManager(linesFile, lines); break;
			case 2: driversManager(driversFile, drivers); break;
			case 3: visualizeInfo(lines); break;
			case 4: openNotepad(lines, linesFile);break;
			case 5: openNotepad(drivers, driversFile);break;
			case 0: return; //Unica maneira de sair
			default: validNumber = false;
			}

		} while (validNumber == false);

	} while (true); //Apresentar sempre o menu
}



