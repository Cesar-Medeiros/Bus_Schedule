#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
//teste
//alteração teste

using namespace std;

struct driverType
{
	int identifier;
	string name;
	int maximumHoursDay;
	int maximumHoursWeek;
	int minimumRestHours;
};

struct lineType
{
	int identifier;
	int frequency;
	vector <string> stops;
	vector <int> duration;
};


void manageDrivers();
int mainMenu();
void viewInfo();
int inputFiltered(int limi, int lims);
void addDriver();
void addLine();
bool existentLine(int code); 
void manageLines();
void removeLine();
int existentLineCode(int code);
int numberOfLines();
int driverLine(int code);
void removeDriver();
void editDriver();
int numberOfDrivers();
bool existentDriver(int code);
bool existentDriverBool(int code);
string lastDriverCode();
driverType extractDriver(int code);
bool existentLineBool(int code);
lineType extractLine(int code);
void editLine();
void stopSchedule();
void routeBetweenStops();
void lineSchedule();
void driversNecessaryForLine();
void availableDrivers();
void linesWithStop();


//main function
int main()
{
	ifstream lines, drivers;
	lines.open("lines.txt");
	drivers.open("drivers.txt");

	//to test if there's an error in file
	if (lines.fail())
	{
		cout << "Erro" << endl;
		exit(1);
	}


	if (drivers.fail())
	{
		cout << "Não foi possível encontrar ficheiro dos condutores" << endl;
		exit(1);
	}

	lines.close();
	drivers.close();
	

	bool continueInMenu = true;

	do
	{
		int chooseMenu = mainMenu();


		switch (chooseMenu)
		{
		case 0:
			continueInMenu = false;
			break;
		case 1:
			manageLines();
			break;
		case 2:
			manageDrivers();
			break;
		case 3:
			viewInfo();
			break;
		default:
			cout << "Algum erro";
			break;
		}
	} while (continueInMenu);



	

	system("CLS");

	cout << "Thank you!\Semprearrolar!\n";


	return 0;
}

//mainMenu function
int mainMenu()
{

	cout << "O que quer fazer?\n";
	cout << "Selecione o numero correspondente\n\n";

	vector<string> menu = { "1 - Gestao de linhas", "2 - Gestão de condutores", "3 - Visualizar informacao", "0 - Sair do menu\n" };

	for (int i = 0; i < menu.size(); i++)
	{
		cout << menu[i] << endl;
	}

	int option = inputFiltered(0, 3);

	return option;
}

//manageLines function
void manageLines()
{
	

	bool continueMenu = true;

	while (continueMenu)
	{

		cout << "What do you want to do?\n\n";

		vector <string> menu = { "1- Add a line", "2- Edit a line's information", "3- Remove a line","0- Go back to the main menu\n" };

		for (int i = 0; i < menu.size(); i++)
		{
			cout << menu[i] << endl;
		}

		int option = inputFiltered(0, 3);
		switch (option)
		{
		case 1:
		{
			addLine();
			break;
		}
		case 2:
		{
			editLine();
			break;
		}
		case 3:
		{
			removeLine();
			break;
		}
		case 0:
		{
			continueMenu = false;
			break;
		}
		default:
		{
			cout << "Insira um´número válido\n";
			break;
		}
		}
	}
}

//manageDrivers function
void manageDrivers()
{
	////http://www.cplusplus.com/forum/general/37333/


	bool continueMenu = true;

	while (continueMenu)
	{
		cout << "What do you want to do?\n\n";

		vector <string> menu = { "1- Add a driver", "2- Edit a driver's profile", "3- Remove a driver","0- Go back to the main menu\n" };

		for (int i = 0; i < menu.size(); i++)
		{
			cout << menu[i] << endl;
		}

		int option = inputFiltered(0, 3);

		switch (option)
		{
		case 1:
		{
			addDriver();
			break;
		}
		case 2:
		{
			editDriver();
			break;
		}
		case 3:
		{
			removeDriver();
			break;
		}
		case 0:
		{
			continueMenu = false;
			break;
		}
		default:
		{
			cout << "Insira um´número válido\n";
			break;
		}
		}
	}

}


//viewInfo function
void viewInfo()
{
	
	bool continueMenu = true;

	while (continueMenu)
	{
		cout << "What do you want to do?\n\n";

		vector <string> menu = { "1- Route and times between any two stops", "2- Calculate the number of drivers necessary for a specific line", "3- Visualize a stop schedule","4- Visualize a line schedule", "5- Available drivers ","6- Lines with specific stop ", "0- Go back to the main menu\n" };

		for (int i = 0; i < menu.size(); i++)
		{
			cout << menu[i] << endl;
		}

		int option = inputFiltered(0, 6);

		switch (option)
		{
		case 1:
		{
			routeBetweenStops();
			break;
		}
		case 2:
		{
			driversNecessaryForLine();
			break;
		}
		case 3:
		{
			stopSchedule();
			break;
		}
		case 4:
		{
			lineSchedule();
			break;
		}
		case 5:
		{
			availableDrivers();
			break;
		}
		case 6:
		{
			linesWithStop();
			break;
		}
		case 0:
		{
			continueMenu = false;
			break;
		}
		default:
		{
			cout << "Insira um número válido\n";
			break;
		}
		}
	}
}

//stopSchedule
void stopSchedule()  
{
	ifstream lines;
	lines.open("lines.txt");

	string lineFromFile;
	lineType line;
	int lineNumber;

	string stop;

	cout << "Insert the stop you wish to see the schedule" << endl;
	cin >> stop;

	bool existsStopInFile = false;

	while (getline(lines, lineFromFile))
	{
		stringstream ss;

		ss << lineFromFile;
		ss >> lineNumber;

		line = extractLine(lineNumber);


		for (int i = 0; i< line.stops.size();i++)
		{
			int hours, minutes;
			if (line.stops[i] == stop)
			{
				existsStopInFile = true;
				hours = 9;
				minutes = 0;
				cout << endl << "Schedule for the stop " << stop << " for line " << line.identifier << endl << endl;
				while (hours < 19)
				{
					cout << setw(2) << setfill('0') << hours << ":";
					cout << setw(2) << setfill('0') << minutes << "\t";
					minutes += line.frequency;
					if (minutes >= 60)
					{
						minutes -= 60;
						hours++;
					}
				}
				break;
			}
		}


	}
	cout << "\n\n";
	if (!existsStopInFile) cout << "Stop wasn't found in any line" << endl;
}

//routeBetweenStops
void routeBetweenStops()
{
	ifstream lines;
	lines.open("lines.txt");

	string lineFromFile;
	lineType line;
	int lineNumber;

	string stopBegin, stopEnd;

	cin.clear();
	cin.ignore(256, '\n');

	cout << "Insert the departure stop" << endl;
	getline(cin, stopBegin);

	cout << "Insert the destination stop" << endl;
	getline(cin, stopEnd);

	bool existsPath = false;

	while (getline(lines, lineFromFile))
	{
		stringstream ss;

		ss << lineFromFile;
		ss >> lineNumber;

		line = extractLine(lineNumber);

		int timeBetweenStops = 0;

		bool isBetweenDesiredStops = false;

		for (int i = 0; i < line.stops.size(); i++)
		{
			if (line.stops[i] == stopBegin) isBetweenDesiredStops = true;
			if (line.stops[i] == stopEnd ) isBetweenDesiredStops = false;
			if (i == line.duration.size()  && isBetweenDesiredStops)
			{
				isBetweenDesiredStops = false;
				timeBetweenStops = 0;

			}
			else if (isBetweenDesiredStops) timeBetweenStops += line.duration[i];
		}

		if (timeBetweenStops != 0)
		{
			cout << "On line " << lineNumber << " the time between " << stopBegin << " and " << stopEnd << " is " << timeBetweenStops << endl;
			existsPath = true;
		}
		


	}
	cout << "\n\n";
	if (!existsPath) cout << "No path between the selected stops found" << endl;
}

//lineSchedule
void lineSchedule()
{
	ifstream lines;
	lines.open("lines.txt");

	string lineFromFile;
	lineType line;
	int lineCode;

	cout << "What's the line you wish to see the schedule? " << endl;
	cin >> lineCode;

	while (getline(lines, lineFromFile))
	{
		stringstream ss;
		int lineNumber;

		ss << lineFromFile;
		ss >> lineNumber;

		line = extractLine(lineNumber);

		if (lineCode == lineNumber)
		{
			int hours = 9;
			int minutes = 0;

			for (int i = 0; i < line.stops.size(); i++) cout << setw(20)<< line.stops[i] << "\t" ;	     
			cout << endl;



			while (hours < 19)
			{
				cout << "\t" << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes ;
				for (int i = 0; i < line.duration.size(); i++)
				{	
					minutes += line.duration[i];
					while (minutes >= 60)
					{
						minutes -= 60;
						hours++;
					}
					cout << "\t\t\t" << setw(2) << setfill('0') << hours << ":";
					cout << setw(2) << setfill('0') << minutes;
				} 
				cout << endl;
				
			}
			cout << endl;
		}
	}
}

//driversNecessaryForLine
void driversNecessaryForLine()
{
	ifstream lines;
	lines.open("lines.txt");

	string lineFromFile;
	lineType line;
	int lineCode;

	cout << "What's the line you wish check how many drivers it needs? " << endl;
	cin >> lineCode;

	while (getline(lines, lineFromFile))
	{
		stringstream ss;
		int lineNumber;

		ss << lineFromFile;
		ss >> lineNumber;

		line = extractLine(lineNumber);

		int time = 0;

		for (int i = 0; i < line.duration.size(); i++) time += line.duration[i];

		if (lineNumber == lineCode)
		{
			int driversNecessary = time/45;
			
			if (driversNecessary == 0) driversNecessary++;

			cout << "Assuming a driver can only drive for 90 min, line " << lineNumber << " will need " << driversNecessary << " drivers" << endl << endl;
		}
		
	}
}

//availableDrivers()
void availableDrivers()
{
	ifstream drivers;
	drivers.open("drivers.txt");

	driverType driver;
	int driverCode;
	string lineFromFile;


	while (getline(drivers, lineFromFile))
	{
		stringstream ss;
		int driverNumber;

		ss << lineFromFile;
		ss >> driverNumber;

		driver = extractDriver(driverNumber);

		cout << "Driver " << driver.identifier << " - " <<  driver.name << endl;

	}
}

//linesWithStop
void linesWithStop()
{
	ifstream lines;
	lines.open("lines.txt");

	string lineFromFile;
	lineType line;
	int lineCode;
	string desiredStop;

	cout << "What's the stop you with to check? " << endl;

	cin.clear();
	cin.ignore(256, '\n');
	getline(cin, desiredStop);

	bool anyLine = false;

	while (getline(lines, lineFromFile))
	{
		stringstream ss;
		int lineNumber;

		ss << lineFromFile;
		ss >> lineNumber;

		line = extractLine(lineNumber);

		for (int i = 0; i < line.stops.size(); i++)
		{
			if (line.stops[i] == desiredStop)
			{
				anyLine = true;
				cout << "The stop exists at line " << lineNumber << endl;
			}
		}

		
	}
	if (anyLine == false) cout << "The stop doesn't exist on any line" << endl;
}


//////////////////Add lines

//addLine //feito
void addLine()
{
	ofstream lines;
	lines.open("lines.txt", ios::app);

	string newLine;
	int identifier, frequency;
	vector <string> stops;
	vector <int> duration;


	cout << "What's the line number you wish to enter? " << endl;
	do
	{
		identifier = inputFiltered(0,10000);
	}while (existentLine(identifier));

	cout << "What's the frequency for that line? " << endl;
	frequency = inputFiltered(1, 24 * 60);
	
	cout << "Type the stops, to pass to the next one hit enter, to finish type 0" << endl;

	//stops
	string temp = "1";
	cin.ignore(256, '\n');
	do
	{
		getline(cin, temp);
		if (temp == "0") break;
		stops.push_back(temp);
	}while (true);

	//stops schedule
	int time;
	for (int i = 0; i < (stops.size() - 1); i++)
	{
		cout << "Time beetwen " << stops[i] << " and " << stops[i + 1] << endl;
		time = inputFiltered(1, 24 * 60);
		duration.push_back(time);
	}

	//putting params of a line to string stream
	//and after that writing them to the file

	stringstream ss;
	ss << "\n" << identifier << " ; " << frequency << " ;";
	for (int i = 0; i < stops.size(); i++)
	{
		if (i< (stops.size() -1)) ss << " " << stops[i] << ",";
		else ss << " " << stops[i];
	}

	ss << ";";
	for (int i = 0; i < duration.size(); i++)
	{
		if (i< (duration.size() - 1)) ss << " " << duration[i] << ",";
		else ss << " " << duration[i];
	}

	lines << ss.str();

	cout << "Line: " << identifier << " was added sucessfully." << endl;

	lines.close();
}

//existentLine
bool existentLine(int code)
{
	int fileCode;
	string line;
	ifstream lines;
	stringstream ss;
	lines.open("lines.txt");
	while (getline(lines, line))
	{
		ss << line;
		ss >> fileCode;	//Extracts the line number as an int
		if (fileCode == code)
		{
			char answer;

			cout << "The line already exists, do you wish to overwrite it? (y/n)" << endl;

			do
				cin >> answer;
			while (answer != 'y' && answer != 'n');

			if (answer == 'y') cout << "falta fazer a função que leva o numero indentificador e elimina uma linha" << endl;

			cout << "What's the line number you wish to enter? " << endl;

			lines.close();
			return true;
		}
	}
	lines.close();
	return false;
}

//////////////////Remove Lines

//removeLine feito
void removeLine()
{
	string line, tempLine;

	int code, numberLine;

	ifstream lines;
	lines.open("lines.txt");

	cout << "What's the line you wish to remove?" << endl;
	
	cin >> code;

	numberLine = existentLineCode(code);  //line that user wants to remove, -1 if it doesn't exist


	int count = 0;

	int linesInFile = numberOfLines();

	if (numberLine == -1) cout << "That line doesn't exist" << endl;

	else
	{
		ofstream temp;
		temp.open("temp.txt");

		while (getline(lines, tempLine))
		{

			if (count != numberLine)
			{
				if (count == (linesInFile - 1)) temp << tempLine;
				else
				{
					tempLine += "\n";
					temp << tempLine;
				}
			}
			count++;
		}


		temp.close();
		lines.close();
		remove("lines.txt");
		rename("temp.txt", "lines.txt");
	}

	lines.close();
}

//numberOfLines 
int numberOfLines()
{
	string line;
	ifstream lines;
	lines.open("lines.txt");

	int count = 0;

	while (getline(lines, line)) count++;

	return count;
}

//existentLineCode     It works as expected, however the function existentLine() might need to be added another line, a line to clear the stringstream 
int existentLineCode(int code)
{
	int fileCode, lineNumber, lineCounter;
	string line;
	ifstream lines;
	stringstream ss;
	lines.open("lines.txt");

	lineNumber = -1; //if it doesn't find the line with that code it will return -1
	lineCounter = 0;

	while (getline(lines, line))
	{
		ss.str("");
		ss << line;
		ss >> fileCode;   //Extracts the line number as an int
		if (fileCode == code)
		{
			lineNumber = lineCounter;
			lines.close();
			return lineNumber;
		}
		lineCounter++;
	}
	lines.close();
	return lineNumber;
} 


///////////////////Edit Lines

void editLine()
{
	int identifier;

	do
	{
		cout << "What's the line's unique identifier you wish to edit?" << endl;
		identifier = inputFiltered(0, 1000);
	} while (!existentLineBool(identifier));

	int lineToRemove = existentLineCode(identifier);

	lineType busLine;

	if (lineToRemove != -1)
	{
		busLine = extractLine(identifier);

		bool continueEditing = true;

		int option;

		while (continueEditing)
		{

			cout << "Identifier- " << busLine.identifier << endl;
			cout << "Frequency- " << busLine.frequency << endl;
			for (int i = 0; i < busLine.stops.size(); i++) cout << "Stop " << i << "--" << busLine.stops[i] << endl;
			for (int i = 0; i < busLine.duration.size(); i++) cout << "Duration " << i << "--" << busLine.duration[i] << endl;

			cout << "What do you want to edit?" << endl;

			vector <string> menu = { "1- Unique Identifier", "2- Frequency of circulation", "3- Stops and time between stops", "0- Go back\n" };

			for (int i = 0; i < menu.size(); i++)
			{
				cout << menu[i] << endl;
			}

			int option = inputFiltered(0, 4);

			switch (option)
			{
			case 1:
			{
				int id;

				do
				{
					cout << "Please insert a new valid identifier: " << endl;
					id = inputFiltered(0, 1000);
				} while (existentLineBool(id));

				busLine.identifier = id;

				cout << "Unique identifier sucessfully changed" << endl;
				break;

			}

			case 2:
			{
				cout << "What's the new frequency of circulation? " << endl;
				int newFrequency;

				do
					cin >> newFrequency;
				while (cin.fail());

				busLine.frequency = newFrequency;

				cout << "Frequency of circulation sucessfully changed" << endl;
				break;
			}

			case 3:
			{
				cout << "what do you want to change?" << endl;
				cout << "0- Nothing" << endl;
				cout << "1- Change a stop" << endl;
				cout << "2- Correct a duration between stops" << endl;
				cout << "3- Change every stop/duration" << endl;


				int opt = inputFiltered(0, busLine.stops.size() - 1);

				switch (opt)
				{
					case 1:
					{
						cout << "Select the one to change" << endl;
						for (int i = 0; i < busLine.stops.size(); i++) cout << "Stop " << i+1 << "--" << busLine.stops[i] << endl;

						//New stop
						int stopC = inputFiltered(1, busLine.stops.size());
						stopC--;

						do
						{
							cin.ignore(256, '\n');
							cout << "insert the new stop" << endl;
							getline(cin, busLine.stops[stopC]);
						}
						while (cin.fail());


						//Correct the durations based on the new location
						if (stopC == 0)
						{
							do
							{
								cout << "What's the time between " << busLine.stops[stopC] << " and " << busLine.stops[stopC + 1] << endl;
								cin >> busLine.duration[stopC];
							} while (cin.fail());
						}
						else if (stopC == busLine.duration.size())
						{
							do
							{
								int tempDuration;
								cout << "What's the time between " << busLine.stops[stopC - 1] << " and " << busLine.stops[stopC] << endl;
								cin >> tempDuration;
								busLine.duration[stopC- 1] = tempDuration;
							} while (cin.fail());

						}
						else
						{
							do
							{
								int tempDuration;
								cout << "What's the time between " << busLine.stops[stopC- 1] << " and " << busLine.stops[stopC ] << endl;
								cin >> tempDuration;
								busLine.duration[stopC - 1] = tempDuration;
							} while (cin.fail());

							do
							{
								cout << "What's the time between " << busLine.stops[stopC] << " and " << busLine.stops[stopC + 1] << endl;
								cin >> busLine.duration[stopC];
							} while (cin.fail());
						}
						
						break;
					}
					case 2:
					{

						for (int i = 0; i < busLine.stops.size(); i++) cout << i+1 <<"Time between " << busLine.stops[i] << " and " << busLine.stops[i+1] << " --- " <<  busLine.duration[i] << endl;
						int stopC = inputFiltered(1, busLine.stops.size());
						stopC--;

						int tempDuration = inputFiltered(1,10000);

						busLine.stops[stopC] = tempDuration;

						break;
					}
					case 3:
					{
						cout << "Insert 0 if you want to exit" << endl << endl;
						vector <string> newStops;
						string tempStop;

						while (cin >> tempStop)
						{
							if (tempStop == "0") break;
							newStops.push_back(tempStop);
						}

						busLine.stops = newStops;
						break;
					}
				

				}
				break;

			}
			case 0:
			{
				continueEditing = false;
				break;
			}
			}
		}
		//write to the file new data


		ofstream temp;
		temp.open("temp.txt");

		ifstream lines;
		lines.open("lines.txt");

		string lineFromFile;

		int count = 0;
		int numLines = numberOfLines();

		stringstream ss;

		while (getline(lines, lineFromFile))
		{
			if (count == lineToRemove)
			{
				ss.str("");
				string lineString;
				ss << busLine.identifier << " ; " << busLine.frequency << " ; ";
				for (int i = 0; i < busLine.stops.size(); i++)
				{
					if (i == busLine.stops.size() - 1) ss << busLine.stops[i] << "; ";
					else ss << busLine.stops[i] << " , ";
				}

				for (int i = 0; i < busLine.duration.size(); i++)
				{
					if (i == busLine.duration.size() - 1) ss << busLine.duration[i];
					else ss << busLine.duration[i] << ", ";
				}
				

				if (count != numLines - 1) ss << "\n";

				lineString = ss.str();

				temp << lineString;
			}
			else
			{
				if (count != numLines - 1) lineFromFile += "\n";
				temp << lineFromFile;
			}
			count++;
		}

		lines.close();
		temp.close();
		remove("lines.txt");
		rename("temp.txt", "lines.txt");
	}
}

bool existentLineBool(int code)
{
	int fileCode;
	string line;
	ifstream lines;
	stringstream ss;
	lines.open("lines.txt");
	while (getline(lines, line))
	{
		ss << line;
		ss >> fileCode;	//Extracts the line number as an int
		if (fileCode == code)
		{
			lines.close();
			return true;
		}
	}
	lines.close();
	return false;
}


lineType extractLine(int code)
{
	lineType busLine;
	string line;

	ifstream lines;
	lines.open("lines.txt");

	int count = 0;

	stringstream ss;

	while (getline(lines, line))
	{
		int schedule;
		ss.str("");
		ss << line;
		ss >> busLine.identifier;

		if (busLine.identifier == code)
		{
			string temp = ss.str();
			ss.str("");

			int pos;

			pos = temp.find(";");
			temp = temp.substr(pos + 1);


			pos = temp.find(";");
			ss << temp.substr(1, pos - 1);
			ss >> busLine.frequency;
			temp = temp.substr(pos + 1);

			//Stops extraction

			vector <string> stops;
			string tempStop;

			while (temp.find(",") <= temp.find(";"))
			{
				stringstream ss2;
				pos = temp.find(",");
				tempStop = temp.substr(1, pos - 1);
				stops.push_back(tempStop);
				temp = temp.substr(pos +1);
			}
			
			pos = temp.find(";");
			tempStop = temp.substr(1, pos - 1);
			stops.push_back(tempStop);
			temp = temp.substr(pos + 1);

			busLine.stops = stops;

			//Time between stops extraction

			vector <int> time;
			int tempTime;

			while (temp.find(",") < string::npos)
			{
				stringstream ss2;
				pos = temp.find(",");
				ss2 << temp.substr(1, pos - 1);
				ss2 >> tempTime;
				time.push_back(tempTime);
				temp = temp.substr(pos + 1);
			}
			ss << temp;
			ss >> tempTime;
			time.push_back(tempTime);

			busLine.duration = time;

			lines.close();
			return busLine;

		}

	}
}


////////////////////Add Drivers 

//addDriver  //feito
void addDriver()
{
	string newDriver;
	int code;

	//Reading driver details from user input
	ifstream drivers;
	drivers.open("drivers.txt");

	stringstream ss;
	int param1, param2, param3;
	
	cout << "What's the driver's identifier?" << endl;

	do
	{
		code = inputFiltered(0,1000);
	} while (existentDriver(code));

	cout << "Insert driver's name" << endl;
	cin.ignore(256, '\n');
	getline(cin, newDriver);
	cout << "Insert the 3 params" << endl;

	param1 = inputFiltered(0, 1000);
	param2 = inputFiltered(0, 1000);
	param3 = inputFiltered(0, 1000);
	if (numberOfDrivers() == 0) ss << code << " ; " << newDriver << "; " << param1 << "; " << param2 << "; " << param3;
	else
	ss << "\n" <<code << " ; " << newDriver << "; " << param1 << "; " << param2 << "; " << param3 ;
	newDriver = ss.str();
	cout << newDriver << endl;
	drivers.close();


	//Writing driver details
	ofstream driversO;

	driversO.open("drivers.txt", ios::app);

	driversO << newDriver;

	driversO.close();
}

//lastDriverCode
string lastDriverCode()
{
	ifstream drivers;
	drivers.open("drivers.txt");

	int count = 1;
	 
	string driver, returnString;
	stringstream ss;
	while (getline(drivers, driver)) count++;
	//char code=  driver[0] - '0'; //to return the number and not the ascii code, old version
	ss << count;
	ss >> returnString;

	drivers.close();

	return returnString;
}

//existentDriver
bool existentDriver(int code)
{
	int fileCode;
	string driver;
	ifstream drivers;
	stringstream ss;
	drivers.open("drivers.txt");
	while (getline(drivers, driver))
	{
		ss.str("");
		ss << driver;
		ss >> fileCode;	//Extracts the line number as an int
		if (fileCode == code)
		{
			char answer;

			cout << "The driver already exists, do you wish to overwrite it? (y/n)" << endl;

			do
				cin >> answer;
			while (answer != 'y' && answer != 'n');

			if (answer == 'y') cout << "falta fazer a função que leva o numero indentificador e elimina uma linha" << endl;

			cout << "What's the driver identifier you wish to enter? " << endl;

			drivers.close();
			return true;
		}
	}
	drivers.close();
	return false;
}

//////////////////Remove Drivers working

//removeDriver
void removeDriver()
{
	string driver, tempDriver;

	ifstream drivers;

	drivers.open("drivers.txt");


	
	cout << "What's the code of the driver you wish to remove?" << endl;

	int driverToRemove;

	int numDrivers = numberOfDrivers();

	cin >> driverToRemove;

	int lineToRemove = driverLine(driverToRemove);

	int count = 0;

	if (lineToRemove == -1)
	{
		cout << "That driver doesn't exist" << endl;
		drivers.close();
	}
	else
	{
		ofstream temp;
		temp.open("temp.txt");

		while (getline(drivers, tempDriver))
		{

			if (count != lineToRemove)
			{
				if (count == (numDrivers - 1)) temp << tempDriver;
				else
				{
					tempDriver += "\n";
					temp << tempDriver;
				}
			}
			count++;
		}
		drivers.close();
		temp.close();
		remove("drivers.txt");
		rename("temp.txt", "drivers.txt");
		cout << "The driver with the code " << driverToRemove << " was removed sucessfully!" << endl;
	}
}

//numberOfDrivers ainda é usada?
int numberOfDrivers()
{
	string driver;

	ifstream drivers;
	drivers.open("drivers.txt");

	int count = 0;

	while (getline(drivers, driver)) count++;

	return count;
}

//driverLine()
int driverLine(int code)
{
	int fileCode, lineNumber, lineCounter;
	string driver;
	ifstream drivers;
	stringstream ss;
	drivers.open("drivers.txt");

	lineNumber = -1; //if it doesn't find the driver with that code it will return -1
	lineCounter = 0;

	while (getline(drivers, driver))
	{
		ss.str("");
		ss << driver;
		ss >> fileCode;   //Extracts the line number as an int
		if (fileCode == code)
		{
			lineNumber = lineCounter;
			drivers.close();
			return lineNumber;
		}
		lineCounter++;
	}
	drivers.close();
	return lineNumber;
}


//////////////////Edit Drivers

void editDriver()
{
	int identifier;

	do
	{
		cout << "What's the driver's code you wish to edit?" << endl;
		identifier = inputFiltered(0, 1000);
	}
	while (!existentDriverBool(identifier));

	int lineToRemove = driverLine(identifier);

	driverType driver;

	if (lineToRemove != -1)
	{
		driver = extractDriver(identifier);

		bool continueEditing = true;

		

		while (continueEditing)
		{
			cout << "What do you want to edit?" << endl;

			vector <string> menu = { "1- Unique Identifier", "2- Name", "3- Maximum number of hours per day", "4- Maximum number of hours per week", "5- Minimum rest hours", "0- Go back\n" };

			for (int i = 0; i < menu.size(); i++)
			{
				cout << menu[i] << endl;
			}

			int option = inputFiltered(0, 5);

			switch (option)
			{
			case 1:
			{
				int id;

				do
				{
					cout << "Please insert a new valid identifier: " << endl;
					id = inputFiltered(0, 1000);
				}
				while (existentDriverBool(id));

				driver.identifier = id;

				cout << "Unique identifier sucessfully changed" << endl;
				break;

			}

			case 2:
			{
				cout << "What's the new driver's name? " << endl;
				string name;

				do
				cin >> name;
				while (cin.fail());

				driver.name = name;

				cout << "Driver's name sucessfully changed" << endl;
				break;
			}

			case 3:
			{
				cout << "What's the new maximum number of hours per day? " << endl;
				int mh;

				mh = inputFiltered(0, 1000);

				driver.maximumHoursDay = mh;

				cout << "Maximum number of hours per day sucessfully changed" << endl;
				break;
			}

			case 4:
			{
				cout << "What's the new maximum number of hours per week? " << endl;
				int mh;

				mh = inputFiltered(0, 1000);

				driver.maximumHoursWeek = mh;

				cout << "Maximum number of hours per week sucessfully changed" << endl;
				break;
			}

			case 5:
			{
				cout << "What's the new minimum rest hours for the driver? " << endl;
				int mh;

				mh = inputFiltered(0, 1000);

				driver.minimumRestHours = mh;

				cout << "Minimum number of rest hours sucessfully changed" << endl;
				break;
			}

			case 0:
			{
				continueEditing = false;
				break;
			}
			}
		}

		//write to the file new data


		ofstream temp;
		temp.open("temp.txt");

		ifstream drivers;
		drivers.open("drivers.txt");

		string line;

		int count = 0;
		int numDrivers = numberOfDrivers();

		stringstream ss;

		while (getline(drivers, line))
		{
			if (count == lineToRemove)
			{
				ss.str("");
				string driverString;
				ss<< driver.identifier << " ; " << driver.name << " ; " << driver.maximumHoursDay << " ; " << driver.maximumHoursWeek << " ; " << driver.minimumRestHours;
				if (count != numDrivers - 1) ss << "\n";

				driverString = ss.str();

				temp << driverString;
			}
			else
			{
				if (count != numDrivers - 1) line += "\n";
				temp << line;
			}
			count++;
		}

		drivers.close();
		temp.close();
		remove("drivers.txt");
		rename("temp.txt", "drivers.txt");
		
	}
	



}
bool existentDriverBool(int code)
{
	int fileCode;
	string driver;
	ifstream drivers;
	stringstream ss;
	drivers.open("drivers.txt");
	while (getline(drivers, driver))
	{
		ss.str("");
		ss << driver;
		ss >> fileCode;	//Extracts the line number as an int
		if (fileCode == code)
		{
			drivers.close();
			return true;
		}
	}
	drivers.close();
	return false;
}

driverType extractDriver(int code)
{
	driverType driver;
	string line;

	ifstream drivers;
	drivers.open("drivers.txt");

	int count = 0;

	char trash;

	stringstream ss;
	
	while (getline(drivers, line))
	{
		int schedule;
		ss.str("");
		ss << line;
		ss >> driver.identifier;

		if (driver.identifier == code)
		{
			string temp = ss.str();
			ss.str("");
			int pos;

			pos = temp.find(";");
			temp = temp.substr(pos + 1);

			pos = temp.find(";");
			driver.name = temp.substr(1, pos-2);
			temp = temp.substr(pos +1);

			pos = temp.find(";");
			ss << temp.substr(1, pos-1);
			ss >> driver.maximumHoursDay;
			temp = temp.substr(pos + 1);

			pos = temp.find(";");
			ss << temp.substr(1, pos - 1);
			ss >> driver.maximumHoursWeek;
			temp = temp.substr(pos + 1);

			ss << temp;
			ss >> driver.minimumRestHours;

			drivers.close();
			return driver;
				
		}

	}
}

///////////////////Auxiliary funtions

//inputFiltered function, takes two limits and inputs an integer in that interval, checking for user mistakes
int inputFiltered(int limi, int lims)
{
	int option;
	bool validValue = true;
	do
	{
		cin >> option;
		if (cin.fail() || option < limi || option> lims )
		{
			cout << "Please enter a valid value\n";
			cin.clear();
			cin.ignore(100, '\n');
			validValue = false;
		}
		else if (validValue == false) validValue = true;

	} while (!validValue);

	return option;
}





