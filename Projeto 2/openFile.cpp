#include "Header.h"

int openFile(string linesFileName, string DriversFileName) {

	char createNewFile = 'N';

	fstream linesFile(linesFileName);
	fstream driversFile(DriversFileName);

	bool linesFileFail = false;
	bool driversFileFail = false;


	if (!linesFile.is_open()) {
		colorCout('!');
		cout << "O ficheiro " << linesFileName << " nao existe." << endl;
		linesFileFail = true;

	}

	if (!driversFile.is_open()) {
		colorCout('!');
		cout << "O ficheiro " << DriversFileName << " nao existe." << endl;
		driversFileFail = true;
	}

	if (linesFileFail || driversFileFail) {
		do {
			colorCout('?');

			if (linesFileFail && driversFileFail)
				cout << "Deseja criar os ficheiros " << linesFileName << " e " << DriversFileName << " (S ou N)? ";

			else if (linesFileFail)
				cout << "Deseja criar o ficheiro " << linesFileName << " (S ou N)? ";

			else if (driversFileFail)
				cout << "Deseja criar o ficheiro " << DriversFileName << " (S ou N)? ";


			cin >> createNewFile;

			char conteudoBuffer;
			cin.get(conteudoBuffer);

			if (conteudoBuffer != '\n')
				createNewFile = 0;

			else createNewFile = toupper(createNewFile);

		} while (!(createNewFile == 'S' || createNewFile == 'N'));


		if (createNewFile == 'S')
		{
			if (linesFileFail) {
				ofstream linha_file(linesFileName);
				linha_file.close();
			}

			if (driversFileFail) {
				ofstream condutor_file(DriversFileName);
				condutor_file.close();
			}

		}

		else return 1;

	}

	return 0;
}