#include "Header.h"

void insertBusStops(Line &line);
void insertTime(Line &line);


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




	std::cout << "\n\n|              Alterar linha             |\n";
	std::cout << "|----------------------------------------|\n";
	std::cout << "|     (1)  ID                            |\n";
	std::cout << "|     (2)  Frequencia                    |\n";
	std::cout << "|     (3)  Paragens                      |\n";
	std::cout << "|     (4)  Tempo entre paragens          |\n";
	std::cout << "|     (0)  Voltar Gerir linhas           |\n\n";

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
			break;


		case 5:
		{
			//Fazer em forma de funcao
			do {
				std::cout << "\n\n|              Stops/Durations              |\n";
				std::cout << "|-------------------------------------------|\n";
				std::cout << "|     (1)  Change a stop                    |\n";
				std::cout << "|     (2)  Correct a duration between stops |\n";
				std::cout << "|     (3)  Change every stop/duration       |\n";
				std::cout << "|     (0)  Go back                          |\n\n";

				int option = readOption();

				switch (option) {
				case 0: return;
				case 1:
				{
					for (unsigned int i = 0; i < lines.at(posLine).getBusStops().size(); i++)
						cout << "Stop " << i + 1 << ": " << lines.at(posLine).getBusStop(i) << endl;



					//New stop
					unsigned int stopIndex;
					do {
						readNum("Select the one to change: ", stopIndex, true);
						stopIndex--;
					} while (stopIndex < 1 || stopIndex >= lines.at(posLine).getBusStops().size());




					//Correct the durations based on the new location

					if (stopIndex == 0)
					{
						std::string text;
						unsigned int duration;
						text = "What's the time between " + lines.at(posLine).getBusStop(stopIndex) + " and " + lines.at(posLine).getBusStop(stopIndex + 1) + ": ";
						readNum(text.c_str(), duration, true);
					}

					else if (stopIndex == lines.at(posLine).getTimings().size() - 1)
					{
						std::string text;
						unsigned int duration;
						unsigned int lastPos = lines.at(posLine).getTimings().size() - 1;
						text = "What's the time between " + lines.at(posLine).getBusStop(lastPos - 1) + " and " + lines.at(posLine).getBusStop(lastPos) + ": ";
						readNum(text.c_str(), duration, true);
					}

					else
					{
						std::string text;
						unsigned int duration1;
						text = "What's the time between " + lines.at(posLine).getBusStop(stopIndex - 1) + " and " + lines.at(posLine).getBusStop(stopIndex) + ": ";
						readNum(text.c_str(), duration1, true);

						unsigned int duration2;
						text = "What's the time between " + lines.at(posLine).getBusStop(stopIndex) + " and " + lines.at(posLine).getBusStop(stopIndex + 1) + ": ";
						readNum(text.c_str(), duration2, true);
					}

					break;
				}

				}

			} while (true);
		}


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
