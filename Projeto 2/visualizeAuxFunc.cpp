#include "Header.h"


void searchBusStop(const std::vector<Line> &lines) {

	std::string busStopName;
	colorCout('?');
	std::cout << "Introduza o nome da paragem que deseja procurar: ";
	getline(std::cin, busStopName);

	std::vector<int> idLineList;

	for (uint i = 0; i < lines.size(); i++) {

		for (uint j = 0; j < lines.at(i).getBusStops().size(); j++) {

			if (busStopName == lines.at(i).getBusStop(j)) {
				idLineList.push_back(lines.at(i).getId());
				break;
			}
		}
	}
	if (idLineList.size() == 0) {
		colorCout('!');
		std::cout << "Nao foram encontradas paragens com nome: " << busStopName << std::endl;
	}

	else {

		std::cout << "\nA paragem " << busStopName << " esta presente nas linhas com ID: ";

		for (uint i = 0; i < idLineList.size(); i++) {

			if (i + 1 != idLineList.size())
				std::cout << idLineList.at(i) << " e ";
			else
				std::cout << idLineList.at(i) << std::endl << std::endl;
		}
	}

}

void showLine(const std::vector<Line> &lines) {

	int posLine = ask_TestID(lines);

	if (posLine != -1) {
		std::cout << "\n\t\t ID = " << lines.at(posLine).getId() << std::endl;
		std::cout << "\n\t\t Frequencia = " << lines.at(posLine).getFreq() << " minutos" << "\n\n\t\t ";

		for (uint i = 0; i < lines.at(posLine).getBusStops().size(); i++) {
			std::cout << lines.at(posLine).getBusStop(i);
			if (i + 1 != lines.at(posLine).getBusStops().size())
				std::cout << "   <-->   " << lines.at(posLine).getTiming(i) << " minutos   <-->   ";

		}
	}
}

/*
std::vector<par> posicaoParagem(const std::vector<Line> &lines, std::string stopName)
{
	std::vector<par> listaID;

	for (uint i = 0; i < lines.size(); i++) {

		for (uint j = 0; j < lines.at(i).getBusStops().size(); j++) {
			if (lines.at(i).getBusStop(j) == stopName) {
				par par;
				par.linha1 = i;
				par.posicao1 = j;
				listaID.push_back(par);
				break; //Encontra 1 elemento igual
			}

		}

	}

return listaID;
}

//Pergunta o nome de duas paragens, verifica se estao na mesma lines e se isso se verificar devolve o tempo entre paragens
void tempoEntreParagens(const std::vector<Line> &lines) {


	std::string paragem1, paragem2;

	std::cout << "Insira o nome da primeira busStopName: ";
	getline(std::cin, paragem1);

	std::cout << "Insira o nome da segunda busStopName: ";
	getline(std::cin, paragem2);

	std::vector<par> paragem1LinhasID = posicaoParagem(lines, paragem1);
	std::vector<par> paragem2LinhasID = posicaoParagem(lines, paragem2);
	std::vector<par> linhasComum;

	for (uint i = 0; i < paragem1LinhasID.size(); i++) {

		for (uint j = 0; j < paragem2LinhasID.size(); j++) {

			if (paragem1LinhasID.at(i).linha1 == paragem2LinhasID.at(j).linha1) {


				//Tentar por mais legivel
				if (paragem1LinhasID.at(i).posicao1 < paragem2LinhasID.at(j).posicao1)
					paragem1LinhasID.at(i).posicao2 = paragem2LinhasID.at(j).posicao1;

				else {
					paragem1LinhasID.at(i).posicao2 = paragem1LinhasID.at(i).posicao1;
					paragem1LinhasID.at(i).posicao1 = paragem2LinhasID.at(j).posicao1; //Aproveitar estrutura 1 para colocar os id de ambas as paragens;
				}

				linhasComum.push_back(paragem1LinhasID.at(i));
				break;

			}

		}
	}


	for (uint i = 0; i < linhasComum.size(); i++) {

		int tempo = 0;

		for (uint j = linhasComum.at(i).posicao1; j < linhasComum.at(i).posicao2; j++) {
			tempo += lines.at(linhasComum.at(i).linha1).getTiming(j);
		}
		linhasComum.at(i).tempo = tempo;

	}
	if (linhasComum.size() == 0) {
		colorCout('!');
		std::cout << "As paragens introduzidas nao se encontram na mesma lines";
	}

	else
	{
		std::cout << "\nTempo entre " << paragem1 << " e " << paragem2 << " = ";

		for (uint i = 0; i < linhasComum.size(); i++) {

			std::cout << "Linha " << linhasComum.at(i).linha1 << ": ";
			std::cout << linhasComum.at(i).tempo << " minutos." << std::endl;
		}

	}


	//linhasComum.at(0).tempo; //Alterar, criar algoritmo para dar o menor tempo;
}
*/

void printCentered(std::ostream& out, const std::string info, const unsigned int sizew) {

	int w = info.length();
	if (sizew > w) {

		int delta = (sizew - w) / 2;
		int desf = (sizew - w) % 2;
		if (desf == 0)
			out << std::string(delta, ' ') + info + std::string(delta, ' ');
		else out << std::string(delta + 1, ' ') + info + std::string(delta, ' ');
	}
	else out << info;
}


struct stopInfo {
	int posLine;
	int posBusStop;
	int timeUntilStop;
};

bool timeBetStopsAux(const std::vector<Line> &lines, const std::string stopName, std::vector<stopInfo> stopInfo, unsigned int index, bool something);

void timeBetweenStops(const std::vector<Line> &lines) {
	std::string busStopName1, busStopName2;

	std::cout << "Introduza o nome da 1 paragem?";
	getline(std::cin, busStopName1);
	
	std::cout << "Introduza o nome da 2 paragem?";
	getline(std::cin, busStopName2);

	
	//Se calhar fazer um ciclo pois pode haver mais que uma paragem com o name1

	int indexLine = -1;

	for (unsigned int i = 0; i < lines.size(); i++) {

		for (unsigned int j = 0; j < lines.at(i).getBusStops().size();j++) {
			if (lines.at(i).getBusStop(j) == busStopName1){
				indexLine = i;
				goto CONTINUE;
			}
		}

	}
CONTINUE:;
	std::vector<stopInfo> stopInfo;
	if (indexLine == -1)
		return;
	else timeBetStopsAux(lines, busStopName2, stopInfo, indexLine, false);
}

bool timeBetStopsAux(const std::vector<Line> &lines, const std::string stopName, std::vector<stopInfo> stopInfo, unsigned int index, bool test) {
	
	for (uint j = 0; j < lines.at(index).getBusStops().size(); j++) {

		for (unsigned int i = 0; i < lines.at(index).getBusStops().size(); i++) {
			if (lines.at(index).getBusStop(i) == stopName){
				std::cout << "Found, line " <<i << "\n" << lines.at(index).getBusStop(i);
				return true;
				
			}
			//Colocar o resto da stopInfo

		}

		if (test)
			return false;

		if (timeBetStopsAux(lines, lines.at(index).getBusStop(j), stopInfo, j, true))
			if (timeBetStopsAux(lines, stopName, stopInfo, j,false))
				return true;
			else timeBetStopsAux(lines, stopName, stopInfo, ++j, false);

		else timeBetStopsAux(lines, lines.at(index).getBusStop(j), stopInfo, ++j, true);

	}


}