
#include "controlador_de_transito.h"
#include <sstream>
#include <algorithm> // Para transformações de string

ControladorDeTransito::ControladorDeTransito() {
    std::cout << "Controlador de Trânsito iniciado!" << std::endl;
    carregarPassageirosCSV(); 
    carregarTransportesCSV(); 
    carregarTrajetosCSV(); 
    carregarViagensCSV(); 
    carregarRelatorio(); // Carregar cidades e trajetos ao inicia
}

ControladorDeTransito::~ControladorDeTransito() {
    for (auto cidade : cidades) delete cidade;
    for (auto transporte : transportes) delete transporte;
    for (auto passageiro : passageiros) delete passageiro;
    for (auto trajeto : trajetos) delete trajeto;
    for (auto viagem : viagens) delete viagem;
}

void ControladorDeTransito::carregarPassageirosCSV() {
    std::ifstream arquivo("passageiros.csv");
    if (!arquivo.is_open()) return; // Se não existir, não faz nada

    std::string linha;
    getline(arquivo, linha); // Ignorar cabeçalho

    while (getline(arquivo, linha)) {
        std::istringstream ss(linha);
        std::string nome, localAtual;

        getline(ss, nome, ',');
        getline(ss, localAtual, ',');

        Cidade* cidade = findCidade(localAtual);
        if (cidade) {
            passageiros.push_back(new Passageiro(nome, cidade));
        }
    }

    arquivo.close();
}

void ControladorDeTransito::carregarTransportesCSV() {
    std::ifstream arquivo("transportes.csv");
    if (!arquivo.is_open()) return; 

    std::string linha;
    getline(arquivo, linha); // Ignorar cabeçalho

    while (getline(arquivo, linha)) {
        std::istringstream ss(linha);
        std::string nome, tipoStr, capacidadeStr, velocidadeStr, distanciaDescansoStr, tempoDescansoStr, localAtual;

        getline(ss, nome, ',');
        getline(ss, tipoStr, ',');
        getline(ss, capacidadeStr, ',');
        getline(ss, velocidadeStr, ',');
        getline(ss, distanciaDescansoStr, ',');
        getline(ss, tempoDescansoStr, ',');
        getline(ss, localAtual, ',');

        char tipo = tipoStr[0];
        int capacidade = std::stoi(capacidadeStr);
        int velocidade = std::stoi(velocidadeStr);
        int distanciaDescanso = std::stoi(distanciaDescansoStr);
        int tempoDescanso = std::stoi(tempoDescansoStr);

        Cidade* cidade = findCidade(localAtual);
        if (cidade) {
            transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distanciaDescanso, tempoDescanso, cidade));
        }
    }

    arquivo.close();
}

void ControladorDeTransito::carregarTrajetosCSV() {
    std::ifstream arquivo("trajetos.csv");
    if (!arquivo.is_open()) return; 

    std::string linha;
    getline(arquivo, linha); // Ignorar cabeçalho

    while (getline(arquivo, linha)) {
        std::istringstream ss(linha);
        std::string origem, destino, tipoStr, distanciaStr;

        getline(ss, origem, ',');
        getline(ss, destino, ',');
        getline(ss, tipoStr, ',');
        getline(ss, distanciaStr, ',');

        char tipo = tipoStr[0];
        int distancia = std::stoi(distanciaStr);

        Cidade* cidadeOrigem = findCidade(origem);
        Cidade* cidadeDestino = findCidade(destino);
        if (cidadeOrigem && cidadeDestino) {
            trajetos.push_back(new Trajeto(cidadeOrigem, cidadeDestino, tipo, distancia));
        } else {
            std::cerr << "Erro ao carregar trajeto: Cidades inválidas (" << origem << ", " << destino << ")." << std::endl;
        }
    }

    arquivo.close();
}

void ControladorDeTransito::salvarTrajetosCSV() {
    std::ofstream arquivo("trajetos.csv");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de trajetos." << std::endl;
        return;
    }

    arquivo << "Origem,Destino,Tipo,Distancia\n";
    for (const auto& trajeto : trajetos) {
        arquivo << trajeto->getOrigem()->getNome() << ","
                << trajeto->getDestino()->getNome() << ","
                << trajeto->getTipo() << ","
                << trajeto->getDistancia() << "\n";
    }

    arquivo.close();
}

void ControladorDeTransito::carregarViagensCSV() {
    std::ifstream arquivo("viagens.csv");
    if (!arquivo.is_open()) return;

    std::string linha;
    getline(arquivo, linha); 

    while (getline(arquivo, linha)) {
        std::istringstream ss(linha);
        std::string nomePassageiro, nomeTransporte, nomeOrigem, nomeDestino;

        getline(ss, nomePassageiro, ',');
        getline(ss, nomeTransporte, ',');
        getline(ss, nomeOrigem, ',');
        getline(ss, nomeDestino, ',');

        Passageiro* passageiro = findPassageiro(nomePassageiro);
        Transporte* transporte = findTransporte(nomeTransporte);
        Cidade* origem = findCidade(nomeOrigem);
        Cidade* destino = findCidade(nomeDestino);

        if (passageiro && transporte && origem && destino) {
            viagens.push_back(new Viagem(transporte, {passageiro}, origem, destino));
        } else {
            std::cerr << "Erro ao carregar viagem: Dados inválidos." << std::endl;
        }
    }

    arquivo.close();
}

void ControladorDeTransito::salvarViagensCSV() {
    std::ofstream arquivo("viagens.csv");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de viagens." << std::endl;
        return;
    }

    arquivo << "Passageiro,Transporte,Origem,Destino\n";
    for (const auto& viagem : viagens) {
        arquivo << viagem->getPassageiros().front()->getNome() << ","
                << viagem->getTransporte()->getNome() << ","
                << viagem->getOrigem()->getNome() << ","
                << viagem->getDestino()->getNome() << "\n";
    }

    arquivo.close();
}

void ControladorDeTransito::carregarRelatorio() {
    std::ifstream arquivo("relatorio_cidades.csv");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de cidades." << std::endl;
        return;
    }

    std::string linha;
    while (getline(arquivo, linha)) {
        if (linha.empty() || linha.find("Cidade Cadastrada,") == std::string::npos) continue;

        // Normalizar e verificar
        std::string nomeCidade = normalizarNome(linha.substr(linha.find(",") + 1));
        if (!findCidade(nomeCidade)) {
            cidades.push_back(new Cidade(nomeCidade));
            std::cout << "Cidade \"" << nomeCidade << "\" carregada do arquivo." << std::endl;
        }
    }

    arquivo.close();
}



void ControladorDeTransito::salvarRelatorio() {
    try {
        std::ofstream arquivoCidades("relatorio_cidades.csv", std::ios::app);
        if (!arquivoCidades.is_open()) throw std::ios_base::failure("Erro ao abrir o arquivo de cidades.");

        for (const auto& cidade : cidades) {
            arquivoCidades << "Cidade Cadastrada," << cidade->getNome() << "\n";
        }
        arquivoCidades.close();

        std::ofstream arquivoPassageiros("passageiros.csv", std::ios::app);
        if (!arquivoPassageiros.is_open()) throw std::ios_base::failure("Erro ao abrir o arquivo de passageiros.");

        for (const auto& passageiro : passageiros) {
            arquivoPassageiros << passageiro->getNome() << "," << (passageiro->getLocalAtual() ? passageiro->getLocalAtual()->getNome() : "Desconhecido") << "\n";
        }
        arquivoPassageiros.close();

        std::ofstream arquivoTransportes("transportes.csv");
        if (!arquivoTransportes.is_open()) throw std::ios_base::failure("Erro ao abrir o arquivo de transportes.");

        arquivoTransportes << "Nome,Tipo,Capacidade,Velocidade,DistanciaDescanso,TempoDescanso,LocalAtual\n";
        for (const auto& transporte : transportes) {
            arquivoTransportes << transporte->getNome() << ","
                               << transporte->getTipo() << ","
                               << transporte->getCapacidade() << ","
                               << transporte->getVelocidade() << ","
                               << transporte->getDistanciaEntreDescansos() << ","
                               << transporte->getTempoDeDescanso() << ","
                               << transporte->getLocalAtual()->getNome() << "\n";
        }
        arquivoTransportes.close();

        // Adicionando a chamada para salvar os trajetos
        salvarTrajetosCSV();

        std::cout << "Relatórios salvos com sucesso!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro ao salvar relatório: " << e.what() << std::endl;
    }
}



void ControladorDeTransito::cadastrarCidade(const std::string& nome) {
    if (findCidade(nome)) {
        std::cout << "A cidade \"" << nome << "\" já está cadastrada." << std::endl;
        return;
    }

    cidades.push_back(new Cidade(nome));
    std::cout << "Cidade \"" << nome << "\" cadastrada com sucesso." << std::endl;
}

void ControladorDeTransito::cadastrarPassageiro(const std::string& nome, const std::string& localAtual) {
    Cidade* local = findCidade(localAtual);
    if (local) {
        passageiros.push_back(new Passageiro(nome, local));
        std::cout << "Passageiro \"" << nome << "\" cadastrado com sucesso na cidade " << localAtual << "." << std::endl;
    } else {
        std::cerr << "Erro: Local inválido para passageiro." << std::endl;
    }
}

std::string ControladorDeTransito::normalizarNome(const std::string& nome) {
    std::string nomeNormalizado = nome;
    nomeNormalizado.erase(std::remove_if(nomeNormalizado.begin(), nomeNormalizado.end(), isspace), nomeNormalizado.end());
    std::transform(nomeNormalizado.begin(), nomeNormalizado.end(), nomeNormalizado.begin(), ::tolower);
    return nomeNormalizado;
}

Cidade* ControladorDeTransito::findCidade(const std::string& nome) {
    std::string nomeNormalizado = normalizarNome(nome);
    for (auto& cidade : cidades) {
        if (normalizarNome(cidade->getNome()) == nomeNormalizado) {
            return cidade;
        }
    }
    return nullptr;
}

#include "controlador_de_transito.h"

Passageiro* ControladorDeTransito::findPassageiro(const std::string& nome) {
    for (Passageiro* passageiro : passageiros) {
        if (passageiro->getNome() == nome) {
            return passageiro;
        }
    }
    return nullptr; 
}

Transporte* ControladorDeTransito::findTransporte(const std::string& nome) {
    for (Transporte* transporte : transportes) {
        if (transporte->getNome() == nome) {
            return transporte;
        }
    }
    return nullptr;  
}



void ControladorDeTransito::avancarHoras(int horas) {
    for (auto viagem : viagens) {
        viagem->avancarHoras(horas);
    }
    std::cout << "Tempo avançado em " << horas << " horas." << std::endl;
}

void ControladorDeTransito::relatarEstado() {
    std::cout << "Relatório de Estado do Sistema:" << std::endl;
    for (const auto& cidade : cidades) {
        std::cout << "Cidade: " << cidade->getNome() << std::endl;
    }
    for (const auto& transporte : transportes) {
        std::cout << "Transporte: " << transporte->getNome() << " - Capacidade: " << transporte->getCapacidade() << std::endl;
    }
    for (const auto& passageiro : passageiros) {
        std::cout << "Passageiro: " << passageiro->getNome() << " - Local Atual: " << (passageiro->getLocalAtual() ? passageiro->getLocalAtual()->getNome() : "Desconhecido") << std::endl;
    }
}

void ControladorDeTransito::cadastrarTrajeto(const std::string& origem, const std::string& destino, char tipo, int duracao) {
    Cidade* cidadeOrigem = findCidade(origem);
    Cidade* cidadeDestino = findCidade(destino);

    if (cidadeOrigem && cidadeDestino) {
        trajetos.push_back(new Trajeto(cidadeOrigem, cidadeDestino, tipo, duracao));
        std::cout << "Trajeto de " << origem << " para " << destino << " cadastrado com sucesso." << std::endl;
    } else {
        std::cerr << "Erro ao cadastrar trajeto: Verifique as cidades." << std::endl;
    }
}

void ControladorDeTransito::iniciarViagem(const std::string& nomePassageiro, const std::vector<std::string>& paradas, const std::string& transporte, const std::string& horario) {
    Passageiro* passageiro = nullptr;
    for (auto p : passageiros) {
        if (p->getNome() == nomePassageiro) {
            passageiro = p;
            break;
        }
    }

    if (!passageiro) {
        std::cerr << "Erro: Passageiro \"" << nomePassageiro << "\" não encontrado." << std::endl;
        return;
    }

    std::vector<Cidade*> cidadesParadas;
    for (const auto& nomeParada : paradas) {
        Cidade* cidade = findCidade(nomeParada);
        if (cidade) {
            cidadesParadas.push_back(cidade);
        } else {
            std::cerr << "Erro: Cidade \"" << nomeParada << "\" não encontrada." << std::endl;
            return;
        }
    }

    Transporte* transp = nullptr;
    for (auto t : transportes) {
        if (t->getNome() == transporte) {
            transp = t;
            break;
        }
    }

    if (!transp) {
        std::cerr << "Erro: Transporte \"" << transporte << "\" não encontrado." << std::endl;
        return;
    }

    viagens.push_back(new Viagem(transp, std::vector<Passageiro*>{passageiro}, cidadesParadas.front(), cidadesParadas.back()));
    std::cout << "Viagem iniciada com sucesso para o passageiro \"" << nomePassageiro << "\"." << std::endl;
}

void ControladorDeTransito::cadastrarTransporte(const std::string& nome, char tipo, int capacidade, int velocidade, int distanciaEntreDescansos, int tempoDeDescanso, const std::string& localAtual) {
    Cidade* cidade = findCidade(localAtual);
    if (!cidade) {
        std::cerr << "Erro: Cidade \"" << localAtual << "\" não encontrada." << std::endl;
        return;
    }

    Transporte* transporte = new Transporte(nome, tipo, capacidade, velocidade, distanciaEntreDescansos, tempoDeDescanso, cidade);
    transportes.push_back(transporte);

    std::cout << "Transporte \"" << nome << "\" cadastrado com sucesso." << std::endl;
}


