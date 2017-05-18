#include "Header.h"
#include "string"

void timeBetween2Stops(const std::vector<Line> &lines);
void printSchedule(const std::vector<Line> &line, int posLine);
void printStopSchedule(const std::vector<Line> &lines);
void showLine(const std::vector<Line> &line);
void searchBusStop(const std::vector<Line> &line);
void printCentered(std::ostream& out, const std::string info, const unsigned int sizew);
void driverVisualize(const Driver &driver, bool displayShift = true);
void busManager(const std::multiset<Shift> &shifts, const std::vector<Driver> &drivers);



void visualizeInfo(const std::vector<Line> &lines, const std::vector<Driver> &drivers, const std::multiset<Shift> &shifts) {



	do {


		std::cout << "\n\n |          Visualizar Informacao         |\n";
		std::cout << " |----------------------------------------|\n";
		std::cout << " |     (1)  Horario de uma linha          |\n";
		std::cout << " |     (2)  Horario de uma paragem        |\n";
		std::cout << " |     (3)  Tempo entre duas paragens     |\n";
		std::cout << " |     (4)  Visualizar uma linha          |\n";
		std::cout << " |     (5)  Linhas com uma paragem        |\n";
		std::cout << " |     (6)  Informacao de um condutor     |\n";
		std::cout << " |     (7)  Autocarros                    |\n";
		std::cout << " |     (0)  Menu principal                |\n\n";

		bool validNumber;

		do {

			validNumber = true;

			int option = readOption(); //Le a opcao e faz os devidos testes para prevenir input invalido

			switch (option) {

			case 0: return;

			case 1: {
				int posLine = ask_TestID(lines);

				if (posLine == -1) { //Linha nao foi encontrada
					colorCout('!');
					std::cout << "Nao foi possivel apresentar o horario da linha que introduziu." << std::endl;
				}
				else {
					printSchedule(lines, posLine);
					std::cout << "\nClique em qualquer tecla para continuar";
					getchar();
				}
				break;
			}

			case 2:
				printStopSchedule(lines);
				break;

			case 3:
				timeBetween2Stops(lines);
				std::cout << "\nClique em qualquer tecla para continuar";
				getchar();
				break;

			case 4:
				showLine(lines);
				std::cout << "\n\nClique em qualquer tecla para continuar";
				getchar();
				break;

			case 5:
				searchBusStop(lines);
				std::cout << "\nClique em qualquer tecla para continuar";
				getchar();
				break;

			case 6: {
				int posDriver = ask_TestID(drivers);
				if (posDriver != -1)
					driverVisualize(drivers.at(posDriver));
				break;
			}

			case 7: {
				busManager(shifts,drivers);
			}

			default: validNumber = false;
			}

		} while (!validNumber);


	} while (true);

}


