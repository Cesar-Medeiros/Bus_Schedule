#include "Header.h"

void addLine(const std::string &fileName, std::vector<Line> &lines);
void changeLine(const std::string &fileName, std::vector<Line> &lines);
void removeLine(const std::string &fileName, std::vector<Line> &lines);



void linesManager(std::string fileName, std::vector<Line> &lines) {

	do {


		std::cout << "\n\n |            Gestao de linhas            |\n";
		std::cout << " |----------------------------------------|\n";
		std::cout << " |     (1)  Criar nova linha              |\n";
		std::cout << " |     (2)  Alterar linha                 |\n";
		std::cout << " |     (3)  Remover linha                 |\n";
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
				addLine(fileName, lines);
				break;

			case 2:
				changeLine(fileName, lines);
				break;

			case 3:
				removeLine(fileName, lines);
				break;

			default:
				validNumber = false;
				break;
			}

		} while (!validNumber);



		if (openFile(fileName) == 'S') {
			writeLines(lines, fileName);
			openNotepad(fileName);
		}

	} while (true);
}


