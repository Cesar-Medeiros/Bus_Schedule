#pragma once


//Bibliotecas
//*********************************************************
//#include <typeinfo>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>


#include "templateFunctions.cpp"
//*********************************************************


//Tipos de dados
//*********************************************************
typedef unsigned int uint;


#include "Bus.h"
#include "Company.h"
#include "Driver.h"
#include "Line.h"
#include "Shift.h"
#include "Time.h"
#include "BusTable.h"

//*********************************************************

//Prototipos funcoes
//*********************************************************************************************************



//Funcoes opcao - Menu principal

//**************************************************************************************************************
void menu(std::vector<Line> &lines, std::vector<Driver> &drivers, std::vector<Bus> &bus, const std::string &linesFile, const std::string &driversFile);

void openNotepad(std::vector<Line> &lines, std::string fileName);
void openNotepad(std::vector<Driver> &drivers, std::string fileName);
void openNotepad(std::string fileName);
char openFile(std::string fileName);

void colorCout(char symbol);
void readNum(const char coutText[], uint &num, bool displaySymbol = true);
int readOption();
int openFile(std::string linesFileName, std::string DriversFileName);
void readLines(std::vector<Line> &lines, std::string fileName);
void writeLines(const std::vector<Line> &lines, std::string fileName);

void readDrivers(std::vector<Driver> &drivers, std::string fileName);
void writeDrivers(const std::vector<Driver> &drivers, std::string fileName);

void linesManager(std::string fileName, std::vector<Line> &lines);

void driversManager(std::string fileName, std::vector<Driver> &drivers);

void visualizeInfo(const std::vector<Line> &lines, const std::vector<Driver> &drivers);

void timeBetweenStops(const std::vector<Line> &lines);

void createShift(const std::string &fileName, std::vector<Driver> &drivers, std::vector<Bus> &bus);

unsigned int addDriver(const std::string &fileName, std::vector<Driver> &drivers);//Repetido em alguns sitios do codigo

void readBus(std::vector<Driver> &drivers, std::vector<Bus> &bus, std::string fileName);

void writeBus(const std::vector<Bus> &bus, std::string fileName);



//Tratamento input utilizador
//**************************************************



//*********************************************************************************

