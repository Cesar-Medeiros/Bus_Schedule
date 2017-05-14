#include "Header.h"
#include <windows.h>

/**
Projeto 2 - Semprarrolar

Objetivo versao 1.0: Gerir linhas e condutores de uma empresa de autocarros
Objetivo versao 2.0: Escalonamento dos condutores da empresa

@author Cesar Medeiros, Duarte Frazão
@version 2.0 12/05/17
*/

void welcomeScreen();

int main() {

	

	std::string linesFile, driversFile, busFile;
	welcomeScreen();


	//Nome dos ficheiros
	/*
	colorCout('?');
	std::cout << "Introduza o nome do ficheiro de linhas (nome.txt): ";
	std::cin >> linesFile;
	colorCout('?');
	std::cout << "Introduza o nome do ficheiro de condutores (nome.txt): ";
	std::cin >> driversFile;
	
	colorCout('?');
	std::cout << "Introduza o nome do ficheiro de autocarros (nome.txt): ";
	std::cin >> busFile;
	
	*/

	linesFile = "linhas.txt";
	driversFile = "condutores.txt";
	busFile = "bus.txt";

	Company company(std::string("Semprarrolar"), driversFile, linesFile, busFile);
	
	std::vector<Line> *lines = company.pointerLines();
	std::vector<Driver> *drivers = company.pointerDrivers();
	std::vector<Bus> *bus = company.pointerBus();


	//Se o ficheiro introduzido nao existe e o utilizador nao o quer criar - condicao é verdadeira


	if (openFile(linesFile, driversFile) == 1) {
		
		colorCout('!');
		std::cout << "O programa vai terminar.\n\n";
		exit(1);
	}
	//==============================================================================

	//Le os ficheiros para os respetivos vetores
	readLines(*lines, linesFile);
	readDrivers(*drivers, driversFile);
	readBus(*drivers, *bus, busFile);

	menu(*lines, *drivers, *bus, linesFile, driversFile, busFile);



	//Tentar implementar - so escrever se o ficheiro for alterado(Ex: bool var global)

	writeLines(*lines, linesFile);
	writeDrivers(*drivers, driversFile);

	
	colorCout('*');
	std::cout << "A sair do programa! \n\n";


	return 0;
}

