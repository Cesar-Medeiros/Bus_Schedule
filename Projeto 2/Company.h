#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Line.h"
#include "Driver.h"



class Empresa{
 private:
 std::string nome;
 std::vector<Driver> condutores;
 std::vector<Line> linhas;
 public:
	 Empresa(std::string nome, std::string fichCondutores, std::string fichLinhas);
  // metodos get
	 std::string getNome() const;
  // metodos set
  // outros metodos
  void distribuiServico(); // funcao que implementa a afectacao de servico
};
