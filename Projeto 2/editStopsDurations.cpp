#include "Header.h"

void editStopsDurations(std::vector<Line> &lines, unsigned int posLine) {

	do {
		std::cout << "\n\n|              Stops/Durations              |\n";
		std::cout << "|-------------------------------------------|\n";
		std::cout << "|     (1)  Change a stop                    |\n";
		std::cout << "|     (2)  Correct a duration between stops |\n";
		std::cout << "|     (3)  Change every stop/duration       |\n";
		std::cout << "|     (0)  Go back                          |\n\n";

		int option = readOption();

		switch (option) {


		case 0: 
			return;

		case 1:
		{	
			std::cout << std::endl;
			for (unsigned int i = 0; i < lines.at(posLine).getBusStops().size(); i++)
				std::cout << "Stop " << i + 1 << ": " << lines.at(posLine).getBusStop(i) << std::endl;
			std::cout << std::endl;


			//New stop
			unsigned int stopIndex;
			std::string name;

			do {
				readNum("Select the one to change: ", stopIndex, true);
				stopIndex--;
			} while (stopIndex < 0 || stopIndex >= lines.at(posLine).getBusStops().size());


			colorCout('?');
			std::cout << "Insira o nome da paragem : ";
			std::cin >> name;
			
			lines.at(posLine).setBusStops(name, stopIndex);

			//Correct the durations based on the new location



			std::vector<unsigned int> indexToChange;

			if (stopIndex == 0)
				indexToChange = { 0,1 };
			else if (stopIndex == lines.at(posLine).getBusStops().size() - 1)
				indexToChange = { stopIndex - 1, stopIndex };
			else
				indexToChange = { stopIndex - 1, stopIndex, stopIndex + 1 };


			for (unsigned int i = 0; i < indexToChange.size()-1; i++) {
				unsigned int i1 = indexToChange.at(i), i2 = indexToChange.at(i+1);
				std::string text;
				unsigned int duration;
				text = "What's the time between " + lines.at(posLine).getBusStop(i1) + " and " + lines.at(posLine).getBusStop(i2) + ": ";
				readNum(text.c_str(), duration, true);
				lines.at(posLine).setTimings(duration, i1);
			}

			break;
		}

		case 2:
		{
			std::cout << std::endl;
			for (unsigned int i = 0; i < lines.at(posLine).getTimings().size(); i++)
				std::cout << "Time " << i + 1 << ": " << lines.at(posLine).getTiming(i) << std::endl;
			std::cout << std::endl;

			unsigned int timeIndex;
			do {
				readNum("Select the one to change: ", timeIndex, true);
				timeIndex--;
			} while (timeIndex < 0 || timeIndex >= lines.at(posLine).getTimings().size());

			unsigned int time;
			readNum("New time: ", time);

			lines.at(posLine).setTimings(time, timeIndex);

			break;

		}
		
		case 3:
			colorCout('?');
			std::cout << "Insert new Bus Stops: " << std::endl << std::endl;
			
			std::string busStop;
			std::vector <std::string> busStopList;

			while (std::cout << " --> ", getline(std::cin, busStop), busStop != "") {
				busStopList.push_back(busStop);
			}
		
			lines.at(posLine).setBusStops(busStopList);


			std::vector <int> timeList;

			for (unsigned int i = 0; i < lines.at(posLine).getBusStops().size()-1; i++) {
				std::string text;
				unsigned int duration;
				text = "What's the time between " + lines.at(posLine).getBusStop(i) + " and " + lines.at(posLine).getBusStop(i+1) + ": ";
				readNum(text.c_str(), duration, true);
				timeList.push_back(duration);
			}

			lines.at(posLine).setTimings(timeList);
			break;
		}

	} while (true);
	

}