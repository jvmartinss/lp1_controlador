# Controlador de Viagens

Este projeto é um sistema de gerenciamento de viagens que permite cadastrar cidades, trajetos, transportes e passageiros, além de planejar e monitorar viagens entre diferentes localidades. O sistema é interativo e opera em um menu principal com várias opções para realizar as operações.

## Funcionalidades

1. **Cadastro de Cidades**
   - Permite cadastrar cidades que serão utilizadas no planejamento das viagens.

2. **Cadastro de Trajetos**
   - Define as conexões entre as cidades, especificando o tipo de trajeto (terrestre ou aquático) e a distância.

3. **Cadastro de Transportes**
   - Cadastra veículos com características específicas, como capacidade, velocidade, e parâmetros relacionados a descanso e distância percorrida.

4. **Cadastro de Passageiros**
   - Registra passageiros no sistema, associando-os a uma cidade de origem.

5. **Iniciar Viagem**
   - Planeja uma viagem, associando um transporte e um grupo de passageiros a um trajeto definido entre cidades.

6. **Avançar Horas**
   - Simula o avanço do tempo, atualizando o progresso das viagens em andamento e o estado dos transportes.

7. **Relatar Estado**
   - Exibe o estado atual do sistema, incluindo informações sobre viagens, transportes e passageiros.

8. **Salvar Relatório**
   - Salva as informações de passageiros e viagens em arquivos CSV para consulta futura.

## Estrutura do Projeto

### **Arquivos principais**

- `main.cpp`: Contém a lógica principal do programa e o menu interativo.
- `controlador_de_transito.h` e `controlador_de_transito.cpp`: Gerencia o controle geral de todas as entidades do sistema (cidades, trajetos, transportes, passageiros e viagens).
- `cidade.h` e `cidade.cpp`: Representa as cidades cadastradas no sistema.
- `trajeto.h` e `trajeto.cpp`: Define os trajetos entre as cidades, incluindo o tipo e a distância.
- `transporte.h` e `transporte.cpp`: Implementa os transportes, com detalhes como capacidade, velocidade, descanso, e gerenciamento do local atual.
- `passageiro.h` e `passageiro.cpp`: Modela os passageiros e inclui funcionalidade para salvar dados em arquivos CSV.
- `viagem.h` e `viagem.cpp`: Gerencia as viagens, incluindo o progresso, o transporte associado, os passageiros e os trajetos.

### **Estrutura de Dados**

#### `Cidade`
- Representa uma cidade com um nome.

#### `Trajeto`
- Define uma rota entre duas cidades, incluindo o tipo de trajeto (aquático ou terrestre) e a distância em quilômetros.

#### `Transporte`
- Inclui características como:
  - Nome
  - Tipo (aquático ou terrestre)
  - Capacidade máxima de passageiros
  - Velocidade em km/h
  - Distância máxima entre descansos
  - Tempo necessário de descanso

#### `Passageiro`
- Armazena o nome e a localização atual de um passageiro.
- Possui funcionalidade para salvar informações em arquivos CSV.

#### `Viagem`
- Gerencia a viagem associando transporte, passageiros, origem e destino.
- Controla o progresso da viagem e atualiza os estados dos participantes e do transporte.

#### `ControladorDeTransito`
- Centraliza o gerenciamento de todas as entidades, permitindo realizar operações como cadastro, planejamento de viagens, avanço de tempo e salvamento de relatórios.

## Como Usar

### **Requisitos**
- Compilador C++ compatível com o padrão C++11 ou superior.
- Ambiente configurado para compilar e executar programas C++.

### **Passo a Passo**
1. Compile o projeto usando o comando:
   ```bash
   g++ -o controlador main.cpp controlador_de_transito.cpp cidade.cpp trajeto.cpp transporte.cpp passageiro.cpp viagem.cpp
   ```

2. Execute o programa:
   ```bash
   ./controlador
   ```

3. Navegue pelo menu interativo para realizar as operações desejadas.

## Fluxo do Menu

1. **Cadastrar Cidade**
   - Insira o nome da cidade a ser cadastrada.

2. **Cadastrar Trajeto**
   - Insira os nomes das cidades de origem e destino, o tipo de trajeto (T para terrestre, A para aquático), e a distância em quilômetros.

3. **Cadastrar Transporte**
   - Forneça informações como nome, tipo, capacidade, velocidade, distância máxima entre descansos, tempo de descanso e localização inicial.

4. **Cadastrar Passageiro**
   - Insira o nome do passageiro e a cidade onde ele está atualmente.

5. **Iniciar Viagem**
   - Escolha o transporte, cidade de origem, destino e passageiros que participarão da viagem.

6. **Avançar Horas**
   - Simule o avanço do tempo, atualizando o progresso das viagens e o estado dos transportes.

7. **Relatar Estado**
   - Exibe um resumo das viagens, transportes e passageiros.

8. **Salvar Relatório**
   - Salva informações sobre os passageiros em um arquivo CSV (`passageiros.csv`).




## Autor
Projeto desenvolvido por [João Victor Martins de Almeida] e [Thiago Araújo Benevides]  como parte de um sistema de controle de viagens em C++.

