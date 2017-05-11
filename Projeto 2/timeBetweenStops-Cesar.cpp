#include "Header.h"
#include <utility>

class stopInfo {
public:
	unsigned int posLine;
	unsigned int posBusStop;
	unsigned int timeUntilStop;

	stopInfo(unsigned int posLine, unsigned int posBusStop, unsigned int timeUntilStop) {

		this->posLine = posLine;
		this->posBusStop = posBusStop;
		this->timeUntilStop = timeUntilStop;

	}

};

std::vector<stopInfo> searchStops(const std::vector<Line> &lines, std::string busStopName) {

	std::vector<stopInfo> returnValue;
	uint time;

	for (uint i = 0; i < lines.size(); i++) {
		time = 0;

		for (uint j = 0; j < lines.at(i).getBusStops().size(); j++)
		{

			if (j != lines.at(i).getTimings().size())
				time += lines.at(i).getTiming(j);

			if (lines.at(i).getBusStop(j) == busStopName) {
				returnValue.push_back(stopInfo(i, j, time));
			}
		}
	}

	return returnValue;
}

std::vector<std::pair<uint, uint>> commonElements(const std::vector<Line> &lines, unsigned int firstLineIndex, unsigned int lastLineIndex) {
	std::vector<std::pair<uint, uint>> commonElements;

	for (unsigned int i = 0; i < lines.at(firstLineIndex).getBusStops().size(); i++) {
		std::string stopName = lines.at(firstLineIndex).getBusStop(i);

		for (unsigned int j = 0; j < lines.at(lastLineIndex).getBusStops().size(); j++) {

			if (stopName == lines.at(lastLineIndex).getBusStop(j))
				commonElements.push_back(std::pair<uint, uint>(i, j));
		}
	}

	return commonElements;
}

uint timeInOneLine(Line line, uint posOne, uint posTwo) { //Ter atencao que pos

	if (posOne > posTwo) {
		uint temp = posTwo;
		posTwo = posOne;
		posOne = temp;

	}

	uint time = 0;

	for (uint i = posOne; i < posTwo;i++)
		time += line.getTiming(i);

	return time;
}

void timeBetweenStops(const std::vector<Line> &lines) {
	std::string busStopName1, busStopName2;
	
	colorCout('?');
	std::cout << "Introduza o nome da 1 paragem? ";
	getline(std::cin, busStopName1);
	
	std::vector<stopInfo> firstStopList = searchStops(lines, busStopName1);


	std::cout << std::endl;

	if (firstStopList.empty()) {
		colorCout('!');
		std::cout << "Nao existe nenhuma paragem com o nome " << busStopName1;
		return;
	}


	colorCout('?');
	std::cout << "Introduza o nome da 2 paragem? ";
	getline(std::cin, busStopName2);


	std::vector<stopInfo> lastStopList = searchStops(lines, busStopName2);
	if (lastStopList.empty()) {
		colorCout('!');
		std::cout << "Nao existe nenhuma paragem com o nome " << busStopName2;
		return;
	}



	uint time = -1;

	for (uint i = 0; i < firstStopList.size(); i++) {
		for (uint j = 0; j < lastStopList.size(); j++) {

			std::vector<std::pair<uint, uint>> commonBusStops = commonElements(lines, firstStopList.at(i).posLine, lastStopList.at(j).posLine);

			for (uint k = 0; k < commonBusStops.size(); k++) {

				uint timeTemp = timeInOneLine(lines.at(firstStopList.at(i).posLine), firstStopList.at(i).posBusStop, commonBusStops.at(k).first);
				timeTemp += timeInOneLine(lines.at(lastStopList.at(j).posLine), lastStopList.at(j).posBusStop, commonBusStops.at(k).second);

				if (timeTemp < time)
					time = timeTemp;
			}

		}

	}

	if (time == -1) {
		colorCout('!');
		std::cout << "Nao encontrou nenhuma ligacao entre " << busStopName1 << " e " << busStopName2 << std::endl;
	}

	else{
		colorCout('*');
		std::cout << "O tempo entre a paragem " << busStopName1 << " e " << busStopName2 << " e' de " << time/60 << " horas e " << time%60 << " minutos " << std::endl;
	}
}

