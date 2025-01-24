#include "controlador_de_transito.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

ControladorDeTransito::ControladorDeTransito() {
    std::cout << "Controlador de Trânsito iniciado!" << std::endl;
}

ControladorDeTransito::~ControladorDeTransito() {
    for (auto cidade : cidades) delete cidade;
    for (auto transporte : transportes) delete transporte;
    for (auto passageiro : passageiros) delete passageiro;
    for (auto trajeto : trajetos) delete trajeto;
    for (auto viagem : viagens) delete viagem;
}

void ControladorDeTransito::carregarRelatorio() {
    std::ifstream arquivo("relatorio_viagens.csv"); // Alterado para ".csv"
    if (arquivo.is_open()) {
        std::string linha;
        while (getline(arquivo, linha)) {
            std::cout << linha << std::endl;
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para carregar o relatório." << std::endl;
    }
}

void ControladorDeTransito::salvarRelatorio() {
    try {
        std::ofstream arquivoCidades("relatorio_cidades.csv", std::ios::app);
        if (!arquivoCidades.is_open()) throw std::ios_base::failure("Erro ao abrir o arquivo de cidades.");

        for (const auto& cidade : cidades) {
            arquivoCidades << "Cidade Cadastrada, " << cidade->getNome() << "\n";
        }
        arquivoCidades.close();

        std::ofstream arquivoPassageiros("relatorio_passageiros.csv", std::ios::app);
        if (!arquivoPassageiros.is_open()) throw std::ios_base::failure("Erro ao abrir o arquivo de passageiros.");

        for (const auto& passageiro : passageiros) {
            arquivoPassageiros << "Passageiro, " << passageiro->getNome() << ", "
                               << passageiro->getLocalAtual()->getNome() << "\n";
        }
        arquivoPassageiros.close();

        std::ofstream arquivoTrajetos("relatorio_trajetos.csv", std::ios::app);
        if (!arquivoTrajetos.is_open()) throw std::ios_base::failure("Erro ao abrir o arquivo de trajetos.");

        for (const auto& trajeto : trajetos) {
            arquivoTrajetos << "Trajeto, " << trajeto->getOrigem()->getNome() << ", "
                            << trajeto->getDestino()->getNome() << ", "
                            << trajeto->getDistancia() << " km\n";
        }
        arquivoTrajetos.close();

        std::cout << "Relatórios salvos com sucesso!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro ao salvar relatório: " << e.what() << std::endl;
    }
}

void ControladorDeTransito::cadastrarCidade(const std::string& nome) {
    if (findCidade(nome)) {
        std::cerr << "Cidade já cadastrada: " << nome << std::endl;
        return;
    }
    cidades.push_back(new Cidade(nome));
}

void ControladorDeTransito::cadastrarTrajeto(const std::string& nomeOrigem, const std::string& nomeDestino, char tipo, int distancia) {
    Cidade* origem = findCidade(nomeOrigem);
    Cidade* destino = findCidade(nomeDestino);
    if (origem && destino) {
        trajetos.push_back(new Trajeto(origem, destino, tipo, distancia));
    } else {
        std::cerr << "Erro: Origem ou destino inválido." << std::endl;
    }
}

void ControladorDeTransito::cadastrarTransporte(const std::string& nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, const std::string& localAtual) {
    Cidade* local = findCidade(localAtual);
    if (local) {
        transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, local));
    } else {
        std::cerr << "Erro: Local inválido para transporte." << std::endl;
    }
}

void ControladorDeTransito::cadastrarPassageiro(const std::string& nome, const std::string& localAtual) {
    Cidade* local = findCidade(localAtual);
    if (local) {
        passageiros.push_back(new Passageiro(nome, local));
    } else {
        std::cerr << "Erro: Local inválido para passageiro." << std::endl;
    }
}

void ControladorDeTransito::iniciarViagem(const std::string& nomeTransporte, const std::vector<std::string>& nomesPassageiros, const std::string& nomeOrigem, const std::string& nomeDestino) {
    Transporte* transporte = findTransporte(nomeTransporte);
    Cidade* origem = findCidade(nomeOrigem);
    Cidade* destino = findCidade(nomeDestino);
    std::vector<Passageiro*> passageirosSelecionados;

    for (const auto& nome : nomesPassageiros) {
        Passageiro* passageiro = findPassageiro(nome);
        if (passageiro) {
            passageirosSelecionados.push_back(passageiro);
        }
    }

    if (transporte && origem && destino) {
        Viagem* viagem = new Viagem(transporte, passageirosSelecionados, origem, destino);
        viagem->iniciarViagem();
        viagens.push_back(viagem);
    } else {
        std::cerr << "Erro: Dados inválidos para iniciar a viagem." << std::endl;
    }
}

void ControladorDeTransito::avancarHoras(int horas) {
    for (auto& viagem : viagens) {
        viagem->avancarHoras(horas);
    }
}

void ControladorDeTransito::relatarEstado() {
    for (const auto& transporte : transportes) {
        std::cout << "Transporte: " << transporte->getNome() << ", Local: "
                  << (transporte->getLocalAtual() ? transporte->getLocalAtual()->getNome() : "Em trânsito") << std::endl;
    }
    for (const auto& passageiro : passageiros) {
        std::cout << "Passageiro: " << passageiro->getNome() << ", Local: "
                  << passageiro->getLocalAtual()->getNome() << std::endl;
    }
}

Cidade* ControladorDeTransito::findCidade(const std::string& nome) {
    for (auto& cidade : cidades) {
        if (cidade->getNome() == nome) {
            return cidade;
        }
    }
    return nullptr;
}

Transporte* ControladorDeTransito::findTransporte(const std::string& nome) {
    for (auto& transporte : transportes) {
        if (transporte->getNome() == nome) {
            return transporte;
        }
    }
    return nullptr;
}

Passageiro* ControladorDeTransito::findPassageiro(const std::string& nome) {
    for (auto& passageiro : passageiros) {
        if (passageiro->getNome() == nome) {
            return passageiro;
        }
    }
    return nullptr;
}
