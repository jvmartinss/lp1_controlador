#include "transporte.h"

Transporte::Transporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual)
    : nome(nome), tipo(tipo), capacidade(capacidade), velocidade(velocidade), distancia_entre_descansos(distancia_entre_descansos), tempo_de_descanso(tempo_de_descanso), localAtual(localAtual), distancia_percorrida(0), horas_descanso_restantes(0) {}

std::string Transporte::getNome() const {
    return nome;
}

char Transporte::getTipo() const {
    return tipo;
}

int Transporte::getCapacidade() const {
    return capacidade;
}

Cidade* Transporte::getLocalAtual() const {
    return localAtual;
}

void Transporte::setLocalAtual(Cidade* local) {
    localAtual = local;
}

bool Transporte::podeViajar() const {
    return horas_descanso_restantes == 0;
}

void Transporte::avancarHoras(int horas) {
    if (horas_descanso_restantes > 0) {
        horas_descanso_restantes = std::max(0, horas_descanso_restantes - horas);
    }
}

void Transporte::viajar(int distancia) {
    distancia_percorrida += distancia;
    if (distancia_percorrida >= distancia_entre_descansos) {
        distancia_percorrida = 0;
        horas_descanso_restantes = tempo_de_descanso;
    }
}

int Transporte::calcularTempoViagem(int distancia) const {
    return std::ceil(static_cast<double>(distancia) / velocidade);
}


int Transporte::getVelocidade() const {
    return velocidade;
}

int Transporte::getDistanciaEntreDescansos() const {
    return distancia_entre_descansos;
}

int Transporte::getTempoDeDescanso() const {
    return tempo_de_descanso;
}
