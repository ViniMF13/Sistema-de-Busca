#ifndef INDICEPACOTES_H
#define INDICEPACOTES_H
#include "Evento.hpp"
#include "IndiceEventos.hpp"
#include <stdio.h>
#include <cstring>
#include <cstdio>
#include <string>

struct NoPacote {
    int key;
    NoPacote* left;
    NoPacote* right;
    int height;

    //ponteiros para primeiro e ultimo evento relacionado ao pacote
    Node* primeiroEvento;
    Node* ultimoEvento;
    int tamanhoLista;

    NoPacote(int k) : key(k), left(nullptr), right(nullptr), height(1), primeiroEvento(nullptr), ultimoEvento(nullptr), tamanhoLista(0) {}
};

class IndicePacotes {    
    private:
    NoPacote* root;
    
    NoPacote* insertNode(NoPacote* node, int key);
    NoPacote* search(NoPacote* node, const int key);

    int getHeight(NoPacote* node);
    int getBalance(NoPacote* node);
    void updateHeight(NoPacote* node);
    NoPacote* rotateRight(NoPacote* y);
    NoPacote* rotateLeft(NoPacote* x);
    NoPacote* balance(NoPacote* node);

    public:
    IndicePacotes();
    ~IndicePacotes();
    void inserir(int key);
    NoPacote* buscarPacote(const int key);
    void setPrimeiroEvento(NoPacote* pacote, Node* evt);
    void setUltimoEvento(NoPacote* pacote, Node* evt);

    void printInOrder();
    void inOrder(NoPacote* node);
    void freeMemory(NoPacote* node);
};

#endif