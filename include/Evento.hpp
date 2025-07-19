#ifndef EVENTO_H
#define EVENTO_H
#include <cstring>
#include <cstdio>
#include <string>

/* TIPOS DE EVENTO
1. RG: Pacote ainda não foi postado (apenas registrado no sistema)
2. AR: Pacote chegou no armazém e foi armazenado na respectiva seção
3. RM: Pacote foi removido da seção para tentativa de transporte
4. UR: Pacote foi rearmazenado por não ser possível transportá-lo
5. TR: Pacote sendo transportado entre armazéns
6. EN: Pacote entregue
*/

class Evento {
    private:     
    int tempo, idPacote, origem, destino;
    std::string tipo, remetente, destinatario;
    //Pacote pacote;

    public:
    Evento();
    void inicializar(std::string T, int tmp, int pac, int org, int dst, std::string rem, std::string dest);
    bool operator<(const Evento& outro) const;

    //getters
    std::string getTipo();
    int getTempo();
    int getIdPacote();
    int getOrigem();
    int getDestino();

    std::string getRemetente();
    std::string getDestinatario();
};

#endif