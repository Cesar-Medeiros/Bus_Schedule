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

