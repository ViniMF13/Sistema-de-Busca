#include "../include/ListaEventos.hpp"
#include "../include/IndiceCliente.hpp"
#include "../include/IndicePacotes.hpp"
#include "../include/IndiceEventos.hpp"
#include "../include/Evento.hpp"
#include <iostream>
#include <fstream>   
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << "input.txt" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Erro: Não foi possível abrir o arquivo " << argv[1] << endl;
        return 1;
    }

    // inicializa as estruturas do sistema
    IndicePacotes indiceP;
    IndiceClientes indiceC;
    IndiceEventos indiceE;
    int count = 0;

    ListaEventos eventos;
    eventos.processar(file, indiceC, indiceP, indiceE, count);
    
    //printf("Pacotes:\n");
    //indiceP.printInOrder();

    //printf("Clientes:\n");
    //indiceC.printInOrder();
    
    //printf("Eventos: %d\n", eventos.getTamanho());
    //indiceE.printInOrder();
   
    return 0;
}

