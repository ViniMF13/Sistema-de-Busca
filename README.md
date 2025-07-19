# Sistema de consultas

Este projeto implementa um sistema de consultas de pacotes em uma rede logística de entregas. 

## 🧠 Objetivo

O objetivo é implementar um sistema de busca eficiente para um sistema logístico que contém grandes volumes de pacotes simultaneos.
O sistema Possibilita dois tipos de Consultas:
1. Pacote:
  - Dado o ID de um pacote, mostra o histórico de eventos do pacote até o momento atual.
2. Cliente:
  - Dado um remente ou destinatário, mostra os pacotes que estão cadastrados no seu nome.

## 🛠️ Estrutura do Projeto

```
├── src/
│   ├── main.cpp                # Função principal            
│   ├── Evento.cpp              # Representação de um Evento no sistema
│   ├── ListaEventos.cpp        # Lista de Eventos no Sistema
│   ├── IndiceClientes.cpp      # Indice para busca de clientess
│   ├── IndicePacotes.cpp       # Indice para busca de Pacotes
│   └── IndiceEventos.cpp       # Indice para busca de Eventos
├── include/                    # Headers correspondentes
├── bin/                        # Binários compilados
├── input.txt                   # Arquivo de entrada eventos
├── README.md                   # Este arquivo
└── Makefile                    # Compilação automatizada
```

## ▶️ Execução

### Compilar
```bash
make
```

### Executar
```bash
./bin/tp3.out input.txt
```

> O arquivo `input.txt` deve conter a configuração do sistema (parâmetros logísticos, matriz de conexões e pacotes a serem transportados).

## 📊 Análise Experimental

A simulação foi utilizada para investigar o impacto de diferentes fatores, como:

- Variação do número de eventos
- Quantidade de pacotes
- Quantidade de clientes

### Métricas observadas:
- Tempo médio de busca
- Tempo de execução do sistema 

Gráficos e tabelas estão disponíveis na documentação em LaTeX.

## 🔐 Robustez e Engenharia

O projeto aplica:
- Programação defensiva (checagens de ponteiros nulos, limites de array, falhas de abertura de arquivos)
- Liberação de memória dinâmica (destrutores customizados, `delete[]`)
- Validação de entradas e controle de estado

## 🧪 Tecnologias

- C++11
- Estruturas de dados: listas ligadas, Arvores AVl
- Algoritmos de rebalanceamento em arvore

## 📘 Documentação

A documentação técnica completa foi elaborada em LaTeX e inclui:
- Análise de complexidade de funções principais
- Estratégias de robustez
- Análise experimental com gráficos

## 📝 Licença

Este projeto é de uso acadêmico e pessoal. Sinta-se à vontade para estudar, modificar e expandir.
