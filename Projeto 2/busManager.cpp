#include "Header.h"

/*
void addBus(const std::string &fileName, std::vector<Bus> &bus);
void changeBus(const std::string &fileName, std::vector<Bus> &bus);
void removeBus(const std::string &fileName, std::vector<Bus> &bus);



void busManager(std::string fileName, std::vector<Bus> &bus) {

	do {

		std::cout << "\n\n";
		std::cout << " |           Gestao de autocarros         |\n";
		std::cout << " |----------------------------------------|\n";
		std::cout << " |     (1)  Novo autocarro                |\n";
		std::cout << " |     (2)  Editar autocarro              |\n";
		std::cout << " |     (3)  Remover autocarro             |\n";
		std::cout << " |     (0)  Menu principal                |\n\n";

		bool validNumber;

		do {

			validNumber = true;

			int option = readOption(); //Le a opcao e faz os devidos testes para prevenir input invalido


			switch (option)
			{
			case 0: //Unica maneira de sair
				return;

			case 1:
				addBus(fileName, bus);
				break;

			case 2:
				changeBus(fileName, bus);
				break;

			case 3:
				removeBus(fileName, bus);
				break;


			default:
				validNumber = false;
				break;
			}



		} while (!validNumber);


		char openFile;
		ask_YN("Abrir o ficheiro (S ou N)? ", openFile); //Mais facil para debug
		if (toupper(openFile) == 'S') {
			writeBus(bus, fileName);
			openNotepad(fileName);
		}

	} while (true);
}

*/
