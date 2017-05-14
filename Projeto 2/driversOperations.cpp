#include "Header.h"


unsigned int addDriver(const std::string &fileName, std::vector<Driver> &drivers) {
	
	
	std::string name;
	unsigned int maxHours, maxWeekWorkingTime, minRestTime;
	

	unsigned int id = readID(drivers);

	colorCout('?');
	std::cout << "Introduza o nome do condutor: \n";
	std::cout << "--> ";

	getline(std::cin, name);


	
	colorCout('?');
	std::cout << "Introduza a duracao de cada turno: \n";
	readNum("--> ", maxHours, false);


	
	colorCout('?');
	std::cout << "Introduza o numero maximo de horas que pode conduzir por semana: \n";
	readNum("--> ", maxWeekWorkingTime, false);


	
	colorCout('?');
	std::cout << "Introduza o numero de horas minimo de descanso entre turnos: \n";
	readNum("--> ", minRestTime, false);



	Driver driver(id, name, maxHours, maxWeekWorkingTime, minRestTime);

	//Defenir a ordem onde vai ser colocado o condutor
	
	unsigned int index = sortID(driver, drivers);


	
	colorCout('*');
	std::cout << "Condutor adicionado com sucesso ao ficheiro " << fileName << std::endl;

	return index;
}

void changeDriver(const std::string &fileName, std::vector<Driver> &drivers) {


	
	
	int posDriver = ask_TestID(drivers); //Tentar perguntar Insira o ID do condutor;

	if (posDriver == -1) return;

	std::cout << "\n\n|         Editar condutor        |\n";
	std::cout << "|--------------------------------|\n";
	std::cout << "| (1) ID                         |\n";
	std::cout << "| (2) Nome                       |\n";
	std::cout << "| (3) Duracao do turno           |\n";
	std::cout << "| (4) Maximo de horas por semana |\n";
	std::cout << "| (5) Tempo minimo de descanso   |\n";
	std::cout << "| (0) Voltar Gerir condutor      |\n\n";

	bool validNumber;

	do {

		validNumber = true;

		int option = readOption(); //Le a opcao e faz os devidos testes para prevenir input invalido


		switch (option)
		{

		case 0: //Unica maneira de sair
			return;

		case 1: {
			unsigned int id = readID(drivers);
			drivers.at(posDriver).setId(id);
			sortID(drivers); //Cria nova na posicao correta
			break;
		}


		case 2:
		{
			std::string name;
			colorCout('?');
			
			std::cout << "Introduza o nome do condutor: \n";
			std::cout << "--> ";
			getline(std::cin, name);
			drivers.at(posDriver).setName(name);
			break;
		}


		case 3: {
			unsigned int maxHours;
			
			readNum("Introduza a duracao de cada turno: ", maxHours, true);
			drivers.at(posDriver).setMaxHours(maxHours);
			break;
		}


		case 4:{
			unsigned int maxWeekWorkingTime;
			
			readNum("Introduza o numero maximo de horas que pode conduzir por semana: ", maxWeekWorkingTime, true);
			drivers.at(posDriver).setMaxWeekWorkingTime(maxWeekWorkingTime);
			break;
		}


		case 5: {
			unsigned int minRestTime;
			
			readNum("Introduza o numero de horas minimo de descanso entre turnos: ", minRestTime, true);
			drivers.at(posDriver).setMinRestTime(minRestTime);
			break;
		}

		default:
			validNumber = false;
			break;
		}

	} while (!validNumber);

	
	colorCout('*');
	std::cout << "Condutor alterado com sucesso no ficheiro " << fileName << std::endl;
}

void removeDriver(const std::string &fileName, std::vector<Driver> &drivers) {

	int pos = ask_TestID(drivers); //Devolve a posicao da linha atraves da introducao do id ou devolve -1 se nao encontrar 

	if (pos != -1) {
		drivers.erase(drivers.begin() + pos);
		
		colorCout('*');
		std::cout << "Condutor removido com sucesso ao ficheiro " << fileName << std::endl;
	}
	else {
		
		colorCout('!');
		std::cout << "Nao foi possivel eliminar o condutor." << std::endl;
	}

}