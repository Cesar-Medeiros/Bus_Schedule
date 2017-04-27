#include "Header.h"

void writeLines(const std::vector<Line> &lines, std::string fileName) {

	std::fstream linesFile;
	linesFile.open(fileName, std::ios_base::out);

	for (uint i = 0; i < lines.size(); i++) {

		linesFile << lines.at(i).getId() << " ; " << lines.at(i).getFreq() << " ; ";

		for (unsigned int j = 0; j < lines.at(i).getBusStops().size(); j++)
			linesFile << lines.at(i).getBusStop(j) << ((j + 1 != lines.at(i).getBusStops().size()) ? ", " : "; ");

		for (uint j = 0; j < lines.at(i).getTimings().size(); j++)
			linesFile << lines.at(i).getTiming(j) << ((j + 1 != lines.at(i).getTimings().size()) ? ", " : "");

		linesFile << std::endl;
	}

	linesFile.close();
}