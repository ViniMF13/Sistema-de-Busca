#include "../include/IndiceCliente.hpp"
#include <iostream>
using namespace std;

IndiceClientes::IndiceClientes() : root(nullptr) {}

IndiceClientes::~IndiceClientes() {
    freeMemory(root);
}

void IndiceClientes::inserir(std::string key) {
    root = insertNode(root, key);
}

void IndiceClientes::printInOrder() {
    inOrder(root);
    cout << endl;
}

void IndiceClientes::inOrder(NoCliente* node) {
    if (node) {
        inOrder(node->left);

        //printa o cliente e a lista de pacotes
        NoId* atual = node->head;
        printf("%s\n", node->key.c_str() );
        printf("%d\n", node->tamanhoLista);
        while (atual != nullptr) {
            printf("%03d", atual->id);
            printf("\n");
            atual = atual->prox;
        }
        printf("\n");

        inOrder(node->right);
    }
}

void IndiceClientes::freeMemory(NoCliente* node) {
    if (node) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
}

NoCliente* IndiceClientes::buscarCliente(const std::string& key) {
    return search(root, key);
}

void IndiceClientes::inserirPacote(NoCliente* node, int id){
    NoId* novo = new NoId;
    novo->id = id; 
    if(node->tail){
       node->tail->prox = novo;
       node->tail = novo;
    } else {
       node->head = novo;
       node->tail = novo; 
    }
    node->tamanhoLista++;
}

//prisvate
int IndiceClientes::getHeight(NoCliente* node) {
    return node ? node->height : 0;
}

int IndiceClientes::getBalance(NoCliente* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void IndiceClientes::updateHeight(NoCliente* node) {
    if (node)
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

NoCliente* IndiceClientes::rotateRight(NoCliente* y) {
    NoCliente* x = y->left;
    NoCliente* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

NoCliente* IndiceClientes::rotateLeft(NoCliente* x) {
    NoCliente* y = x->right;
    NoCliente* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

NoCliente* IndiceClientes::balance(NoCliente* node) {
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

NoCliente* IndiceClientes::insertNode(NoCliente* node, std::string key) {
    if (!node){
        NoCliente* newNode = new NoCliente(key);
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

NoCliente* IndiceClientes::search(NoCliente* node, const std::string& key) {
    if (!node || node->key == key) return node;
    if (key < node->key) return search(node->left, key);
    else return search(node->right, key);
}


