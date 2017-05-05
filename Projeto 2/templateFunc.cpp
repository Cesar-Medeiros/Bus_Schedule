#include "Header.h"

#ifndef TEMPLATE
#define TEMPLATE

//Nestas templates functions foi aproveitado o facto de tanto a struct linha como o condutor tem um membro id em comum.

//estrutura e' um vetor de linhas ou condutores
//estruturaTemp e' uma variavel do tipo linhaStruct ou condutorStruct


/**
Le o ID e verifica se ja se encontra no vetor
@param estruturaTemp estrutura Struct onde vai ser guardado o id e o vetor onde vai procurar o id.
*/

template <class T> void readID(T &classVar, const std::vector<T> &vec) {

	bool foundID;
	unsigned int id;
	do {
		foundID = false;

		
		readNum("Introduza o ID: ", id);

		for (uint i = 0; i < vec.size(); i++) {
			if (id == vec.at(i).getId()) {
				foundID = true;
				colorCout('!');
				std::cout << "ID ja existe \n\n";
				break;
			}
		}

	} while (foundID);

	classVar.setId(id);
}


/**
Pergunta o id de uma linha ou condutor ao utilizado e verifica se e' valido. Se nao for valido volta a perguntar.

@param estrutura Vector de linhas ou de condutores.
@return Posicao do elemento do vetor ou -1 se o utilizador nao quiser tentar novamente.
*/
template <class T> int ask_TestID(const std::vector<T> &vect) {

	int pos;
	uint id;
	bool validID;

	do {
		pos = -1;

		readNum("Introduza um ID: ", id);


		for (uint i = 0; i<vect.size(); i++) {
			if (id == vect.at(i).getId())
				pos = i;
		}

		if (pos == -1)
		{
			validID = false;
			colorCout('!');
			std::cout << "Id not found.\n";

			char repeatCicle;

			do {
				colorCout('?');
				std::cout << "Try again (S ou N)? ";
				std::cin >> repeatCicle;

				char bufferContent;
				std::cin.get(bufferContent);
				if (bufferContent != '\n') {
					std::cin.ignore(1000, '\n');
					repeatCicle = 0;
					colorCout('!');
					std::cout << "Invalid Input" << std::endl;
				}

			} while (toupper(repeatCicle) != 'N' && toupper(repeatCicle) != 'S');

			if (toupper(repeatCicle) == 'N')
				return -1;
		}

		else validID = true;

	} while (!validID);

	return pos;
}


/**
Insere uma linha ou condutor(estruturaTemp) por ordem do ID num vetor estrutura
@param estruturaTemp estrutura 1o - Struct onde se encontrar o id, 2o - Vetor onde se vai inserir a estruturaTemp.
*/
template <class T> void sortID(T &classVar, std::vector<T> &vect) {

	uint i = 0;
	bool insertID = false;

	while ((i < vect.size()) && !insertID) {
		if (classVar.getId() < vect.at(i).getId()) {
			vect.insert(vect.begin() + i, classVar);
			insertID = true;
		}
		i++;
	}

	if (!insertID)
		vect.push_back(classVar);
}


template <class T> void sortID(std::vector<T> &vect) {

	bool inOrder;

	do {
		inOrder = true;

		for (uint i = 0; i < vect.size() - 1; i++) {
			if (vect.at(i).getId() > vect.at(i + 1).getId()) {
				std::iter_swap(&vect.at(i), &vect.at(i + 1));
				inOrder = false;
			}
		}

	} while (!inOrder);
}


//Nao esta a ser usada nesta versao do projeto
template <class T> int gestaoNotepad(const std::string &nomeFicheiro, std::vector<T> &estrutura) {

	int opcao;

	std::cout << "\n\nDeseja \"operacao\" o ficheiro: \n";
	std::cout << "1 - No notepad\n";
	std::cout << "2 - Pela consola\n\n";

	do {
		int opcao = lerOpcao();
	} while ((opcao != 1) && (opcao != 2));

	if (opcao == 1) {
		openNotepad(nomeFicheiro);
		estrutura.clear();
		/*if (typeid(T).name() == "linhaStruct") {

		lerFicheiroLinhas(estrutura, nomeFicheiro);
		}
		else readDrivers(estrutura, nomeFicheiro);*/
	}
	return opcao;
}

#endif