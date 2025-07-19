#include "../include/ListaEventos.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ListaEventos::ListaEventos(){
    eventos = nullptr;
    tamanhoEventos = 0;
}

ListaEventos::~ListaEventos() {
        destruir();
}

void ListaEventos::processarEventos(std::ifstream& entrada, IndiceClientes &indiceC, IndicePacotes &indiceP, IndiceEventos &indiceE, int &count) {
    std::string linha;
    while (std::getline(entrada, linha)) {
        std::istringstream stream(linha);  // cria um fluxo a partir da linha

        int tempo;
        std::string sigla;
        stream >> tempo >> sigla;

        if(sigla == "EV"){ //processar eventos
            std::string remetente, destinatario, tipo;
            int id, origem, destino;
            Evento evento;

            stream >> tipo;
            if (tipo == "RG") {
                //inicializa e insere na lista de eventos do sistema
                stream >> id >> remetente >> destinatario >> origem >> destino;
                evento.inicializar(tipo, tempo, id, origem, destino, remetente, destinatario);
                Evento* ponteiroEvento = inserirEvento(evento);

                // 1 - gera a chave e insere um ponteiro para o evento no indeiceE
                std::ostringstream oss;
                oss << std::setw(3) << std::setfill('0') << id;
                oss << std::setw(7) << std::setfill('0') << tempo;
                std::string chave = oss.str();
                
                indiceE.inserir(chave);
                Node* evt = indiceE.buscarEvento(chave);
                indiceE.setPonteiro(evt, ponteiroEvento);
               
                // 2 - insere o pacote no indice de Pacotes e atualiza os poeniros para eventos
                indiceP.inserir(id);
                NoPacote* pacote = indiceP.buscarPacote(id);
                indiceP.setPrimeiroEvento(pacote, evt);
                indiceP.setUltimoEvento(pacote, evt);

                // 3 - insere o remetente e o destinatario no indiceC e armazena o pacote na lista de pacotes do cliente
                indiceC.inserir(remetente);
                NoCliente* rem = indiceC.buscarCliente(remetente);
                indiceC.inserirPacote(rem, id);

                indiceC.inserir(destinatario);
                NoCliente* dest = indiceC.buscarCliente(destinatario);
                indiceC.inserirPacote(dest, id);

            } else if (tipo == "EN") {
                //inicializa e insere na lista de eventos do sistema
                stream >> id >> destino;
                evento.inicializar(tipo, tempo, id, -1, destino, "", "");
                Evento* ponteiroEvento = inserirEvento(evento);

                //1 - gera a chave e insere um ponteiro para o evento no indeiceE
                std::ostringstream oss;
                oss << std::setw(3) << std::setfill('0') << id;
                oss << std::setw(7) << std::setfill('0') << tempo;
                std::string chave = oss.str();
                indiceE.inserir(chave);
                Node* evt = indiceE.buscarEvento(chave);
                indiceE.setPonteiro(evt, ponteiroEvento);

                //2 - atualiza o ultimo evento no indice de Pacotes
                NoPacote* pacote = indiceP.buscarPacote(id);
                indiceP.setUltimoEvento(pacote, evt);

            } else {
                stream >> id >> origem >> destino;
                evento.inicializar(tipo, tempo, id, origem, destino, "", "");
                Evento* ponteiroEvento = inserirEvento(evento);

                //1 - gera a chave composta e insere no indeice de Eventos
                std::ostringstream oss;
                oss << std::setw(3) << std::setfill('0') << id;
                oss << std::setw(7) << std::setfill('0') << tempo;
                oss << std::setw(3) << std::setfill('0') << count++; // eliminar conflito de eventos no mesmo tempo

                std::string chave = oss.str();
                indiceE.inserir(chave);
                Node* evt = indiceE.buscarEvento(chave);
                indiceE.setPonteiro(evt, ponteiroEvento);

                //2 - atualiza o ultimo evento no indice de Pacotes
                NoPacote* pacote = indiceP.buscarPacote(id);
                indiceP.setUltimoEvento(pacote, evt);

            } 
        } else { //processar consultas
            std::string cl;
            int pc;

            if(sigla == "CL"){
                stream >> cl;
                NoCliente* cliente = indiceC.buscarCliente(cl);
                printf("%d CL %s \n", tempo, cl.c_str());
                if(cliente){ 
                    printf("%d\n", (2*cliente->tamanhoLista) );
                    gerarRespostasCliente(cliente, indiceP);
                } else {
                    printf("%d\n", 0);
                }
                

            } else if(sigla == "PC"){
                stream >> pc;
                NoPacote* pacote = indiceP.buscarPacote(pc);
                if(pacote){ 
                    printf("%07d PC %03d\n", tempo, pc);
                    printf("%0d\n", pacote->tamanhoLista);
                    gerarRespostasPacote(pacote, indiceE);
                }
            }
        }   
    }
}

void ListaEventos::gerarRespostasCliente(NoCliente* cliente, IndicePacotes &indiceP){
    IndiceEventos indiceAux;
    int contador = 0;

    NoId* atual = cliente->head;
    while(atual != nullptr){
        
        NoPacote* pacote = indiceP.buscarPacote(atual->id);
        // insere o primeiro e ultimo evento no indiceAuxiliar
        Evento* evt1 = pacote->primeiroEvento->evento;
        std::ostringstream oss1;
        oss1 << std::setw(7) << std::setfill('0') << evt1->getTempo();
        oss1 << std::setw(3) << std::setfill('0') << atual->id;
        oss1 << std::setw(3) << std::setfill('0') << contador++; // eliminar conflito de eventos no mesmo tempo
        std::string chave1 = oss1.str();
        indiceAux.inserir(chave1);
        Node* e1 = indiceAux.buscarEvento(chave1);
        indiceAux.setPonteiro(e1, evt1);

        Evento* evt2 = pacote->ultimoEvento->evento;
        std::ostringstream oss2;
        oss2 << std::setw(7) << std::setfill('0') << evt2->getTempo();
        oss2 << std::setw(3) << std::setfill('0') << atual->id;
        oss2 << std::setw(3) << std::setfill('0') << contador++; // eliminar conflito de eventos no mesmo tempo
        std::string chave2 = oss2.str();
        indiceAux.inserir(chave2);
        Node* e2 = indiceAux.buscarEvento(chave2);
        indiceAux.setPonteiro(e2, evt2);

        atual = atual->prox;
    }
    
    //faz o caminhamento no indice auxilair
    indiceAux.printInOrder();
}

void ListaEventos::gerarRespostasPacote(NoPacote* pacote, IndiceEventos &indiceE) {
    // faz o caminhamento no Indice de Eventos original e printa os eventos relacionados ao pacote
    indiceE.printPcInorder(indiceE.getBloodyRoots(), pacote->key);
}

Evento* ListaEventos::inserirEvento(const Evento& e) {
    NoEvento* novo = new NoEvento; //alloca memória no heap para o evento 
    novo->evento = e; // aqui o evento é copiado para o nó
    novo->prox = eventos;
    eventos = novo;
    tamanhoEventos++;

    return &novo->evento;
}

void ListaEventos::imprimir(){
    NoEvento* atual = eventos;
    printf("Eventos: %d \n", tamanhoEventos);
    while (atual != nullptr) {
        printf("%07d EV %s %03d %s %s %03d %03d",
              atual->evento.getTempo(), atual->evento.getTipo().c_str(), atual->evento.getIdPacote(), 
              atual->evento.getRemetente().c_str(), atual->evento.getDestinatario().c_str(), atual->evento.getOrigem(), atual->evento.getDestino() );
        printf("\n");
        atual = atual->prox;
    }
}

void ListaEventos::destruir() {
    NoEvento* atual = eventos;
    while (atual != nullptr) {
        NoEvento* temp = atual;
        atual = atual->prox;
        delete temp;
    }
    eventos = nullptr;
}

int ListaEventos::getTamanho(){ return tamanhoEventos; }