#include "../include/IndicePacotes.hpp"
#include <iostream>
using namespace std;

IndicePacotes::IndicePacotes() : root(nullptr) {}

IndicePacotes::~IndicePacotes() {
    freeMemory(root);
}

void IndicePacotes::inserir(int key) {
    root = insertNode(root, key);
}

void IndicePacotes::setPrimeiroEvento(NoPacote* pacote, Node* evento){
    pacote->primeiroEvento = evento;
}

void IndicePacotes::setUltimoEvento(NoPacote* pacote, Node* evento){
     pacote->ultimoEvento = evento;
     pacote->tamanhoLista++;
}

void IndicePacotes::printInOrder() {
    inOrder(root);
}

void IndicePacotes::inOrder(NoPacote* node) {
    if (node) {
        inOrder(node->left);

        printf("PC %03d\n", node->key);

        inOrder(node->right);
    }
}

void IndicePacotes::freeMemory(NoPacote* node) {
    if (node) {

/*
        NoLista* atual = node->inicio;
        while (atual) {
            NoLista* temp = atual;
            atual = atual->prox;
            delete temp;
        }
*/

        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
}

NoPacote* IndicePacotes::buscarPacote(const int key) {
    return search(root, key);
}


//prinvate
int IndicePacotes::getHeight(NoPacote* node) {
    return node ? node->height : 0;
}

int IndicePacotes::getBalance(NoPacote* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void IndicePacotes::updateHeight(NoPacote* node) {
    if (node)
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

NoPacote* IndicePacotes::rotateRight(NoPacote* y) {
    NoPacote* x = y->left;
    NoPacote* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

NoPacote* IndicePacotes::rotateLeft(NoPacote* x) {
    NoPacote* y = x->right;
    NoPacote* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

NoPacote* IndicePacotes::balance(NoPacote* node) {
    updateHeight(node);
    int balanceFactor = getBalance(node);

    if (balanceFactor > 1) {
        if (getBalance(node->left) < 0)
            node->left = rotateLeft(node->left); // Caso Left-Right
        return rotateRight(node); // Caso Left-Left
    }
    if (balanceFactor < -1) {
        if (getBalance(node->right) > 0)
            node->right = rotateRight(node->right); // Caso Right-Left
        return rotateLeft(node); // Caso Right-Right
    }

    return node;
}

NoPacote* IndicePacotes::insertNode(NoPacote* node, int key) {
    if (!node){
        NoPacote* newNode = new NoPacote(key);
        return newNode;
    } 

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // Ignorar duplicatas

    return balance(node);
}

NoPacote* IndicePacotes::search(NoPacote* node, const int key) {
    if (!node || node->key == key) return node;
    if (key < node->key) return search(node->left, key);
    else return search(node->right, key);
}


