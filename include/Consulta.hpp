#ifndef CONSULTA_H
#define CONSULTA_H
#include "Evento.hpp"
#include <cstring>
#include <cstdio>
#include <string>

class Consulta {
    private:     
    int tipo; // 1 = Cliente, 2 = Pacote
    int tempo;
    int idPacote;
    std::string cliente;
    Evento** listaEventos; // lista de ponteiros para eventos
    int tamanho;

    public:
    Consulta();
    ~Consulta();
    void inicializar(int tip, int tem, int id, std::string cl, int n);

    //getters
    int getTipo();
    int getTempo();
};

#endif