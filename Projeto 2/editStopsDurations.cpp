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

			std::vector<unsigned int> indexToChange;

			if (stopIndex == 0)
				indexToChange = { 0,1 };
			else if (stopIndex == lines.at(posLine).getBusStops().size() - 1)
				indexToChange = { stopIndex - 1, stopIndex };
			else
				indexToChange = { stopIndex - 1, stopIndex, stopIndex + 1 };


			for (unsigned int i = 0; i < indexToChange.size()-1; i++) {
				unsigned int i1 = indexToChange.at(0), i2 = indexToChange.at(1);
				std::string text;
				unsigned int duration;
				text = "What's the time between " + lines.at(posLine).getBusStop(i1) + " and " + lines.at(posLine).getBusStop(i2) + ": ";
				readNum(text.c_str(), duration, true);

			}

			break;
		}

		
		
		
		
		
		
		}

	} while (true);
	

}