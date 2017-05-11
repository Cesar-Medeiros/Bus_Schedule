#include "Header.h"
void searchBusStop(const std::vector<Line> &lines) {

	std::string busStopName;
	colorCout('?');
	std::cout << "Introduza o nome da paragem que deseja procurar: ";
	getline(std::cin, busStopName);

	std::vector<int> idLineList;

	for (uint i = 0; i < lines.size(); i++) {

		for (uint j = 0; j < lines.at(i).getBusStops().size(); j++) {

			if (busStopName == lines.at(i).getBusStop(j)) {
				idLineList.push_back(lines.at(i).getId());
				break;
			}
		}
	}
	if (idLineList.size() == 0) {
		colorCout('!');
		std::cout << "Nao foram encontradas paragens com nome: " << busStopName << std::endl;
	}

	else {

		std::cout << "\nA paragem " << busStopName << " esta presente nas linhas com ID: ";

		for (uint i = 0; i < idLineList.size(); i++) {

			if (i + 1 != idLineList.size())
				std::cout << idLineList.at(i) << " e ";
			else
				std::cout << idLineList.at(i) << std::endl << std::endl;
		}
	}

}

void showLine(const std::vector<Line> &lines) {

	int posLine = ask_TestID(lines);

	if (posLine != -1) {
		std::cout << "\n\t\t ID = " << lines.at(posLine).getId() << std::endl;
		std::cout << "\n\t\t Frequencia = " << lines.at(posLine).getFreq() << " minutos" << "\n\n\t\t ";

		for (uint i = 0; i < lines.at(posLine).getBusStops().size(); i++) {
			std::cout << lines.at(posLine).getBusStop(i);
			if (i + 1 != lines.at(posLine).getBusStops().size())
				std::cout << "   <-->   " << lines.at(posLine).getTiming(i) << " minutos   <-->   ";

		}
	}
}

void printCentered(std::ostream& out, const std::string info, const unsigned int sizew) {

	unsigned int w = info.length();
	if (sizew > w) {

		int delta = (sizew - w) / 2;
		int desf = (sizew - w) % 2;
		if (desf == 0)
			out << std::string(delta, ' ') + info + std::string(delta, ' ');
		else out << std::string(delta + 1, ' ') + info + std::string(delta, ' ');
	}
	else out << info;
}


void imprimirHoras(uint time) {
	uint weekDay = time / (24 * 60);
	uint hour = (time % (24 * 60)) / 60;
	uint min = (time % (24 * 60)) % 60;
	std::string text;
	switch (weekDay) {
	case 0: text = "Seg"; break;
	case 1: text = "Ter"; break;
	case 2: text = "Qua"; break;
	case 3: text = "Qui"; break;
	case 4: text = "Sex"; break;
	case 5: text = "Sab"; break;
	case 6: text = "Dom"; break;
	}
	std::cout << text << ", ";
	std::cout << Time(hour, min, 5) << std::endl;

}


void driverVisualize(const Driver &driver)
{


	std::cout << "Id: " << driver.getId() << std::endl;
	std::cout << "Name: " << driver.getName() << std::endl;
	std::cout << "Duração maxima de um turno: " << driver.getMaxHours() << std::endl;
	std::cout << "Tempo minimo de descanso entre turnos: " << driver.getMinRestTime() << std::endl;
	std::cout << "Tempo restante por semana: " << driver.getMaxWeekWorkingTime() << std::endl; //Criar novo atributo
	std::cout << std::endl;

	std::cout << "Turnos existentes: " << std::endl;


	for (uint i = 0; i < driver.getShifts().size(); i++) {
		uint startTime = driver.getShifts().at(i).getStartTime();
		uint endTime = driver.getShifts().at(i).getEndTime();

		std::cout << "Inicio do turno: ";
		imprimirHoras(startTime);

		std::cout << "Fim do turno: ";
		imprimirHoras(endTime);
		std::cout << std::endl;
	}


}