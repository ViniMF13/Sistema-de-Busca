#ifndef INDICEEVENTOS_H
#define INDICEEVENTOS_H
#include "Evento.hpp"
#include <stdio.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <iomanip>
#include "Evento.hpp"

struct Node {
    std::string key;
    Node* left;
    Node* right;
    int height;

    Evento* evento; //ponteiro para evento na lista

    Node(std::string k) : key(k), left(nullptr), right(nullptr), height(1), evento(nullptr) {}
};

class IndiceEventos {    
    private:
    Node* root;  

    Node* insertNode(Node* node, std::string key);
    Node* search(Node* node, const std::string key);
    int getHeight(Node* node);
    int getBalance(Node* node);
    void updateHeight(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);

    public:
    IndiceEventos();
    ~IndiceEventos();
    
    void inserir(std::string key);
    Node* buscarEvento(const std::string key);
    void setPonteiro(Node* node, Evento*evt);
    Node* getBloodyRoots();

    void printInOrder();
    void printPcInorder(Node* node, int id);
    void inOrder(Node* root);

    void freeMemory(Node* node);
};

#endif