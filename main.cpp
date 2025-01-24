#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <fstream>
#include <cmath>

#include "cidade.h"
#include "trajeto.h"
#include "transporte.h"
#include "passageiro.h"
#include "viagem.h"
#include "controlador_de_transito.h"


void exibirMenu() {
    std::cout << "\n---------------------------------------------------\n";
    std::cout << "\n---------- Controlador de Viagens -----------------\n";
    std::cout << "------------- 1. Cadastrar Cidade -------------------\n";
    std::cout << "------------- 2. Cadastrar Trajeto ------------------\n";
    std::cout << "------------- 3. Cadastrar Transporte ---------------\n";
    std::cout << "------------- 4. Cadastrar Passageiro ---------------\n";
    std::cout << "------------- 5. Iniciar Viagem ---------------------\n";
    std::cout << "------------- 6. Avançar Horas ----------------------\n";
    std::cout << "------------- 7. Relatar Estado ---------------------\n";
    std::cout << "------------- 8. Salvar Relatório -------------------\n";
    std::cout << "------------- 9. Sair -------------------------------\n";
    std::cout << "------------- Escolha uma opção: --------------------";
    std::cout << "\n---------------------------------------------------\n";
}

int main() {
    ControladorDeTransito controlador;
    int opcao;

    do {
        exibirMenu();
        std::cin >> opcao;
        std::cin.ignore(); // Limpar buffer do cin

        switch (opcao) {
            case 1: {
                std::string nome;
                std::cout << "Digite o nome da cidade: ";
                std::getline(std::cin, nome);
                controlador.cadastrarCidade(nome);
                break;
            }
            case 2: {
                std::string origem, destino;
                char tipo;
                int distancia;
                std::cout << "Digite o nome da cidade de origem: ";
                std::getline(std::cin, origem);
                std::cout << "Digite o nome da cidade de destino: ";
                std::getline(std::cin, destino);
                std::cout << "Digite o tipo de trajeto (A - Aquático, T - Terrestre): ";
                std::cin >> tipo;
                std::cout << "Digite a distância (em km): ";
                std::cin >> distancia;
                std::cin.ignore();
                controlador.cadastrarTrajeto(origem, destino, tipo, distancia);
                break;
            }
            case 3: {
                std::string nome, localAtual;
                char tipo;
                int capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso;
                std::cout << "Digite o nome do transporte: ";
                std::getline(std::cin, nome);
                std::cout << "Digite o tipo do transporte (A - Aquático, T - Terrestre): ";
                std::cin >> tipo;
                std::cout << "Digite a capacidade do transporte: ";
                std::cin >> capacidade;
                std::cout << "Digite a velocidade do transporte (km/h): ";
                std::cin >> velocidade;
                std::cout << "Digite a distância máxima entre descansos (km): ";
                std::cin >> distancia_entre_descansos;
                std::cout << "Digite o tempo de descanso (em horas): ";
                std::cin >> tempo_de_descanso;
                std::cin.ignore();
                std::cout << "Digite o nome da cidade atual: ";
                std::getline(std::cin, localAtual);
                controlador.cadastrarTransporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, localAtual);
                break;
            }
            case 4: {
                std::string nome, localAtual;
                std::cout << "Digite o nome do passageiro: ";
                std::getline(std::cin, nome);
                std::cout << "Digite o nome da cidade atual: ";
                std::getline(std::cin, localAtual);
                controlador.cadastrarPassageiro(nome, localAtual);
                break;
            }
            case 5: {
                std::string nomeTransporte, origem, destino;
                int numPassageiros;
                std::cout << "Digite o nome do transporte: ";
                std::getline(std::cin, nomeTransporte);
                std::cout << "Digite o nome da cidade de origem: ";
                std::getline(std::cin, origem);
                std::cout << "Digite o nome da cidade de destino: ";
                std::getline(std::cin, destino);
                std::cout << "Digite o número de passageiros: ";
                std::cin >> numPassageiros;
                std::cin.ignore();
                std::vector<std::string> nomesPassageiros(numPassageiros);
                for (int i = 0; i < numPassageiros; ++i) {
                    std::cout << "Digite o nome do passageiro " << i + 1 << ": ";
                    std::getline(std::cin, nomesPassageiros[i]);
                }
                controlador.iniciarViagem(nomeTransporte, nomesPassageiros, origem, destino);
                break;
            }
            case 6: {
                int horas;
                std::cout << "Digite o número de horas a avançar: ";
                std::cin >> horas;
                std::cin.ignore();
                controlador.avancarHoras(horas);
                break;
            }
            case 7:
                controlador.relatarEstado();
                break;
            case 8:
                controlador.salvarRelatorio();
                break;
            case 9:
                std::cout << "Saindo do sistema...\n";
                break;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (opcao != 9);

    return 0;
}
