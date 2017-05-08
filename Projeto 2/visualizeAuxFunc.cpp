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
}*/


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



//printConnection
//Imprime ligações
void printConnection(connectionInfo connection)
{
	cout << connection.line << "--" << connection.time << " -- " << connection.stop << endl;
}

//stopsWithConnection
//retorna um vetor de ligações com a paragem stop, ignorando possiveis ligações com a paragem lastStop
std::vector<connectionInfo> stopsWithConnection(std::string stop, std::string lastStop, const std::vector<Line> &lines)
{
	std::vector<connectionInfo> connections;

	//iterates every line
	for (uint i = 0; i < lines.size(); i++)
	{
		//iterates every stop in he line
		for (uint j = 0; j < lines.at(i).getBusStops().size(); j++)
		{
			//if the current stop is the stop we want to know the connections 
			//and it's not the stop that we had previously in our path (tested in the next if) we add that stop to our path
			//in a struct that gives information about the id of the line, time to take that stop, nextStop
			//this if tests for the case where it's the stop we want is the first one
			if (j == 0 && lines.at(i).getBusStop(j) == stop)
			{
				if (lines.at(i).getBusStop(j + 1) != lastStop)
				{
					connectionInfo addInfo;
					addInfo.line = lines.at(i).getId();
					addInfo.time = lines.at(i).getTiming(j);
					addInfo.stop = lines.at(i).getBusStop(j + 1);
					connections.push_back(addInfo);
				}
			}
			//this if tests for the case where it's the stop we want is the last one
			else if (lines.at(i).getBusStop(j) == stop && j == (lines.at(i).getBusStops().size() - 1))
			{
				if (lines.at(i).getBusStop(j - 1) != lastStop)
				{
					connectionInfo addInfo;
					addInfo.line = lines.at(i).getId();
					addInfo.time = lines.at(i).getTiming(j - 1);
					addInfo.stop = lines.at(i).getBusStop(j - 1);
					connections.push_back(addInfo);
				}
			}
			//this if tests for the case where it's the stop we want is between the first and the last
			else if (lines.at(i).getBusStop(j) == stop)
			{
				if (lines.at(i).getBusStop(j - 1) != lastStop)
				{
					connectionInfo addInfo;
					addInfo.line = lines.at(i).getId();
					addInfo.time = lines.at(i).getTiming(j - 1);
					addInfo.stop = lines.at(i).getBusStop(j - 1);
					connections.push_back(addInfo);
				}
				if (lines.at(i).getBusStop(j + 1) != lastStop)
				{
					connectionInfo addInfo;
					addInfo.line = lines.at(i).getId();
					addInfo.time = lines.at(i).getTiming(j);
					addInfo.stop = lines.at(i).getBusStop(j + 1);
					connections.push_back(addInfo);
				}
			}
		}
	}

	return connections;
}

//cleanPaths
//Elimina os primeiros count caminhos de um vetor de caminhos, serve para eliminar caminhos que foram repetido ao adicionar uma nova paragem 
vector < vector <connectionInfo>> cleanPaths(vector < vector <connectionInfo>> paths, int count)
{
	vector<vector <connectionInfo>>::const_iterator first = paths.begin() + count;
	vector<vector <connectionInfo>>::const_iterator last = paths.end();
	vector<vector <connectionInfo>> newVec(first, last);

	return newVec;
}

//printPaths
//imprime um vetor de caminhos
void printPaths(vector < vector <connectionInfo>> paths)
{
	cout << "--------------" << endl;
	for (uint i = 0; i < paths.size(); i++)
	{
		cout << "New path " << endl;
		for (uint j = 0; j < paths.at(i).size(); j++)
		{
			printConnection(paths[i][j]);
		}
	}
	cout << "--------------" << endl;

}

//printPath
//imprime um caminho
void printPath(vector <connectionInfo> path)
{
	vector <string> stops;
	vector < int> line;
	int time = 0;
	for (uint i = 0; i < path.size(); i++)
	{
		stops.push_back(path.at(i).stop);
		line.push_back(path.at(i).line);
		time += path.at(i).time;
	}
	cout << "The trip will take you " << time << " minutes" << endl;
	for (int i = 0; i < path.size(); i++)
	{
		cout << "Stop " << stops.at(i) << "---" << "Line " << line.at(i) << endl;
	}
}

//validPaths
//Retorna um vetor com os index de caminhos que já tenham chegado ao destino
vector<int> validPaths(vector < vector <connectionInfo>> paths, std::string finalPosition)
{
	vector <int> validPaths;

	for (int i = 0; i < paths.size(); i++)
	{
		for (int j = 0; j < paths.at(i).size(); j++)
		{
			if (paths[i][j].stop == finalPosition) validPaths.push_back(i);
		}
	}
	return validPaths;
}

//updateValidPaths
//No ciclo da função teste ao adicionar caminhos completos ao vetor respetivo, temos de os remover, no entanto quando removemos um 
//index inferior a outros que venham a seguir temos de decrementar os seguintes, serve como um remendo para isso
vector < int> updateIndexValidPaths(vector<int> indexValidPaths, int  index)
{
	int indexChanged = indexValidPaths.at(index);
	for (int i = 0; i < indexValidPaths.size(); i++)
	{
		if (indexValidPaths.at(i) > indexChanged) indexValidPaths.at(i) = indexValidPaths.at(i) - 1;
	}
	return indexValidPaths;
}

//pathTime
//retorna o tempo de um caminho
int pathTime(vector <connectionInfo> path)
{
	int time = 0;
	for (int i = 0; i < path.size(); i++)
	{
		time += path.at(i).time;
	}
	return time;
}

//longerPath
//Retorna um vetor que contem a informação do index e tempo do caminho mais lento
vector<int> longerPath(vector < vector <connectionInfo>> bestPaths)
{
	int longerPath = 0;
	int index = 0;

	for (int i = 0; i < bestPaths.size(); i++)
	{
		if (pathTime(bestPaths.at(i)) > longerPath)
		{
			longerPath = pathTime(bestPaths.at(i));
			index = i;
		}
	}
	vector<int> longerPathInfo;
	longerPathInfo.push_back(index);
	longerPathInfo.push_back(longerPath);
	return longerPathInfo;
}

//RemoveSlowerPaths
//Dando um vetor de caminhos, e um caminho completo, elimina do vetor de caminhos, os que são mais lentos que o completo
vector < vector <connectionInfo>> removeSlowerPaths(vector < vector <connectionInfo>> paths, vector <connectionInfo> completedPath)
{
	int minTime = pathTime(completedPath);
	for (int i = 0; i < paths.size();)
	{
		if (pathTime(paths.at(i)) > minTime) paths.erase(paths.begin() + i);
		else i++;
	}
	return paths;
}

//bestPaths
//Retorna um vetor de 3 caminhos, os mais rápidos
//Pode ser modificado para retornar mais ou até contabilizar perdas de tempo de mudanças de linha
vector < vector <connectionInfo>> bestPaths(vector < vector <connectionInfo>> paths)
{
	vector < vector <connectionInfo>> bestPaths;


	for (int i = 0; i < paths.size(); i++)
	{
		if (bestPaths.size() < 3)
		{
			bestPaths.push_back(paths.at(i));
		}
		else
		{
			int time = pathTime(paths.at(i));
			vector <int> longerPathInfo = longerPath(bestPaths);
			if (time < longerPathInfo.at(1)) bestPaths.at(longerPathInfo.at(0)) = paths.at(i);
		}
	}
	return bestPaths;
}

//FasterCompleted
//devolve o caminho mais rápido de um vetor de caminhos
vector <connectionInfo> fasterCompleted(vector < vector <connectionInfo>> paths)
{
	int minTime, iter;

	minTime = pathTime(paths.at(0));
	iter = 0;

	for (int i = 0; i < paths.size(); i++)
	{
		if (pathTime(paths.at(i)) < minTime)
		{
			minTime = pathTime(paths.at(i));
			iter = i;
		}
	}

	return paths.at(iter);
}

//printFinalPaths
//imprime as rotas finais encontradas
void printFinalPaths(vector < vector <connectionInfo>> paths)
{
	cout << "----------------------------" << endl;
	cout << "The path(s) are " << endl;
	cout << "----" << endl;
	for (int i = 0; i < paths.size(); i++)
	{
		cout << "Rout " << i + 1 << endl;
		printPath(paths.at(i));
		cout << "----" << endl;
	}
}


//Estado da função
//falta compor a função de modo a mostrar a linha da primeira paragem, fácil de implementar
//Contabilizar e aconselhar sobre atrasos de mudanças de linha, também não deve ser muito dificil
//Se não encontrar caminho direto aconselhar a ir a pé parte do caminho? Dificil de implementar
//Está funcional, agora é só otimizar
//falta no cin das paragens aceitar paragens com mais do que uma palavra
void teste(const std::vector<Line> &lines)
{
	string firstStop, lastStop;

	std::cout << "Insira a paragem inicial" << endl;

	cin >> firstStop;

	cout << "Insira a paragem final" << endl;

	cin >> lastStop;

	std::vector<connectionInfo> connections;

	connections = stopsWithConnection(firstStop, "", lines);

	//Se não encontrou nenhuma conexão significa que não colocou uma paragem certa
	if (connections.empty()) cout << "Não foram encontradas ligações com a paragem inicial inserida, secalhar a paragem não existe (fazer com parte a pé?) " << endl;

	//colocar no vetor de caminhos as ligações iniciais com a paragem inicial
	vector < vector <connectionInfo>> paths;

	for (int i = 0; i < connections.size(); i++)
	{
		vector <connectionInfo> temp;
		temp.push_back(connections.at(i));
		paths.push_back(temp);
	}

	bool continueSearch = true;

	int iterations = 0;

	vector <vector <connectionInfo>> completedPaths;

	//ciclo que percorre possibilidades de caminhos
	while (continueSearch)
	{
		vector <int > indexValidPaths = validPaths(paths, lastStop);

		//adiciona algum caminho já completo
		//remove-os dos caminhos a serem calculados
		if (!indexValidPaths.empty())
		{
			//adiciona caminhos encontrados ao vetor de caminhos completos
			for (int i = 0; i < indexValidPaths.size(); i++)
			{
				cout << "------------------Caminho encontrado-------------------" << endl;
				completedPaths.push_back(paths.at(indexValidPaths.at(i)));

			}
			//Remove os caminhos completos do vetor de caminhos, para não continuar a procurar opções
			for (int i = 0; i < indexValidPaths.size(); i++)
			{
				paths.erase(paths.begin() + indexValidPaths.at(i));
				indexValidPaths = updateIndexValidPaths(indexValidPaths, i);
			}
			//remove os caminhos que já ultrapassam em tempo a pior solução, pode ter de ser otimizada, se a ligação for quase direta elimina todas as opções
			if (!completedPaths.empty())
			{
				paths = removeSlowerPaths(paths, fasterCompleted(completedPaths));
			}

		}

		//Enquanto não tivermos, neste caso 3 soluções (pode ser mudado), vai procurar opções de caminhos
		if (completedPaths.size() < 3)
		{
			int count = paths.size();

			//numa primeira iteração vê conexões, excluindo a paragem anterior, a inicial
			if (iterations == 0)
			{
				int sizePaths = paths.size();
				for (int i = 0; i < sizePaths; i++)
				{
					connections = stopsWithConnection(paths[i][paths[i].size() - 1].stop, firstStop, lines);
					for (int j = 0; j < connections.size(); j++)
					{
						vector <connectionInfo> temp;
						for (int s = 0; s <paths.at(i).size(); s++)
						{
							temp.push_back(paths[i][s]);
						}
						temp.push_back(connections.at(j));
						paths.push_back(temp);
					}
				}
				//limpa do vetor de caminhos os caminhos anteriores(quando se adiciona a um caminho de 2 paragens uma terceira, fica o vetor anterior de 2 no inicio, eliminam-se esses
				paths = cleanPaths(paths, count);
			}
			//em iterações posteriores procura conexões, excluindo a paragem anterior
			else if (iterations > 0 && iterations< 10)
			{
				int sizePaths = paths.size();
				vector <vector <connectionInfo>> originalPaths = paths;
				for (int i = 0; i < sizePaths; i++)
				{
					connections = stopsWithConnection(originalPaths[i][originalPaths[i].size() - 1].stop, originalPaths[i][originalPaths[i].size() - 2].stop, lines);
					for (int j = 0; j < connections.size(); j++)
					{
						vector <connectionInfo> temp;
						for (int s = 0; s < originalPaths[i].size(); s++)
						{
							temp.push_back(originalPaths[i][s]);
						}
						temp.push_back(connections.at(j));
						paths.push_back(temp);
					}
				}
				paths = cleanPaths(paths, count);
			}
			//Está a parar na 10+ iteração mas pode ser otimizado
			else if (iterations > 10) continueSearch = false;


			iterations++;
		}
		else continueSearch = false;

	}
	//parte final
	if (!completedPaths.empty())
	{
		//de todos os caminhos completos refina de modo a selecionar até os três melhores 
		vector < vector <connectionInfo>> refinedPaths = bestPaths(completedPaths);

		//adiciona a primeira paragem, falta mudar para pôr a paragem inicial, e também contabilizar e aconselhar sobre atrasos de mudanças de linha
		connectionInfo originStop;
		originStop.line = 0;
		originStop.stop = firstStop;
		originStop.time = 0;

		//Adiciona a paragem inicial ao vetor no inicio
		for (int i = 0; i < refinedPaths.size(); i++)
		{
			refinedPaths.at(i).insert(refinedPaths.at(i).begin(), originStop);
		}

		printFinalPaths(refinedPaths);


	}
	else cout << "O algoritmo não encontrou solucao" << endl;
}

