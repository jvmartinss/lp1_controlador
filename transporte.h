#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include <string>
#include <algorithm> 
#include <cmath> 
#include "cidade.h"

class Transporte {
private:
    std::string nome;
    char tipo;
    int capacidade;
    int velocidade;
    int distancia_entre_descansos;
    int tempo_de_descanso;
    Cidade* localAtual;
    int distancia_percorrida;
    int horas_descanso_restantes;

public:
    int getVelocidade() const;
    int getDistanciaEntreDescansos() const;
    int getTempoDeDescanso() const;
    Transporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual);

    std::string getNome() const;
    char getTipo() const;
    int getCapacidade() const;
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* local);

    bool podeViajar() const;
    void avancarHoras(int horas);
    void viajar(int distancia);
    int calcularTempoViagem(int distancia) const;
};

#endif
