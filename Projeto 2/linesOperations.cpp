#include "Header.h"

void insertBusStops(Line &line);
void insertTime(Line &line);
void editStopsDurations(std::vector<Line> &lines, unsigned int posLine);


void addLine(const std::string &fileName, std::vector<Line> &lines) {

	Line line;

	readID(line, lines);

	std::cout << std::endl;
	unsigned int freq;
	readNum("Introduza a frequencia com que o autocarro passa (em minutos): ", freq);
	
	line.setFreq(freq);
	insertBusStops(line);
	insertTime(line);
	sortID(line, lines);

	std::cout << std::endl;
	colorCout('*');
	std::cout << "Linha adicionada com sucesso ao ficheiro " << fileName << std::endl;

}

void changeLine(const std::string &fileName, std::vector<Line> &lines) {

	std::cout << std::endl;
	int posLine = ask_TestID(lines); //Tentar perguntar Insira o ID da linha;
	if (posLine == -1) return;


	cout << "\n\nIdentifier: " << lines.at(posLine).getId() << endl;
	cout << "Frequency: " << lines.at(posLine).getFreq() << endl;

	for (int i = 0; i < lines.at(posLine).getBusStops().size(); i++)
		cout << "Stop " << i << ": " << lines.at(posLine).getBusStop(i) << endl;

	for (int i = 0; i < lines.at(posLine).getTimings().size(); i++)
		cout << "Duration " << i << ": " << lines.at(posLine).getTiming(i) << endl;




	std::cout << "\n\n|               Edit Lines               |\n";
	std::cout << "|----------------------------------------|\n";
	std::cout << "|     (1)  ID                            |\n";
	std::cout << "|     (2)  Frequency                     |\n";
	std::cout << "|     (3)  Stops/Durations               |\n";
	std::cout << "|     (0)  Go Back                       |\n\n";

	bool validNumber;

	do {

		validNumber = true;

		int option = readOption(); //Le a opcao e faz os devidos testes para prevenir input invalido


		switch (option)
		{

		case 0: //Unica maneira de sair
			return;

		case 1: {
			readID(lines.at(posLine), lines);
			sortID(lines);
			break;
		}


		case 2:
			std::cout << std::endl;
			unsigned int freq;
			readNum("Introduza a frequencia com que o autocarro passa (em minutos): ", freq);
			lines.at(posLine).setFreq(freq);
			break;

/*
		case 3: {
			
			std::string busStop;
			std::vector<std::string> busStopList;


			int initialStops, finalStops;

			initialStops = lines.at(posLine).getBusStops().size();
			insertBusStops(lines.at(posLine));
			finalStops = lines.at(posLine).getBusStops().size();

			if (initialStops != finalStops)
				insertTime(lines.at(posLine));

			break;
		}

		case 4:
			insertTime(lines.at(posLine));
			break;*/


		case 3:
			editStopsDurations(lines, posLine);


		default:
			validNumber = false;
			break;
		}

	} while (!validNumber);

	std::cout << std::endl;
	colorCout('*');
	std::cout << "Linha alterada com sucesso no ficheiro " << fileName << std::endl;
}

void removeLine(const std::string &fileName, std::vector<Line> &lines) {

	int pos = ask_TestID(lines); //Devolve a posicao da linha atraves da introducao do id ou devolve -1 se nao encontrar 

	if (pos != -1) {
		lines.erase(lines.begin() + pos);
		std::cout << std::endl;
		colorCout('*');
		std::cout << "Linha removida com sucesso ao ficheiro " << fileName << std::endl;
	}
	else {
		std::cout << std::endl;
		colorCout('!');
		std::cout << "Nao foi possivel eliminar a linha." << std::endl;
	}

}
