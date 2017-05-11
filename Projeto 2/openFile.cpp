#include "Header.h"

int openFile(std::string linesFileName, std::string DriversFileName) {

	char createNewFile = 'N';

	std::fstream linesFile(linesFileName);
	std::fstream driversFile(DriversFileName);

	bool linesFileFail = false;
	bool driversFileFail = false;


	if (!linesFile.is_open()) {
		colorCout('!');
		std::cout << "O ficheiro " << linesFileName << " nao existe." << std::endl;
		linesFileFail = true;

	}

	if (!driversFile.is_open()) {
		colorCout('!');
		std::cout << "O ficheiro " << DriversFileName << " nao existe." << std::endl;
		driversFileFail = true;
	}

	if (linesFileFail || driversFileFail) {
		do {
			colorCout('?');

			if (linesFileFail && driversFileFail)
				std::cout << "Deseja criar os ficheiros " << linesFileName << " e " << DriversFileName << " (S ou N)? ";

			else if (linesFileFail)
				std::cout << "Deseja criar o ficheiro " << linesFileName << " (S ou N)? ";

			else if (driversFileFail)
				std::cout << "Deseja criar o ficheiro " << DriversFileName << " (S ou N)? ";


			std::cin >> createNewFile;

			char conteudoBuffer;
			std::cin.get(conteudoBuffer);

			if (conteudoBuffer != '\n')
				createNewFile = 0;

			else createNewFile = toupper(createNewFile);

		} while (!(createNewFile == 'S' || createNewFile == 'N'));


		if (createNewFile == 'S')
		{
			if (linesFileFail) {
				std::ofstream linha_file(linesFileName);
				linha_file.close();
			}

			if (driversFileFail) {
				std::ofstream condutor_file(DriversFileName);
				condutor_file.close();
			}

		}

		else return 1;

	}

	return 0;
}