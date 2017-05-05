#include "Header.h"

void openNotepad(std::vector<Line> &lines, std::string fileName) {

	writeLines(lines, fileName);
	std::string programa = "notepad " + fileName;
	char * cstring = new char[programa.length() + 1];
	strcpy_s(cstring, programa.length() + 1, programa.c_str());
	system(cstring);
	lines.clear();
	readLines(lines, fileName);
}

void openNotepad(std::vector<Driver> &drivers, std::string fileName) {
	writeDrivers(drivers, fileName);
	
	std::string programa = "notepad " + fileName;
	char * cstring = new char[programa.length() + 1];
	strcpy_s(cstring, programa.length() + 1, programa.c_str());
	
	system(cstring);
	drivers.clear();
	readDrivers(drivers, fileName);
}

void openNotepad(std::string fileName) {
	std::string programa = "notepad " + fileName;
	char * cstring = new char[programa.length() + 1];
	strcpy_s(cstring, programa.length() + 1, programa.c_str());
	system(cstring);
}

char openFile(std::string fileName) {

	char openFile;

	do {
		colorCout('?');
		std::cout << "Abrir o ficheiro (S ou N)? ";
		std::cin >> openFile;

		char bufferContent; //Se o utilizador introduzir mais que um carater -> Input invalio
		std::cin.get(bufferContent);

		if (std::cin.fail() || bufferContent != '\n') {
			std::cin.clear();
			std::cin.ignore(1000, '\n'); //Se falhar ignora o resto dos carateres.
			openFile = 0;
		}


	} while (toupper(openFile) != 'S' && toupper(openFile) != 'N');

	return toupper(openFile);
}