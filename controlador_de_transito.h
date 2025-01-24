#ifndef CONTROLADOR_DE_TRANSITO_H
#define CONTROLADOR_DE_TRANSITO_H

#include <vector>
#include <string>
#include "cidade.h"
#include "transporte.h"
#include "trajeto.h"
#include "passageiro.h"
#include "viagem.h"

class ControladorDeTransito {
public:
    ControladorDeTransito();
    ~ControladorDeTransito();

    // Funções principais
    void carregarRelatorio();
    void salvarRelatorio();

    // Métodos de cadastro
    void cadastrarCidade(const std::string& nome);
    void cadastrarTrajeto(const std::string& nomeOrigem, const std::string& nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(const std::string& nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, const std::string& localAtual);
    void cadastrarPassageiro(const std::string& nome, const std::string& localAtual);

    // Controle de viagens
    void iniciarViagem(const std::string& nomeTransporte, const std::vector<std::string>& nomesPassageiros, const std::string& nomeOrigem, const std::string& nomeDestino);
    void avancarHoras(int horas);
    void relatarEstado();

private:
    // Métodos auxiliares
    Cidade* findCidade(const std::string& nome);
    Transporte* findTransporte(const std::string& nome);
    Passageiro* findPassageiro(const std::string& nome);

    // Atributos
    std::vector<Cidade*> cidades;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Trajeto*> trajetos;
    std::vector<Viagem*> viagens;
};

#endif // CONTROLADOR_DE_TRANSITO_H
