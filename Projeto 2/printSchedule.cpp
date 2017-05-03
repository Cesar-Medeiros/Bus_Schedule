#include "Header.h"
void imprimirCentrado(std::string const &original, int targetSize);

void printSchedule(const std::vector<Line> &lines, int posLine) {
	//A ultima passagem eve ocorrer se o valor de partida for menor que o valor de timeEnd. Não interessa
	//que o valor de chegada seja maior 
	//Algoritmo errado - Só funciona para uma paragem

	const uint timeStart = 8 * 60;
	const uint timeEnd = 20 * 60;


	uint horasPrimeiraParagem = timeStart;


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
		imprimirCentrado(lines.at(posLine).getBusStop(i), lines.at(posLine).getBusStop(i).length() + 4);
	}


	std::cout << "\n\t\t";
	for (uint i = 0; i < lines.at(posLine).getBusStops().size(); i++) {

		std::string formato(lines.at(posLine).getBusStop(i).length(), '-');
		imprimirCentrado(formato, lines.at(posLine).getBusStop(i).length() + 4);
	}


	std::cout << std::endl;

	for (int i = 0; i < lineMaxNum; i++) {
		std::cout << "\t\t";
		int acc = 0; // Acumulacao dos minutes das paragens

		for (uint i = 0; i < lines.at(posLine).getBusStops().size(); i++) {

			//Calcular hours e minutes
			uint minutes, hours;
			std::string min_str, hour_str;

			minutes = (horasPrimeiraParagem + acc) % 60;
			hours = (horasPrimeiraParagem + acc) / 60;

			min_str = (minutes < 10) ? ("0" + std::to_string(minutes)) : std::to_string(minutes);
			hour_str = (hours < 10) ? ("0" + std::to_string(hours)) : std::to_string(hours);

			//Apresentar hours e minutes formatados e centrados		
			imprimirCentrado((hour_str + ":" + min_str), (lines.at(posLine).getBusStop(i).length() + 4));


			//Como nao existe nenhuma paragem a seguir a ultima paragem nao se acrescenta esse tempo
			if (i + 1 != lines.at(posLine).getBusStops().size())
				acc += lines.at(posLine).getTiming(i);


		}

		std::cout << std::endl;

		//Quando comeca a proxima viagem a comecar na primeira paragem
		horasPrimeiraParagem += lines.at(posLine).getFreq();
	}
}

void imprimirCentrado(std::string const &original, int targetSize) {

	int w = original.length();
	if (targetSize > w) {

		int delta = (targetSize - w) / 2;
		int desf = (targetSize - w) % 2;
		if (desf == 0)
			std::cout << std::string(delta, ' ') + original + std::string(delta, ' ');
		else std::cout << std::string(delta + 1, ' ') + original + std::string(delta, ' ');
	}

	else std::cout << original;
}