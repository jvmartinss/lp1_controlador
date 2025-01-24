#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>
#include <vector>
#include "cidade.h"  

class Passageiro {
public:
    // Construtor
    Passageiro(std::string nome, Cidade* localAtual);

    // Métodos para acessar os atributos
    std::string getNome() const;
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* local);

    // Função para salvar os passageiros em um arquivo CSV
    static void salvarPassageirosEmCSV(const std::vector<Passageiro*>& passageiros);

private:
    std::string nome;
    Cidade* localAtual;
};

#endif 
