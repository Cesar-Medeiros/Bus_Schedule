#include "Header.h"

void printCentered(std::ostream& out, const std::string info, const unsigned int sizew);
void printSchedule(const std::vector<Line> &lines, int posLine) {

	//A ultima passagem eve ocorrer se o valor de partida for menor que o valor de timeEnd. Não interessa
	//que o valor de chegada seja maior 
	//Algoritmo errado - Só funciona para uma paragem

	const uint timeStart = 8 * 60;
	const uint timeEnd = 20 * 60;


	uint timeFirstStop = timeStart;


	int oneLineTime = 0;
	for (uint i = 0; i < lines.at(posLine).getTimings().size(); i++) {
		oneLineTime += lines.at(posLine).getTiming(i);
	}

	//Quantas vigens sao possiveis concretizar a comecar pela primeira paragem
	//**
	int lineMaxNum = (timeEnd - timeStart - oneLineTime) / lines.at(posLine).getFreq();


	std::cout << "\n\n\t ID da linha = " << lines.at(posLine).getId() << "\n\n\t\t";

	//Visualizar o nome das paragens formatadas
	for (uint i = 0; i < lines.at(posLine).getBusStops().size(); i++) {
		printCentered(std::cout, lines.at(posLine).getBusStop(i), lines.at(posLine).getBusStop(i).length() + 4);
	}


	std::cout << "\n\t\t";


	for (uint i = 0; i < lines.at(posLine).getBusStops().size(); i++) {
		std::string formato(lines.at(posLine).getBusStop(i).length(), '-');
		printCentered(std::cout, formato, lines.at(posLine).getBusStop(i).length() + 4);
	}


	
	int acc;

	for (int i = 0; i < lineMaxNum; i++) {
		std::cout << std::endl;
		std::cout << "\t\t";
		acc = 0; // Acumulacao dos minutes das paragens
		for (uint i = 0; i < lines.at(posLine).getBusStops().size(); i++) {
			
			//Calcular hours e minutes
			uint minutes, hours, sizeW;

			hours = (timeFirstStop + acc) / 60;
			minutes = (timeFirstStop + acc) % 60;
			sizeW = lines.at(posLine).getBusStop(i).length() + 4;

			std::cout << Time(hours, minutes, sizeW);


			//Como nao existe nenhuma paragem a seguir a ultima paragem nao se acrescenta esse tempo
			if (i + 1 != lines.at(posLine).getBusStops().size())
				acc += lines.at(posLine).getTiming(i);

		}

		

		//Quando comeca a proxima viagem a comecar na primeira paragem
		timeFirstStop += lines.at(posLine).getFreq();
	}
}

