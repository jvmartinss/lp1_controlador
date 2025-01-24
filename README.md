# Controlador de Viagens

Este projeto implementa um sistema de controle de viagens, permitindo o gerenciamento de cidades, trajetos, transportes, passageiros e viagens. O sistema é interativo e opera por meio de um menu que permite realizar diversas operações, como cadastro de entidades e controle de viagens.

---

## Funcionalidades

1. **Cadastrar Cidades:**
   - Permite adicionar cidades ao sistema.
2. **Cadastrar Trajetos:**
   - Define trajetos entre cidades, especificando origem, destino, tipo (terrestre ou aquático) e distância.
3. **Cadastrar Transportes:**
   - Adiciona meios de transporte, incluindo informações como capacidade, velocidade e regras de descanso.
4. **Cadastrar Passageiros:**
   - Insere passageiros no sistema e vincula cada um a uma cidade inicial.
5. **Iniciar Viagem:**
   - Organiza uma viagem entre duas cidades, utilizando um transporte e transportando passageiros.
6. **Avançar Horas:**
   - Simula o progresso do tempo e atualiza o estado das viagens em andamento.
7. **Relatar Estado:**
   - Exibe informações sobre transportes e passageiros, como localização atual.
8. **Salvar Relatórios:**
   - Gera relatórios em arquivos CSV para cidades, passageiros e trajetos.

---

## Estrutura do Projeto

O sistema é composto por diversas classes, cada uma representando um aspecto do modelo:

### Classes Principais

1. **`Cidade`**
   - Representa uma cidade, identificada pelo seu nome.

2. **`Trajeto`**
   - Define um trajeto entre duas cidades, incluindo o tipo (terrestre ou aquático) e a distância.

3. **`Transporte`**
   - Representa um meio de transporte, com informações como capacidade, velocidade, distância entre descansos e tempo de descanso.

4. **`Passageiro`**
   - Representa um passageiro, com nome e localização atual.

5. **`Viagem`**
   - Gerencia a realização de uma viagem, incluindo transporte, passageiros, origem, destino e o progresso da viagem.

6. **`ControladorDeTransito`**
   - Coordena o funcionamento do sistema, gerenciando as entidades cadastradas e as interações entre elas.

7. **`main`**
   - Contém o menu interativo para interação com o sistema.

---

## Requisitos

- **Linguagem:** C++
- **Compilador:** Recomendado GCC ou equivalente com suporte a C++11 ou superior.
- **Bibliotecas Padrão:**
  - `<iostream>` para entrada e saída.
  - `<vector>` para armazenamento dinâmico.
  - `<string>` para manipulação de textos.
  - `<fstream>` para operações com arquivos.
  - `<cmath>` para cálculos matemáticos.
  - `<exception>` para tratamento de erros.

---

## Execução

1. Compile todos os arquivos com o seguinte comando:
   ```bash
   g++ -o controlador main.cpp cidade.cpp controlador_de_transito.cpp passageiro.cpp trajeto.cpp transporte.cpp viagem.cpp
   ```

2. Execute o programa:
   ```bash
   ./controlador
   ```

---

## Detalhes do Menu Interativo

O programa apresenta um menu com as seguintes opções:

1. **Cadastrar Cidade:** Solicita o nome da cidade e a adiciona ao sistema.
2. **Cadastrar Trajeto:** Solicita informações sobre origem, destino, tipo e distância do trajeto.
3. **Cadastrar Transporte:** Solicita informações sobre o transporte, como capacidade, velocidade e local atual.
4. **Cadastrar Passageiro:** Solicita o nome do passageiro e sua localização inicial.
5. **Iniciar Viagem:** Define um transporte, passageiros, origem e destino para iniciar uma viagem.
6. **Avançar Horas:** Simula o avanço do tempo e atualiza o estado do sistema.
7. **Relatar Estado:** Exibe informações sobre transportes e passageiros.
8. **Salvar Relatório:** Salva os dados do sistema em arquivos CSV.
9. **Sair:** Encerra o programa.

---

## Estrutura dos Arquivos de Relatório

- **`relatorio_cidades.csv`:** Contém a lista de cidades cadastradas.
- **`relatorio_passageiros.csv`:** Contém informações sobre os passageiros e suas localizações.
- **`relatorio_trajetos.csv`:** Contém informações sobre os trajetos cadastrados.

---

## Melhorias Futuras

- Implementar persistência de dados para carregamento ao reiniciar o programa.
- Adicionar suporte para editar ou remover entidades (cidades, transportes, etc.).
- Implementar validação de entrada mais robusta no menu.

---

## Autor
Projeto desenvolvido por [João Victor Martins de Almeida] e [Thiago Araújo Benevides]  como parte de um sistema de controle de viagens em C++.

