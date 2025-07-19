#ifndef LISTAEVENTOS_H
#define LISTAEVENTOS_H
#include "IndiceCliente.hpp"
#include "IndicePacotes.hpp"
#include "IndiceEventos.hpp"
#include "Evento.hpp"


struct NoEvento {
    Evento evento;
    NoEvento* prox;
};

class ListaEventos {
    private:
    NoEvento* eventos; 
    int tamanhoEventos;
    
    public:
    ListaEventos();
    ~ListaEventos();
    void processar(std::ifstream& entrada, IndiceClientes &indiceC, IndicePacotes &indiceP, IndiceEventos &indiceE, int &count);
    Evento* inserirEvento(const Evento& p);
    
    void gerarRespostasCliente(NoCliente* cliente, IndicePacotes &indiceP);
    void gerarRespostasPacote(NoPacote* pacote, IndiceEventos &indiceE);

    void imprimir();
    int getTamanho();
    void destruir();
};

#endif