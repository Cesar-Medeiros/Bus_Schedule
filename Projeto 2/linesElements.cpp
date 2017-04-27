#include "Header.h"


void insertBusStops(Line &line) {

	std::string busStop;
	std::vector<string> busStopList;

	std::cout << std::endl;
	colorCout('?');
	std::cout << "Introduza as paragens (ENTER para terminar): \n";

	do {
		std::cout << "--> ";
		getline(std::cin, busStop);

		if (busStop != "")
			busStopList.push_back(busStop);
	} while (busStop != "");

	line.setBusStops(busStopList);

}

//Se changed = true entao a funcao esta a ser chamada pela opcao changed linha;
//Se changed = false a funcao esta a ser chamada pela opcao acrescentar linha;
void insertTime(Line &line) {

	std::vector<int> timeList;
	
	/*
	if (changed)
		line.paragensTempo.erase(line.paragensTempo.begin(), line.paragensTempo.end());
	*/

	for (uint i = 0; i < line.getBusStops().size()-1; i++) {

		uint time;
		std::cout << std::endl;
		colorCout('?');
		std::cout << "Introduza o tempo entre " << line.getBusStop(i) << " e " << line.getBusStop(i+1) << ": " << std::endl;
		readNum("--> ", time, false);
		timeList.push_back(time);
	}

	line.setTimings(timeList);
}



