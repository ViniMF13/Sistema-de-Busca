#include "../include/IndiceEventos.hpp"
#include <iostream>
using namespace std;

IndiceEventos::IndiceEventos() : root(nullptr) {}

IndiceEventos::~IndiceEventos() {
    freeMemory(root);
}

void IndiceEventos::inserir(std::string key) {
    root = insertNode(root, key);
}

Node* IndiceEventos::buscarEvento(const std::string key) {
    return search(root, key);
}

void IndiceEventos::setPonteiro(Node* node, Evento* evt) {
    node->evento = evt;
}

Node* IndiceEventos::getBloodyRoots(){ return root; }

void IndiceEventos::printInOrder() {
    inOrder(root);
}

void IndiceEventos::inOrder(Node* node){
    if(node){
        inOrder(node->left);
        //printf("%s\n", root->key.c_str()); // para debugar
        // Formatação diferenciada por tipo de evento
        if (node->evento->getTipo() == "RG") {
            printf("%07d EV %s %03d %s %s %03d %03d\n",
                node->evento->getTempo(), 
                node->evento->getTipo().c_str(),
                node->evento->getIdPacote(),
                node->evento->getRemetente().c_str(),
                node->evento->getDestinatario().c_str(),
                node->evento->getOrigem(),
                node->evento->getDestino());
        } else if (node->evento->getTipo() == "EN") {
            printf("%07d EV %s %03d %03d\n",
                node->evento->getTempo(),
                node->evento->getTipo().c_str(),
                node->evento->getIdPacote(),
                node->evento->getDestino());
        } else {
            printf("%07d EV %s %03d %03d %03d\n",
                node->evento->getTempo(),
                node->evento->getTipo().c_str(),
                node->evento->getIdPacote(),
                node->evento->getOrigem(),
                node->evento->getDestino());
        }
        inOrder(node->right);
    }
}

void IndiceEventos::printPcInorder(Node* node, int id) {
    if (!node) return;
    
    // Percorre recursivamente toda a árvore
    printPcInorder(node->left, id);
    
    // Imprime apenas eventos do pacote desejado
    if (node->evento->getIdPacote() == id) {
        // Formatação diferenciada por tipo de evento
        if (node->evento->getTipo() == "RG") {
            printf("%07d EV %s %03d %s %s %03d %03d\n",
                node->evento->getTempo(), 
                node->evento->getTipo().c_str(),
                node->evento->getIdPacote(),
                node->evento->getRemetente().c_str(),
                node->evento->getDestinatario().c_str(),
                node->evento->getOrigem(),
                node->evento->getDestino());
        } else if (node->evento->getTipo() == "EN") {
            printf("%07d EV %s %03d %03d\n",
                node->evento->getTempo(),
                node->evento->getTipo().c_str(),
                node->evento->getIdPacote(),
                node->evento->getDestino());
        } else {
            printf("%07d EV %s %03d %03d %03d\n",
                node->evento->getTempo(),
                node->evento->getTipo().c_str(),
                node->evento->getIdPacote(),
                node->evento->getOrigem(),
                node->evento->getDestino());
        }
    }
    
    printPcInorder(node->right, id);
}

void IndiceEventos::freeMemory(Node* node) {
    if (node) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
}

//prinvate
int IndiceEventos::getHeight(Node* node) {
    return node ? node->height : 0;
}

int IndiceEventos::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void IndiceEventos::updateHeight(Node* node) {
    if (node)
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

Node* IndiceEventos::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* IndiceEventos::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* IndiceEventos::balance(Node* node) {
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

Node* IndiceEventos::insertNode(Node* node, std::string key) {
    if (!node){
        Node* newNode = new Node(key);
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

Node* IndiceEventos::search(Node* node, const std::string key) {
    if (!node || node->key == key) return node;
    if (key < node->key) return search(node->left, key);
    else return search(node->right, key);
}


