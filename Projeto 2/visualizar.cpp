#include "Header.h"
#include "string"

void printHorarioLinha(const std::vector<Line> &line, int posLine);
void printHorarioParagem(const std::vector<Line> &line);
void tempoEntreParagens(const std::vector<Line> &line);
void mostrarLinha(const std::vector<Line> &line);
void procuraParagem(const std::vector<Line> &line);



void visualizarInformacao(const std::vector<Line> &linha) {



	do {


		std::cout << "\n\n |          Visualizar Informacao         |\n";
		std::cout << " |----------------------------------------|\n";
		std::cout << " |     (1)  Horario de uma linha          |\n";
		std::cout << " |     (2)  Horario de uma paragem        |\n";
		std::cout << " |     (3)  Tempo entre duas paragens     |\n";
		std::cout << " |     (4)  Visualizar uma linha          |\n";
		std::cout << " |     (5)  Linhas com uma paragem        |\n";
		std::cout << " |     (0)  Menu principal                |\n\n";

		bool validNumber;

		do {

			validNumber = true;

			int option = readOption(); //Le a opcao e faz os devidos testes para prevenir input invalido

			switch (option) {

			case 0: return;

			case 1: {
				int posLine = ask_TestID(linha);

				if (posLine == -1) { //Linha nao foi encontrada
					colorCout('!');
					std::cout << "Nao foi possivel apresentar o horario da linha que introduziu." << std::endl;
				}
				else {
					printHorarioLinha(linha, posLine);
					std::cout << "\nClique em qualquer tecla para continuar";
					getchar();
				}
				break;
			}

			case 2:
				printHorarioParagem(linha);
				break;

			case 3:
				tempoEntreParagens(linha);
				std::cout << "\nClique em qualquer tecla para continuar";
				getchar();
				break;

			case 4:
				mostrarLinha(linha);
				std::cout << "\n\nClique em qualquer tecla para continuar";
				getchar();
				break;

			case 5:
				procuraParagem(linha);
				std::cout << "\nClique em qualquer tecla para continuar";
				getchar();
				break;

			default: validNumber = false;
			}

		} while (!validNumber);


	} while (true);

}


void procuraParagem(const std::vector<Line> &line) {

	std::string paragem;
	colorCout('?');
	std::cout << "Introduza o nome da paragem que deseja procurar: ";
	std::cin >> paragem;
	std::cin.ignore(1000, '\n');
	std::vector<int> idLinhas;

	for (uint i = 0; i < line.size(); i++) {

		for (uint j = 0; j < line.at(i).getBusStops().size(); j++) {

			if (paragem == line.at(i).getBusStop(j)) {
				idLinhas.push_back(line.at(i).getId());
				break;
			}
		}
	}
	if (idLinhas.size() == 0) {
		colorCout('!');
		std::cout << "Nao foram encontradas paragens com nome: " << paragem << std::endl;
	}

	else {

		std::cout << "\nA paragem " << paragem << " esta presente nas linhas com ID: ";

		for (uint i = 0; i < idLinhas.size(); i++) {

			if (i + 1 != idLinhas.size())
				std::cout << idLinhas.at(i) << " e ";
			else
				std::cout << idLinhas.at(i) << std::endl << std::endl;
		}
	}

}

void mostrarLinha(const std::vector<Line> &lines) {

	int posLinha = ask_TestID(lines);

	if (posLinha != -1) {
		std::cout << "\n\t\t ID = " << lines.at(posLinha).getId() << std::endl;
		std::cout << "\n\t\t Frequencia = " << lines.at(posLinha).getFreq() << " minutos" << "\n\n\t\t ";

		for (uint i = 0; i < lines.at(posLinha).getBusStops().size(); i++) {
			std::cout << lines.at(posLinha).getBusStop(i);
			if (i + 1 != lines.at(posLinha).getBusStops().size())
				std::cout << "   <-->   " << lines.at(posLinha).getTiming(i) << " minutos   <-->   ";

		}
	}
}


std::vector<par> posicaoParagem(const std::vector<Line> &lines, std::string stopName)
{
	std::vector<par> listaID;

	for (uint i = 0; i < lines.size(); i++) {

		for (uint j = 0; j < lines.at(i).getBusStops().size(); j++) {
			if (lines.at(i).getBusStop(j) == stopName) {
				par par;
				par.linha = i;
				par.posicao1 = j;
				listaID.push_back(par);
				break; //Encontra 1 elemento igual
			}
		}

	}

	return listaID;
}

//Pergunta o nome de duas paragens, verifica se estao na mesma linha e se isso se verificar devolve o tempo entre paragens
void tempoEntreParagens(const std::vector<Line> &lines) {


	std::string paragem1, paragem2;
	std::cout << "Insira o nome da primeira paragem: ";
	getline(std::cin, paragem1);
	std::cout << "Insira o nome da segunda paragem: ";
	getline(std::cin, paragem2);



	std::vector<par> paragem1LinhasID = posicaoParagem(lines, paragem1);
	std::vector<par> paragem2LinhasID = posicaoParagem(lines, paragem2);
	std::vector<par> linhasComum;

	for (uint i = 0; i < paragem1LinhasID.size(); i++) {

		for (uint j = 0; j < paragem2LinhasID.size(); j++) {

			if (paragem1LinhasID.at(i).linha == paragem2LinhasID.at(j).linha) {


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
			tempo += lines.at(linhasComum.at(i).linha).getTiming(j);
		}
		linhasComum.at(i).tempo = tempo;

	}
	if (linhasComum.size() == 0) {
		colorCout('!');
		std::cout << "As paragens introduzidas nao se encontram na mesma linha";
	}

	else
	{
		std::cout << "\nTempo entre " << paragem1 << " e " << paragem2 << " = ";

		for (uint i = 0; i < linhasComum.size(); i++) {

			std::cout << "Linha " << linhasComum.at(i).linha << ": ";
			std::cout << linhasComum.at(i).tempo << " minutos." << std::endl;
		}

	}


	//linhasComum.at(0).tempo; //Alterar, criar algoritmo para dar o menor tempo;
}