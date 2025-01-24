#include "viagem.h"
#include <iostream>

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino), emAndamento(false), horasEmTransito(0) {}

void Viagem::iniciarViagem() {
    if (transporte->podeViajar()) {
        emAndamento = true;
        transporte->setLocalAtual(nullptr);
    } else {
        std::cout << "O transporte precisa descansar antes de iniciar a viagem.\n";
    }
}

void Viagem::avancarHoras(int horas) {
    if (emAndamento) {
        horasEmTransito += horas;
        transporte->avancarHoras(horas);
        int tempoEstimado = transporte->calcularTempoViagem(calcularDistancia());
        if (horasEmTransito >= tempoEstimado) {
            emAndamento = false;
            transporte->setLocalAtual(destino);
            for (auto& passageiro : passageiros) {
                passageiro->setLocalAtual(destino);
            }
        }
    }
}

int Viagem::calcularDistancia() const {
    return origem->getNome() == destino->getNome() ? 0 : 1;
}

bool Viagem::isEmAndamento() const {
    return emAndamento;
}

Cidade* Viagem::getDestino() const {
    return destino;
}

// Implementações dos métodos adicionados
Transporte* Viagem::getTransporte() const {
    return transporte;
}

std::vector<Passageiro*> Viagem::getPassageiros() const {
    return passageiros;
}

Cidade* Viagem::getOrigem() const {
    return origem;
}
