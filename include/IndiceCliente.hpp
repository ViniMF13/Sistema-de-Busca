#ifndef INDICECLIENTES_H
#define INDICECLIENTES_H
#include "Evento.hpp"
#include "IndicePacotes.hpp"
#include <stdio.h>
#include <cstring>
#include <cstdio>
#include <string>


struct NoId {
    int id;
    NoId* prox;

    NoId() : id(-1), prox(nullptr) {}
};

struct NoCliente {
    std::string key;
    NoCliente* left;
    NoCliente* right;
    int height;
    
    // lista de pacotes 
    NoId* head; 
    NoId* tail; 
    int tamanhoLista;

    NoCliente(std::string k) : key(k), left(nullptr), right(nullptr), height(1), head(nullptr), tail(nullptr), tamanhoLista(0) {}
};

class IndiceClientes {    
    private:
    NoCliente* root;

    NoCliente* insertNode(NoCliente* node, std::string key);
    NoCliente* search(NoCliente* node, const std::string& key);

    int getHeight(NoCliente* node);
    int getBalance(NoCliente* node);
    void updateHeight(NoCliente* node);
    NoCliente* rotateRight(NoCliente* y);
    NoCliente* rotateLeft(NoCliente* x);
    NoCliente* balance(NoCliente* node);

    public:
    IndiceClientes();
    ~IndiceClientes();
    void inserir(std::string key);
    NoCliente* buscarCliente(const std::string& key);
    void inserirPacote(NoCliente* node, int id);

    void printInOrder();
    void inOrder(NoCliente* node);
    void freeMemory(NoCliente* node);
};

#endif