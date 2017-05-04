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

	std::string linesFile, driversFile;
	std::vector<Line> line; //Vetor que contem todas as linhas existentes
	std::vector<Driver> driver;//Vetor que contem todos os condutores existente

	welcomeScreen();


	//Nome dos ficheiros
	/*
	colorCout('?');
	std::cout << "Introduza o nome do ficheiro de linhas (nome.txt): ";
	std::cin >> linesFile;
	colorCout('?');
	std::cout << "Introduza o nome do ficheiro de condutores (nome.txt): ";
	std::cin >> driversFile;
	std::cout << std::endl;
	*/

	linesFile = "linhas.txt";
	driversFile = "condutores.txt";



	//Se o ficheiro introduzido nao existe e o utilizador nao o quer criar - condicao é verdadeira


	if (openFile(linesFile, driversFile) == 1) {
		std::cout << std::endl;
		colorCout('!');
		std::cout << "O programa vai terminar.\n\n";
		exit(1);
	}
	//==============================================================================

	//Le os ficheiros para os respetivos vetores
	readLines(line, linesFile);
	readDrivers(driver, driversFile);



	menu(line, driver, linesFile, driversFile);



	//Tentar implementar - so escrever se o ficheiro for alterado(Ex: bool var global)

	writeLines(line, linesFile);
	writeDrivers(driver, driversFile);

	std::cout << std::endl;
	colorCout('*');
	std::cout << "A sair do programa! \n\n";


	return 0;
}

