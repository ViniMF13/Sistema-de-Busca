#include "../include/Consulta.hpp"

 Consulta::Consulta(){
    tipo = -1;                    
    tempo = -1;          
    idPacote = -1;
    cliente = "";
    listaEventos = nullptr;
 }

 // Destrutor para liberar memória
Consulta::~Consulta() {
   for (int i = 0; i < tamanho; ++i) {
      delete listaEventos[i]; // libera cada Evento se tiver sido alocado
   }
   delete[] listaEventos; // libera o array de ponteiros
}


 void Consulta::inicializar(int tip, int tem, int id, std::string cl, int n){
   tipo = tip;
   tempo = tem;
   idPacote = id;
   cliente = cl;
   listaEventos = nullptr;
   /*
   // Aloca array de ponteiros para Evento
   listaEventos = new Evento*[n];

   // Inicializa os ponteiros com nullptr ou com novos objetos Evento
   for (int i = 0; i < n; ++i) {
      listaEventos[i] = nullptr; // ou: new Evento(...);
   }
   */
   
}




// Getters
int Consulta::getTipo() { return tipo; }
int Consulta::getTempo() { return tempo; }



