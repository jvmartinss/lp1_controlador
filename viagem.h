#ifndef VIAGEM_H
#define VIAGEM_H

#include <vector>
#include <string>
#include "transporte.h"
#include "passageiro.h" 
#include "cidade.h"   

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    bool emAndamento;
    int horasEmTransito;

public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino);

    void iniciarViagem();
    void avancarHoras(int horas);
    int calcularDistancia() const;
    bool isEmAndamento() const;
    Cidade* getDestino() const;
};

#endif
