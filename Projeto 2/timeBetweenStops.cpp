#include "Header.h"

std::vector<connectionInfo> stopsWithConnection(std::string stop, std::string lastStop, const std::vector<Line> &lines);
void printConnection(connectionInfo connection);

//printConnection
//Imprime ligacoes
void printConnection(connectionInfo connection)
{
	std::cout << connection.line << "--" << connection.time << " -- " << connection.stop << std::endl;
}

//stopsWithConnection
//retorna um vetor de ligacoes com a paragem stop, ignorando possiveis ligacoes com a paragem lastStop
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
std::vector < std::vector <connectionInfo>> cleanPaths(std::vector < std::vector <connectionInfo>> paths, int count)
{
	std::vector<std::vector <connectionInfo>>::const_iterator first = paths.begin() + count;
	std::vector<std::vector <connectionInfo>>::const_iterator last = paths.end();
	std::vector<std::vector <connectionInfo>> newVec(first, last);

	return newVec;
}

//printPaths
//imprime um vetor de caminhos
void printPaths(std::vector < std::vector <connectionInfo>> paths)
{
	std::cout << "--------------" << std::endl;
	for (uint i = 0; i < paths.size(); i++)
	{
		std::cout << "New path " << std::endl;
		for (uint j = 0; j < paths.at(i).size(); j++) printConnection(paths[i][j]);
	}
	std::cout << "--------------" << std::endl;

}

//printPath
//imprime um caminho
void printPath(std::vector <connectionInfo> path)
{
	std::vector <std::string> stops;
	std::vector < int> line;
	int time = 0;
	for (uint i = 0; i < path.size(); i++)
	{
		stops.push_back(path.at(i).stop);
		line.push_back(path.at(i).line);
		time += path.at(i).time;
	}
	std::cout << std::endl;
	std::cout << "A viagem ira demorar " << time << " minutos" << std::endl;
	for (int i = 0; i < path.size(); i++)
	{

		
		std::cout << "Paragem " << " --- " << stops.at(i);
		if (i != 0) std::cout << " --- " << " Linha " << line.at(i) << std::endl;
		else std::cout <<" ---  Paragem Inicial" << std::endl;

	}
	std::cout << std::endl;
}

//validPaths
//Retorna um vetor com os index de caminhos que j? tenham chegado ao destino
std::vector<int> validPaths(std::vector < std::vector <connectionInfo>> paths, std::string finalPosition)
{
	std::vector <int> validPaths;

	for (int i = 0; i < paths.size(); i++)
	{
		for (int j = 0; j < paths.at(i).size(); j++)
		{
			if (paths[i][j].stop == finalPosition) 
				validPaths.push_back(i);
		}
	}
	return validPaths;
}

//updateValidPaths
//No ciclo da fun??o teste ao adicionar caminhos completos ao vetor respetivo, temos de os remover, no entanto quando removemos um 
//index inferior a outros que venham a seguir temos de decrementar os seguintes, serve como um remendo para isso
std::vector < int> updateIndexValidPaths(std::vector<int> indexValidPaths, int  index)
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
int pathTime(std::vector <connectionInfo> path)
{
	int time = 0;
	for (int i = 0; i < path.size(); i++)
	{
		time += path.at(i).time;
	}
	return time;
}

//longerPath
//Retorna um vetor que contem a informa??o do index e tempo do caminho mais lento
std::vector<int> longerPath(std::vector < std::vector <connectionInfo>> bestPaths)
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
	std::vector<int> longerPathInfo;
	longerPathInfo.push_back(index);
	longerPathInfo.push_back(longerPath);
	return longerPathInfo;
}

//RemoveSlowerPaths
//Dando um vetor de caminhos, e um caminho completo, elimina do vetor de caminhos, os que s?o mais lentos que o completo
std::vector < std::vector <connectionInfo>> removeSlowerPaths(std::vector < std::vector <connectionInfo>> paths, std::vector <connectionInfo> completedPath)
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
//Retorna um vetor de 3 caminhos, os mais r?pidos
//Pode ser modificado para retornar mais ou at? contabilizar perdas de tempo de mudan?as de linha
std::vector < std::vector <connectionInfo>> bestPaths(std::vector < std::vector <connectionInfo>> paths)
{
	std::vector < std::vector <connectionInfo>> bestPaths;


	for (int i = 0; i < paths.size(); i++)
	{
		if (bestPaths.size() < 2)
		if (bestPaths.size() < 10)
		{
			bestPaths.push_back(paths.at(i));
		}
		else
		{
			int time = pathTime(paths.at(i));
			std::vector <int> longerPathInfo = longerPath(bestPaths);
			if (time < longerPathInfo.at(1)) bestPaths.at(longerPathInfo.at(0)) = paths.at(i);
		}
	}
	return bestPaths;
}


//FasterCompleted
//devolve o caminho mais r?pido de um vetor de caminhos
std::vector <connectionInfo> fasterCompleted(std::vector < std::vector <connectionInfo>> paths)
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
void printFinalPaths(std::vector < std::vector <connectionInfo>> paths, std::string firstStop, std::string lastStop)
{
	std::cout << "----------------------------" << std::endl;

	std::cout << "Os caminhos encontrados foram:" << std::endl;
	std::cout << std::endl << std::endl;

	for (int i = 0; i < paths.size(); i++)
	{
		std::cout << "Caminho " << i + 1 << std::endl;
		printPath(paths.at(i));
		std::cout << std::endl;
	}
}

//ultimateRefinery
//last modifications to give the brest 3 results
std::vector < std::vector <connectionInfo>> ultimateRefinery(std::vector < std::vector <connectionInfo>> refinedPaths)
{
	std::vector<int> times;
	for (int i = 0; i < refinedPaths.size(); i++)
	{
		int time = 0;
		for (int j = 0; j < refinedPaths.at(i).size(); j++)
		{
			time += refinedPaths.at(i).at(j).time;
			//adicionar tempo medio de espera
			if (j != refinedPaths.at(i).size() - 1)
			{
				if (refinedPaths.at(i).at(j).line != refinedPaths.at(i).at(j + 1).line) time += 5;
			}
		}
		times.push_back(time);
	}
	std::vector < std::vector <connectionInfo>> bestPaths;
	for (int i = 0; i < refinedPaths.size(); i++)
	{
		if (bestPaths.size() < 3)
		{
			bestPaths.push_back(refinedPaths.at(i));
		}
		else
		{
			int time = pathTime(refinedPaths.at(i));
			std::vector <int> longerPathInfo = longerPath(bestPaths);
			if (time < longerPathInfo.at(1)) bestPaths.at(longerPathInfo.at(0)) = refinedPaths.at(i);
		}
	}
	return bestPaths;
}


//Estado da fun??o
//falta compor a fun??o de modo a mostrar a linha da primeira paragem, f?cil de implementar
//Contabilizar e aconselhar sobre atrasos de mudan?as de linha, tamb?m n?o deve ser muito dificil
//Se n?o encontrar caminho direto aconselhar a ir a p? parte do caminho? Dificil de implementar
//Est? funcional, agora ? s? otimizar
//falta no cin das paragens aceitar paragens com mais do que uma palavra
void timeBetween2Stops(const std::vector<Line> &lines)
{
	std::string firstStop, lastStop;
	colorCout('?');
	std::cout << "Insira a paragem inicial: ";
	getline(std::cin, firstStop);


	colorCout('?');
	std::cout << "Insira a paragem final: ";
	getline(std::cin, lastStop);

	std::vector<connectionInfo> connections = stopsWithConnection(firstStop, "", lines);



	if (connections.empty())
	{
		colorCout('!');
		std::cout << "Primeira paragem inserida nao exite" << std::endl;
		return;
	}
	std::vector<connectionInfo> connectionsF = stopsWithConnection(lastStop, "", lines);
	if (connectionsF.empty()) {
		colorCout('!');
		std::cout << "Ultima paragem inserida nao exite" << std::endl;
		return;
	}




	//colocar no vetor de caminhos as liga??es iniciais com a paragem inicial
	std::vector <std::vector <connectionInfo>> paths;

	for (int i = 0; i < connections.size(); i++)
	{
		std::vector <connectionInfo> temp;
		temp.push_back(connections.at(i));
		paths.push_back(temp);
	}

	bool continueSearch = true;

	int iterations = 0;

	std::vector <std::vector <connectionInfo>> completedPaths;

	//ciclo que percorre possibilidades de caminhos
	while (continueSearch)
	{
		std::vector <int> indexValidPaths = validPaths(paths, lastStop);

		//adiciona algum caminho j? completo
		//remove-os dos caminhos a serem calculados
		if (!indexValidPaths.empty())
		{
			//adiciona caminhos encontrados ao vetor de caminhos completos
			for (int i = 0; i < indexValidPaths.size(); i++)
			{
				completedPaths.push_back(paths.at(indexValidPaths.at(i)));

			}
			//Remove os caminhos completos do vetor de caminhos, para n?o continuar a procurar op??es
			for (int i = 0; i < indexValidPaths.size(); i++)
			{
				paths.erase(paths.begin() + indexValidPaths.at(i));
				indexValidPaths = updateIndexValidPaths(indexValidPaths, i);
			}
			//remove os caminhos que j? ultrapassam em tempo a pior solu??o, pode ter de ser otimizada, se a liga??o for quase direta elimina todas as op??es
			if (!completedPaths.empty())
				paths = removeSlowerPaths(paths, fasterCompleted(completedPaths));

		}

		//Enquanto n?o tivermos, neste caso 3 solu??es (pode ser mudado), vai procurar op??es de caminhos
		if (completedPaths.size() < 3)
		{
			unsigned int count = paths.size();

			//numa primeira itera??o v? conex?es, excluindo a paragem anterior, a inicial
			if (iterations == 0)
			{
				unsigned int sizePaths = paths.size();
				for (int i = 0; i < sizePaths; i++)
				{
					connections = stopsWithConnection(paths[i][paths[i].size() - 1].stop, firstStop, lines);
					for (int j = 0; j < connections.size(); j++)
					{
						std::vector <connectionInfo> temp;
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
			//em itera??es posteriores procura conex?es, excluindo a paragem anterior
			else if (iterations > 0 && iterations< 10)
			{
				unsigned int sizePaths = paths.size();
				std::vector <std::vector <connectionInfo>> originalPaths = paths;
				for (int i = 0; i < sizePaths; i++)
				{
					connections = stopsWithConnection(originalPaths[i][originalPaths[i].size() - 1].stop, originalPaths[i][originalPaths[i].size() - 2].stop, lines);
					for (int j = 0; j < connections.size(); j++)
					{
						std::vector <connectionInfo> temp;
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
			//Est? a parar na 10+ itera??o mas pode ser otimizado
			else if (iterations > 10) continueSearch = false;


			iterations++;
		}
		else continueSearch = false;

	}
	//parte final
	if (!completedPaths.empty())
	{
		//de todos os caminhos completos refina de modo a selecionar at? os tr?s melhores 
		std::vector <std::vector <connectionInfo>> refinedPaths = bestPaths(completedPaths);
		refinedPaths = ultimateRefinery(refinedPaths);
		//adiciona a primeira paragem, falta mudar para p?r a paragem inicial, e tamb?m contabilizar e aconselhar sobre atrasos de mudan?as de linha
		connectionInfo originStop;
		originStop.line = 0;
		originStop.stop = firstStop;
		originStop.time = 0;

		//Adiciona a paragem inicial ao vetor no inicio
		for (int i = 0; i < refinedPaths.size(); i++)
			refinedPaths.at(i).insert(refinedPaths.at(i).begin(), originStop);

		printFinalPaths(refinedPaths, firstStop, lastStop);

	}
	else std::cout << "O algoritmo nao encontrou solucao" << std::endl;
}
