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

void printCentered(std::ostream& out, const std::string info, const unsigned int sizew) {

	unsigned int w = info.length();
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
//Imprime liga��es
void printConnection(connectionInfo connection)
{
	cout << connection.line << "--" << connection.time << " -- " << connection.stop << endl;
}

//stopsWithConnection
//retorna um vetor de liga��es com a paragem stop, ignorando possiveis liga��es com a paragem lastStop
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
//Retorna um vetor com os index de caminhos que j� tenham chegado ao destino
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
//No ciclo da fun��o teste ao adicionar caminhos completos ao vetor respetivo, temos de os remover, no entanto quando removemos um 
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
//Retorna um vetor que contem a informa��o do index e tempo do caminho mais lento
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
//Dando um vetor de caminhos, e um caminho completo, elimina do vetor de caminhos, os que s�o mais lentos que o completo
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
//Retorna um vetor de 3 caminhos, os mais r�pidos
//Pode ser modificado para retornar mais ou at� contabilizar perdas de tempo de mudan�as de linha
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
//devolve o caminho mais r�pido de um vetor de caminhos
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


//Estado da fun��o
//falta compor a fun��o de modo a mostrar a linha da primeira paragem, f�cil de implementar
//Contabilizar e aconselhar sobre atrasos de mudan�as de linha, tamb�m n�o deve ser muito dificil
//Se n�o encontrar caminho direto aconselhar a ir a p� parte do caminho? Dificil de implementar
//Est� funcional, agora � s� otimizar
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

	//Se n�o encontrou nenhuma conex�o significa que n�o colocou uma paragem certa
	if (connections.empty()) cout << "N�o foram encontradas liga��es com a paragem inicial inserida, secalhar a paragem n�o existe (fazer com parte a p�?) " << endl;

	//colocar no vetor de caminhos as liga��es iniciais com a paragem inicial
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

		//adiciona algum caminho j� completo
		//remove-os dos caminhos a serem calculados
		if (!indexValidPaths.empty())
		{
			//adiciona caminhos encontrados ao vetor de caminhos completos
			for (int i = 0; i < indexValidPaths.size(); i++)
			{
				cout << "------------------Caminho encontrado-------------------" << endl;
				completedPaths.push_back(paths.at(indexValidPaths.at(i)));

			}
			//Remove os caminhos completos do vetor de caminhos, para n�o continuar a procurar op��es
			for (int i = 0; i < indexValidPaths.size(); i++)
			{
				paths.erase(paths.begin() + indexValidPaths.at(i));
				indexValidPaths = updateIndexValidPaths(indexValidPaths, i);
			}
			//remove os caminhos que j� ultrapassam em tempo a pior solu��o, pode ter de ser otimizada, se a liga��o for quase direta elimina todas as op��es
			if (!completedPaths.empty())
			{
				paths = removeSlowerPaths(paths, fasterCompleted(completedPaths));
			}

		}

		//Enquanto n�o tivermos, neste caso 3 solu��es (pode ser mudado), vai procurar op��es de caminhos
		if (completedPaths.size() < 3)
		{
			int count = paths.size();

			//numa primeira itera��o v� conex�es, excluindo a paragem anterior, a inicial
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
			//em itera��es posteriores procura conex�es, excluindo a paragem anterior
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
			//Est� a parar na 10+ itera��o mas pode ser otimizado
			else if (iterations > 10) continueSearch = false;


			iterations++;
		}
		else continueSearch = false;

	}
	//parte final
	if (!completedPaths.empty())
	{
		//de todos os caminhos completos refina de modo a selecionar at� os tr�s melhores 
		vector < vector <connectionInfo>> refinedPaths = bestPaths(completedPaths);

		//adiciona a primeira paragem, falta mudar para p�r a paragem inicial, e tamb�m contabilizar e aconselhar sobre atrasos de mudan�as de linha
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
	else cout << "O algoritmo n�o encontrou solucao" << endl;
}
