#include "Header.h"

#include <Windows.h>
/**Pergunta ao utilizador para escolher uma opcao. Previne erros de input.
@return Opcao se o numero introduzido for inteiro, ou -1 se o input nao for um inteiro
*/

int readOption() {

	int option;
	colorCout('?');
	std::cout << "Escolha uma opcao: ";
	std::cin >> option;

	char bufferContent;
	std::cin.get(bufferContent);

	if (std::cin.fail() || bufferContent != '\n') {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		colorCout('!');
		std::cout << "Input invalido\n\n";
		option = -1; //Ter a certeza que o lixo de memoria que ficou na opcao nao seja nenhuma das opcoes
	}

	return option;
}

/**Le um numeros (unsigned int). O parametro texto e uma string que e apresentada ao utilizador.
@param

textoImprimir imprime um texto para a consola;
var Variavel onde vai ser guardado o numero;
simboloPergunta True para apresentar o simbolo ?

*/

void readNum(const char coutText[], uint &num, bool displaySymbol) {

	char bufferContent;

	do {
		if (displaySymbol)
			colorCout('?');

		std::cout << coutText;
		std::cin >> num;
		std::cin.get(bufferContent);

		if ((std::cin.fail() || bufferContent != '\n')) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			colorCout('!');
			std::cout << "Invalid Input\n\n";

		}

	} while (std::cin.fail() || bufferContent != '\n');
}

void colorCout(char symbol) {
	int colorNum;
	bool validSymbol = true;
	switch (symbol) {

	case '?': colorNum = 9; break;
	case '!': colorNum = 12; break;
	case '*': colorNum = 10; break;
	default: validSymbol = false;
	}

	if (validSymbol) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
		std::cout << "[" << symbol << "] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void ask_YN(char text[], char &answer) {
	do {
		colorCout('?');
		std::cout << text;
		std::cin >> answer;

		char bufferContent;
		std::cin.get(bufferContent);
		if (bufferContent != '\n') {
			std::cin.ignore(1000, '\n');
			answer = 0;
			colorCout('!');
			std::cout << "Invalid Input" << std::endl;
		}

	} while (toupper(answer) != 'N' && toupper(answer) != 'S');
}