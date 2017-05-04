#include "Header.h"

struct stopInfo {
	int posLine;
	int posBusStop;
	int timeUntilStop;
};


void printStopSchedule(const std::vector<Line> &lines) {

	std::string busStopName;
	colorCout('?');
	std::cout << "Introduza o nome de uma paragem: ";
	getline(std::cin, busStopName);



	std::vector <stopInfo> stopInfoList;

	//1o - Pesquisar as posiçoes da lines onde se encontra a busStopName e conta o time ate ela no mesmo ciclo
	//2o Apresentar todos os horarios nessa lines somando ao horario inicial o time calculado e depois a frequencia



	for (uint i = 0; i < lines.size(); i++) {
		uint time = 0;

		for (uint j = 0; j < lines.at(i).getBusStops().size(); j++) {

			stopInfo posicoesTemp;


			if (busStopName == lines.at(i).getBusStop(j)) {

				posicoesTemp.posLine = i;
				posicoesTemp.posBusStop = j;
				posicoesTemp.timeUntilStop = time;
				stopInfoList.push_back(posicoesTemp);

				//Se encontrar uma busStopName numa determinada lines quebra o ciclo e vai pesquisar noutra
				break;
			}

			if (j + 1 != lines.at(i).getBusStops().size())
				time += lines.at(i).getTiming(j);
		}
	}

	if(stopInfoList.size() == 0){
		std::cout << std::endl;
		colorCout('!');
		std::cout << "Nao foi possivel encontrar a paragem " << busStopName << " !" << std::endl;
		return;
	}



	//Imprime "Paragem busStopName"
	const char a = 186;
	std::cout << "\n\n\t" << (char)201 << std::string(busStopName.length() + 8, 205) << (char)187 << "\n";
	std::cout << "\t" << a<<"Paragem " << busStopName <<a<< std::endl;
	std::cout << "\t" << (char)200 << std::string(busStopName.length() + 8, 205) << (char)188 << "\n";


	//Horario de abertura e fecho da empresa de autocarros
	const uint timeStart = 8 * 60;
	const uint timeEnd = 20 * 60;


	//Imprimir o horario

	for (uint i = 0; i < stopInfoList.size(); i++) {

		Line line = lines.at(stopInfoList.at(i).posLine);
		std::cout << "\n\n Linha " << line.getId() << std::endl;

		std::cout << "\n Sentido: " << line.getBusStop(line.getBusStops().size() - 1) << "\n\n";


		uint iterationNum = (timeEnd - timeStart) / line.getFreq();

		uint timeOneWay = timeStart + stopInfoList.at(i).timeUntilStop;
		uint timeReturn = timeStart + 2 * line.timeLine() - stopInfoList.at(i).timeUntilStop;


		while (timeOneWay - stopInfoList.at(i).timeUntilStop < timeEnd) {
			std::cout << Time(timeOneWay / 60, timeOneWay % 60, 8);
			timeOneWay += line.getFreq();
		}

		std::cout << "\n\n Sentido: " << line.getBusStop(0) << "\n\n";

		while (timeReturn + stopInfoList.at(i).timeUntilStop - line.timeLine() < timeEnd) {
			std::cout << Time(timeReturn / 60, timeReturn % 60, 8);
			timeReturn += line.getFreq();
		}


		std::cout << "\n\n";
	}

}

