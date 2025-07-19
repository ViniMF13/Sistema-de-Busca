#include "../include/Evento.hpp"
#include <cstring>
#include <cstdio>

 
 
 Evento::Evento(){
    tipo = "";                    
    tempo = -1;          
    idPacote = -1;
    origem = -1;
    destino = -1; 
    destinatario = "";
    remetente = "";
 }

 void Evento::inicializar(std::string T, int tmp, int pac, int org, int dst, std::string rem, std::string dest){
    tipo = T;
    tempo = tmp;
    idPacote = pac;
    origem = org;
    destino = dst; 
    destinatario = dest;
    remetente = rem;
}

// Getters
std::string Evento::getTipo() { return tipo; }
std::string Evento::getRemetente() { return remetente; }
std::string Evento::getDestinatario() { return destinatario; }
int Evento::getIdPacote() { return idPacote; }
int Evento::getTempo() { return tempo; }
int Evento::getOrigem() { return origem; }
int Evento::getDestino() { return destino; }


