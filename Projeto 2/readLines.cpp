#include "Header.h"

//Acabar com espacos
//Acabar com new line

void readLines(std::vector<Line> &lines, std::string fileName) {

	std::fstream linesFile;
	linesFile.open(fileName, std::ios::in);

	linesFile.peek(); //Para posteriormente testar se e o ficheiro esta vazio

	while (!linesFile.eof()) { // <--- Com a condicao anterior a flag eof fica se o ficheiro estiver vazio 


		int id, freq;
		char comma;
		linesFile >> id >> comma >> freq >> comma;


		std::string busStopText;
		std::string timeText;
		
		//Paragens de uma determinada linha

		getline(linesFile, busStopText);

		if (busStopText.empty()) break;


		unsigned int semicolonPos = busStopText.find_last_of(';'); //posicao do ponto e virgula
		timeText = busStopText.substr(semicolonPos + 1); // A string timeText contem agora todos os tempos entre paragens
		busStopText = busStopText.substr(1, semicolonPos - 1); //A string busStopText contem agora todas as paragens ate ao ;
		

		unsigned int commaPos; //Posicao da primeira virgula que vai ser alterado ao longo do tempo

		



//Ciclo para o nome das Paragens
		std::vector <std::string> busStops;

		do {
			commaPos = busStopText.find_first_of(',');
			unsigned int poss = std::string::npos;
			std::string stopTemp = busStopText.substr(0, busStopText.find_first_of(','));

			stopTemp = stopTemp.substr(stopTemp.find_first_not_of(' '), stopTemp.find_last_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") + 1);

			busStopText = busStopText.substr(commaPos + 2);
			busStops.push_back(stopTemp);

		} while (commaPos != 4294967295);

		




//Ciclo para o tempo entre paragens
		std::vector<int> times;


		do{
			commaPos = timeText.find_first_of(',');
			std::string timeBetween = timeText.substr(0, timeText.find_first_of(','));
			timeText = timeText.substr(commaPos + 2);
			times.push_back(stoi(timeBetween));
		} while (commaPos != 4294967295);


//Gravar tudo no vetor lines
		Line line(id,freq, busStops, times);
		lines.push_back(line);
	}

	linesFile.close();
}