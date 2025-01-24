#include "passageiro.h"
#include <fstream>
#include <iostream>

Passageiro::Passageiro(std::string nome, Cidade* localAtual)
    : nome(nome), localAtual(localAtual) {}

std::string Passageiro::getNome() const {
    return nome;
}

Cidade* Passageiro::getLocalAtual() const {
    return localAtual;
}

void Passageiro::setLocalAtual(Cidade* local) {
    localAtual = local;
}

// Função para salvar a lista de passageiros em um arquivo CSV
void Passageiro::salvarPassageirosEmCSV(const std::vector<Passageiro*>& passageiros) {
    std::ofstream arquivo("passageiros.csv");
    if (arquivo.is_open()) {
        // Escreve o cabeçalho
        arquivo << "Nome,Local Atual\n";

        // Escreve os dados dos passageiros
        for (const auto& passageiro : passageiros) {
            arquivo << passageiro->getNome() << "," 
                    << (passageiro->getLocalAtual() ? passageiro->getLocalAtual()->getNome() : "Desconhecido") 
                    << "\n";
        }

        arquivo.close();
        std::cout << "Passageiros salvos em passageiros.csv" << std::endl;
    } else {
        std::cerr << "Erro ao abrir o arquivo para salvar os passageiros." << std::endl;
    }
}
