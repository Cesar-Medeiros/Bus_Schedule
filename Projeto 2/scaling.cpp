#include "Header.h"
#include <set>
#include <utility>

void driverVisualize(const Driver &driver);
int verifyShift(const Driver &driver, const Shift &shift, unsigned int &index);
<<<<<<< Updated upstream
void insertBusOrdered(std::vector<Bus> &bus, Bus busTemp);


=======
<<<<<<< Updated upstream
void writeShift(const std::multiset<Shift> shifts, std::string fileName);
bool verifyShift(const Driver &driver, const Shift &shift);
void imprimirHoras(uint time);
=======
<<<<<<< Updated upstream
void insertBusOrdered(std::vector<Bus> &bus, Bus busTemp);


=======
<<<<<<< Updated upstream
void writeShift(const std::multiset<Shift> shifts, std::string fileName);
bool verifyShift(const Driver &driver, const Shift &shift);
void imprimirHoras(uint time);
=======
void insertBusOrdered(std::vector<Bus> &bus, Bus busTemp);

using namespace std;
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes
>>>>>>> Stashed changes

unsigned int timeShift() {

	std::string dayName;
	unsigned int hour, min;

	unsigned int weekDay;
	bool invalidInput;
	do {
		invalidInput = false;
		char dots;
		std::cin >> dayName >> hour >> dots >> min;

		bool invalidDayName = false;


		if (dayName == "Seg")
			weekDay = 0;
		else if (dayName == "Ter")
			weekDay = 1;
		else if (dayName == "Qua")
			weekDay = 2;
		else if (dayName == "Qui")
			weekDay = 3;
		else if (dayName == "Sex")
			weekDay = 4;
		else if (dayName == "Sab")
			weekDay = 5;
		else if (dayName == "Dom")
			weekDay = 6;
		else weekDay = -1;


		if (std::cin.fail() || weekDay == -1 || hour >= 24 || min >= 60) {
			invalidInput = true;
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}

		if (invalidInput) {
			colorCout('!');
			std::cout << "Invalid Input\n\n";
		}

	} while (invalidInput);

	return weekDay * 24 * 60 + hour * 60 + min;
}

void addShift(Driver &driver, Bus &bus) {

	bool finish = false;

	unsigned int busLineId, busNumber;

	readNum("Introduza o numero da linha: ", busLineId);
	readNum("Introduza o numero do autocarro: ", busNumber);


	bus = Bus(busNumber, driver.getId(), busLineId);


	while (!finish) {

		
		colorCout('?');
		std::cout << "Introduza o tempo no formato Dia hh:mm (Ex: Seg 8:00): " << std::endl;

		std::cout << "Inicio do servico: " << std::endl;
		unsigned int startTime = timeShift();

		std::cout << "Fim do servico: " << std::endl;
		unsigned int endTime = timeShift();

		Shift shift(busLineId, driver.getId(), busNumber, startTime, endTime);

		uint indexInsertion;

		int errorCode = verifyShift(driver, shift, indexInsertion);

		switch (errorCode) {
		case 0:
			bus.insert(indexInsertion, shift);
			driver.insert(indexInsertion, shift);
			break;

		case 1:
			colorCout('!');
			std::cout << "Foi ultrapassada a duracao maxima de um turno" << std::endl;
			break;

		case 2:
			colorCout('!');
			std::cout << "Foram ultrapassadas as horas de trabalho maximas por semana" << std::endl;
			break;

		case 3:
			colorCout('!');
			std::cout << "Nao foi respeitado o tempo minimo de descanso entre turnos" << std::endl;
			break;
		case 4:
			colorCout('!');
			std::cout << "Tempo inicial do turno superior ao tempo final" << std::endl;
			break;
		}


		char answer;
		ask_YN("Deseja introduzir mais algum turno(S/N): ", answer);

		if (toupper(answer) == 'N')
			finish = true;

	}
}

void createShift(const std::string &driversFile, const std::string &busFile, std::vector<Driver> &drivers, std::vector<Bus> &bus) {


	unsigned int driverIndex = ask_TestID(drivers);

	if (driverIndex == -1) {

		char answer;
		ask_YN("Deseja adicionar um condutor(S / N) ? " , answer);

		if (toupper(answer) == 'N')
			return;

		else
			driverIndex = addDriver(driversFile, drivers);
	}

	Bus busTemp;

	//Turnos Existentes
	addShift(drivers.at(driverIndex), busTemp);


	//Inserir por ordem crescente os autocarros
	insertBusOrdered(bus, busTemp);

	//writeBus(bus, busFile); //Depois e' so' acrescentar um parametro com o nome do ficheiro de condutores

	driverVisualize(drivers.at(driverIndex));

}

int verifyShift(const Driver &driver, const Shift &shift, unsigned int &index) {

	int duration = (shift.getEndTime() - shift.getStartTime());
	
	if (duration < 0)
		return 4;

	else if (duration > driver.getMaxHours()*60)
		return 1;

	else if (duration > driver.getMaxWeekWorkingTime()*60) 
		return 2;

	else {
		unsigned int i = 0;
		index = i;
		for (i; i < driver.getShifts().size(); i++) {

			if (shift.getEndTime() + driver.getMinRestTime() * 60 < driver.getShifts().at(i).getStartTime()) {
				if (i == 0 || shift.getStartTime() > driver.getMinRestTime() + driver.getShifts().at(i - 1).getEndTime()) {
					index = i;
					return 0;
				}
			}

			if (i + 1 == driver.getShifts().size()) {
				if (shift.getStartTime() > driver.getShifts().at(i).getEndTime() + driver.getMinRestTime() * 60) {
					index = i + 1;
					return 0;
				}
				else return 3;
			}

			

		}


		return 0;

	}



}

int busesNeeded(const Line &line)
{
	//n = (int)((double)tempo_ida_e_volta / frequencia_dos_autocarros_na_linha + 1.0);
	int time = 0;
	for (int i = 0; i < line.getTimings().size(); i++)
	{
		time += line.getTimings().at(i);
	}
	time *= 2;
	//cout << "Tempo de ida e volta: " << time << endl;

	int buses = (int)((double)time / (line.getFreq() + 1.0));

	//cout << "Numero de autocarros: " << buses << endl;;

	std::vector<std::pair<int, int>> info;

	int begin = 0;

	/*for (int i = 0; i < buses; i++)
	{
		info.push_back(make_pair(i, begin));
	}*/
	/*
	for (int i = 0; i < info.size(); i++)
	{
	int hours = begin / 60;
	int minutes = begin - hours * 60;
	hours += 9;
	cout << i + 1 << " autocarro que sai às " << hours << ":" << minutes  << "chega passados " << time  << endl;
	begin += line.getFreq();
	}
	*/
	return buses;
}

bool operator<(Shift shift1, Shift shift2)
{
	if (shift1.getBusLineId() < shift2.getBusLineId()) return true;
	else return false;
}

std::multiset<Shift> createBlankShifts(std::vector<Line> &lines)
{
	std::multiset<Shift> shifts;
	for (int i = 0; i < lines.size(); i++)
	{
		int time = 0; //tempo total da linha
		for (int j = 0; j < lines.at(i).getTimings().size(); j++)
		{
			time += lines.at(i).getTimings().at(j);
		}

		time *= 2;

		int buses = busesNeeded(lines.at(i)); //numero de autocarros necessários
		int begin = 9 * 60;
		int end = begin + time;

		int busNumber = 1;

		while (begin != 23 * 60) //enquanto o tempo inicial é menor que 23h
		{
			Shift temp;
			temp.setBusLineId(lines.at(i).getId());
			temp.setBusOrderNumber(busNumber);
			temp.setDriverId(-1);
			temp.setStartTime(begin);
			temp.setEndTime(end);
			busNumber++;
			if (busNumber > buses ) busNumber = 1;
			begin += lines.at(i).getFreq();
			end += lines.at(i).getFreq();
			shifts.insert(temp);

		}
	}
<<<<<<< Updated upstream
	//std::cout << shifts.size() << std::endl;
	/*for (int i = 0; i < shifts.size(); i++)
=======
<<<<<<< Updated upstream
	std::cout << shifts.size() << std::endl;
=======
<<<<<<< Updated upstream
	//std::cout << shifts.size() << std::endl;
	/*for (int i = 0; i < shifts.size(); i++)
=======
	std::cout << shifts.size() << std::endl;
	return shifts;
}

<<<<<<< Updated upstream
void removeShift(std::vector<Shift> shifts, Shift shift)
{
	for (int i = 0; i < shifts.size(); i++)
	{
		if (shifts.at(i).getBusLineId() == shift.getBusLineId() && shifts.at(i).getBusOrderNumber() == shift.getBusOrderNumber() && shifts.at(i).getDriverId() == shift.getDriverId() && shifts.at(i).getEndTime() == shift.getEndTime() && shifts.at(i).getStartTime() == shift.getStartTime())
			shifts.erase(shifts.begin() + i);
	}
}




=======
//Dado um vetor de shifts elimina os shifts que já têm condutor
std::vector<Shift> removeShifts(std::vector<Shift> shifts)
{
	for (int i = 0; i < shifts.size(); i++)
	{
		if (shifts.at(i).getDriverId() != -1) shifts.erase(shifts.begin() + i);
	}
	return shifts;
}

>>>>>>> Stashed changes
//dado um vetor de shifts retorna um vetor de ints onde cada int são as linhas do vetor de shifts
vector<int> linesInShifts(vector<Shift> shifts)
{
	vector<int> lines;
	for (int i = 0; i < shifts.size(); i++)
	{
		bool add = true;
		for (int j = 0; j < lines.size(); j++)
		{
			if (shifts.at(i).getBusLineId() == lines.at(j)) add = false;
		}
		if (add) lines.push_back(shifts.at(i).getBusLineId());
	}
	return lines;
}

//Dado um vetor de shifts retorna uma vetor de shifts da linha especificada
vector<Shift> shiftsForLine(vector<Shift> shifts, int line)
{
	vector<Shift> lineShifts;

	for (int i = 0; i < shifts.size(); i++)
	{
		if (shifts.at(i).getBusLineId() == line) lineShifts.push_back(shifts.at(i));
	}
	return lineShifts;
}

//dado um vetor de shifts(de preferencia da mesma linha) retorna um vetor de shifts dessa linha de um determinado busNumber
vector<Shift> shiftsForBus(vector<Shift> shifts, int numberOfTheBus)
{
	vector<Shift> busShifts;
	for (int i = 0; i < shifts.size(); i++)
	{
		if (shifts.at(i).getBusOrderNumber() == numberOfTheBus) busShifts.push_back(shifts.at(i));
	}
	return busShifts;
}

//print de shifts formatado
void printFreeShifts(vector<Shift> freeShifts, int line, int numberOfBus)
{
	vector <pair <int, int>> tempos;

	int begin, end;

	for (int i = 0; i < freeShifts.size(); i++)
	{
		begin = freeShifts.at(i).getStartTime();
		end = freeShifts.at(i).getEndTime();
		tempos.push_back(make_pair(begin, end));
<<<<<<< Updated upstream

	}

	cout << "Autocarro " << numberOfBus << " da linha " << line << endl;
=======
		
	}

	cout << "Autocarro " << numberOfBus<< " da linha "<< line << endl;
>>>>>>> Stashed changes
	for (int i = 0; i < tempos.size(); i++)
	{
		begin = tempos.at(i).first;
		end = tempos.at(i).second;
		cout << begin << "---" << end << endl;
	}
}

<<<<<<< Updated upstream
/*//dado um mutiset de Shifts retorna um vetor de Shifts
=======
//dado um mutiset de Shifts retorna um vetor de Shifts
>>>>>>> Stashed changes
void freeBuses(std::multiset<Shift> shifts, int line, int numberOfBus)
{
	std::multiset<Shift>::iterator it;
	std::vector<Shift> shiftsV;
	for (it = shifts.begin(); it != shifts.end(); ++it)
	{
		shiftsV.push_back(*it);
	}
	vector<Shift> freeShifts = removeShifts(shiftsV);
	freeShifts = shiftsForLine(freeShifts, line);
	freeShifts = shiftsForBus(freeShifts, numberOfBus);
	printFreeShifts(freeShifts, line, numberOfBus);
	/*	for (int  i = 0; i < freeShifts.size(); i++ )
>>>>>>> Stashed changes
	{
<<<<<<< Updated upstream
	cout << "------------------------------------" << endl;
<<<<<<< Updated upstream
	cout << "Autocarro numero " << shifts.at(i).getBusOrderNumber() << endl;
	cout << "Linha numero" << shifts.at(i).getBusLineId() << endl;
	cout << "Conduzido pelo driver ID (-1 vazio)" << shifts.at(i).getDriverId() << endl;
	cout << "Inicio do turno " << shifts.at(i).getStartTime() << endl;
	cout << "Fim do turno " << shifts.at(i).getEndTime() << endl;
	cout << "------------------------------------" << endl;
	}*/
>>>>>>> Stashed changes
	return shifts;
}
=======
	cout << "Autocarro numero " << freeShifts.at(i).getBusOrderNumber() << endl;
	cout << "Linha numero" << freeShifts.at(i).getBusLineId() << endl;
	cout << "Conduzido pelo driver ID (-1 vazio)" << freeShifts.at(i).getDriverId() << endl;
	cout << "Inicio do turno " << freeShifts.at(i).getStartTime() << endl;
	cout << "Fim do turno " << freeShifts.at(i).getEndTime() << endl;
	cout << "------------------------------------" << endl;*/
	

=======
		cout << "------------------------------------" << endl;
		cout << "Autocarro numero " << freeShifts.at(i).getBusOrderNumber() << endl;
		cout << "Linha numero" << freeShifts.at(i).getBusLineId() << endl;
		cout << "Conduzido pelo driver ID (-1 vazio)" << freeShifts.at(i).getDriverId() << endl;
		cout << "Inicio do turno " << freeShifts.at(i).getStartTime() << endl;
		cout << "Fim do turno " << freeShifts.at(i).getEndTime() << endl;
		cout << "------------------------------------" << endl;
	}
	*/


}
>>>>>>> Stashed changes


>>>>>>> Stashed changes

void removeShift(std::vector<Shift> shifts, Shift shift)
{
	for (int i = 0; i < shifts.size(); i++)
	{
		if (shifts.at(i).getBusLineId() == shift.getBusLineId() && shifts.at(i).getBusOrderNumber() == shift.getBusOrderNumber() && shifts.at(i).getDriverId() == shift.getDriverId() && shifts.at(i).getEndTime() == shift.getEndTime() && shifts.at(i).getStartTime() == shift.getStartTime())
			shifts.erase(shifts.begin() + i);
	}
}




//dado um vetor de shifts retorna um vetor de ints onde cada int são as linhas do vetor de shifts
vector<int> linesInShifts(vector<Shift> shifts)
{
	vector<int> lines;
	for (int i = 0; i < shifts.size(); i++)
	{
		bool add = true;
		for (int j = 0; j < lines.size(); j++)
		{
			if (shifts.at(i).getBusLineId() == lines.at(j)) add = false;
		}
		if (add) lines.push_back(shifts.at(i).getBusLineId());
	}
	return lines;
}

//Dado um vetor de shifts retorna uma vetor de shifts da linha especificada
vector<Shift> shiftsForLine(vector<Shift> shifts, int line)
{
	vector<Shift> lineShifts;

	for (int i = 0; i < shifts.size(); i++)
	{
		if (shifts.at(i).getBusLineId() == line) lineShifts.push_back(shifts.at(i));
	}
	return lineShifts;
}

//dado um vetor de shifts(de preferencia da mesma linha) retorna um vetor de shifts dessa linha de um determinado busNumber
vector<Shift> shiftsForBus(vector<Shift> shifts, int numberOfTheBus)
{
	vector<Shift> busShifts;
	for (int i = 0; i < shifts.size(); i++)
	{
		if (shifts.at(i).getBusOrderNumber() == numberOfTheBus) busShifts.push_back(shifts.at(i));
	}
	return busShifts;
}

//print de shifts formatado
void printFreeShifts(vector<Shift> freeShifts, int line, int numberOfBus)
{
	vector <pair <int, int>> tempos;

	int begin, end;

	for (int i = 0; i < freeShifts.size(); i++)
	{
		begin = freeShifts.at(i).getStartTime();
		end = freeShifts.at(i).getEndTime();
		tempos.push_back(make_pair(begin, end));

	}

	cout << "Autocarro " << numberOfBus << " da linha " << line << endl;
	for (int i = 0; i < tempos.size(); i++)
	{
		begin = tempos.at(i).first;
		end = tempos.at(i).second;
		cout << begin << "---" << end << endl;
	}
}

/*//dado um mutiset de Shifts retorna um vetor de Shifts
void freeBuses(std::multiset<Shift> shifts, int line, int numberOfBus)
{
	std::multiset<Shift>::iterator it;
	std::vector<Shift> shiftsV;
	for (it = shifts.begin(); it != shifts.end(); ++it)
	{
		shiftsV.push_back(*it);
	}
	vector<Shift> freeShifts = removeShifts(shiftsV);
	freeShifts = shiftsForLine(freeShifts, line);
	freeShifts = shiftsForBus(freeShifts, numberOfBus);
	printFreeShifts(freeShifts, line, numberOfBus);
	/*	for (int  i = 0; i < freeShifts.size(); i++ )
>>>>>>> Stashed changes
	{
	cout << "------------------------------------" << endl;
	cout << "Autocarro numero " << shifts.at(i).getBusOrderNumber() << endl;
	cout << "Linha numero" << shifts.at(i).getBusLineId() << endl;
	cout << "Conduzido pelo driver ID (-1 vazio)" << shifts.at(i).getDriverId() << endl;
	cout << "Inicio do turno " << shifts.at(i).getStartTime() << endl;
	cout << "Fim do turno " << shifts.at(i).getEndTime() << endl;
	cout << "------------------------------------" << endl;
	}*/
	return shifts;
}

void deleteShift();
void editShift();