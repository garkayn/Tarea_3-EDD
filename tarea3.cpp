#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#define NOVISITADO false
#define VISITADO true

struct tNodoLista {
    int id;
    bool visitado;
    tNodoLista* next;
};

class tLista{
    private:
        tNodoLista* head;
        tNodoLista* tail;
        tNodoLista* curr;
        int listSize;
        int pos;
    public:
        tLista() {
            head = tail = curr = nullptr;
            listSize = 0; pos = 0;
        }
        void clear() {
            tNodoLista* temp;
            while (head != nullptr) {
                temp = head;
                head = head->next;
                delete temp;
            }
            head = tail = curr = nullptr;
            listSize = pos = 0;
        }
        void moveToStart() { 
            curr = head; 
            pos = 0; 
        }
        void moveToEnd() { 
            curr = tail; 
            pos = listSize; 
        }
        void append(int id_nuevo){
            tNodoLista* nuevo = new tNodoLista();
            nuevo->id = id_nuevo;
            nuevo->next = nullptr;
            nuevo->visitado = NOVISITADO;
            if(head == nullptr){
                head = tail = curr = nuevo;
            } else {
                tail->next = nuevo;
                tail = nuevo;
            }
            listSize++;
        }
        void imprimirLista(){
            tNodoLista* temp = head;
            while(temp != nullptr){
                cout<<temp->id<<endl;
                temp = temp->next;
            }
        }
        bool buscar(int id){
            tNodoLista* temp = head;
            while (temp != nullptr) {
                if (temp->id == id) {
                    return true;
                }
                temp = temp->next;      
            }
            return false;
        }
        int currValue(){
            return curr->id;
        }
        int length(){
            return listSize;
        }
        int currPos(){
            return pos;
        }
        void prev() {
            tNodoLista* temp;
            if (curr == head) return;
            temp = head;
            while (temp->next != curr) temp = temp->next;
            curr = temp;
            pos--;
        }
        void next(){
            if(curr != tail){
                curr = curr->next;
                pos++;
            }
        }

};

struct tNodoCola {
    tNodoLista nodo;
    tNodoCola* next;
};

class tCola {
    private:
        tNodoCola* frente;
        tNodoCola* cola;
        int size;

    public:
        tCola() : frente(nullptr), cola(nullptr), size(0) {}

        ~tCola() {
            while (frente != nullptr) {
                dequeue();
            }
        }

        void enqueue(int asignacion) {   
            tNodoCola* nuevo = new tNodoCola;
            nuevo->nodo.id = asignacion;
            nuevo->next = nullptr;       
            if (frente == nullptr) {    
                frente = nuevo;
                cola = frente;
            }
            else {
                cola->next = nuevo;
                cola = nuevo;
            }          
            size++;
            nuevo->next = nullptr;       
        }

        void dequeue() {
            if (frente != nullptr) {
                tNodoCola* temp = frente;
                frente = frente->next;
                delete temp;
                if (frente == nullptr) {
                    cola = nullptr;
                }
                size--;
            }
        }

        int frontValue() {
            return frente->nodo.id;
        }

        bool isEmpty() {
            return frente == nullptr;
        }

        int getSize() {
            return size;
        }
};


class tGrafo {
    private:
        tLista* adyLista;
        bool* marcas;
        int numeroNodos;
        int cantidadConductores;
        int cantidadVertices;
        int cantidadEnlaces;
    public:
        void leerArchivo(fstream &file){
            file>>cantidadVertices;
            cout<<"CANTIDAD DE VERTICES: "<<cantidadVertices<<endl;
            file>>cantidadEnlaces;
            cout<<"CANTIDAD DE ENLACES: "<<cantidadEnlaces<<endl;
            file>>cantidadConductores;
            cout<<"CANTIDAD DE CONDUCTORES: "<<cantidadConductores<<endl;
        }
        void construirGrafo(fstream &file){
            adyLista = new tLista[cantidadVertices]; 
            marcas = new bool[cantidadVertices];
            for (int i = 0; i < cantidadVertices; i++) {
                marcas[i] = NOVISITADO;  
            }

            for(int i=0; i<cantidadEnlaces; i++){
                int inicio;
                int fin;
                file>>inicio;
                file>>fin;
                adyLista[inicio-1].append(fin);
            }
        }

        void mostrarVecinos(){
            for(int i=0; i<cantidadVertices; i++){
                cout<<"VERTICE: "<<i+1<<endl;
                cout<<"QUE TIENE LOS SIGUIENTES VECINOS (HOT): "<<endl;
                for(int j=0; j<adyLista[i].length() ; j++){
                    cout<<adyLista[i].currValue()<<endl;
                    adyLista[i].next();
                }
                adyLista[i].moveToStart();
                cout<<"ME DEVOLVI AL VECINO: "<<adyLista[i].currValue()<<endl;
            }
        }

        void mostrarMarcas(){
            for(int i=0;i<cantidadVertices;i++){
                cout<<"VERTICE: "<<i+1<<" CON MARCA: "<<marcas[i]<<endl;
            }
        }

        void setMark(int vertice, bool visitar) {
            if(visitar){
                marcas[vertice-1] = VISITADO;
            }else{
                marcas[vertice-1] = NOVISITADO;
            }
        }

        bool getMark(int vertice){
            return marcas[vertice-1];
        }

        void setMarkFalse(){
            for(int i=0; i<cantidadVertices; i++){
                marcas[i] = NOVISITADO;
            }
        }

        int nVertex(){
            return cantidadVertices;
        }

        int first(int vertice){
            return adyLista[vertice-1].currValue();
        }

        int next(int vertice){
            adyLista[vertice -1].next();
            return adyLista[vertice-1].currValue();
        }

        int cantVecinosV(int vertice){
            return adyLista[vertice-1].length();
        }

        bool isEdge(int vertice, int vecino){
            return adyLista[vertice-1].buscar(vecino);
        }
        void volverInicio(int vertice){
            adyLista[vertice-1].moveToStart();
        }
};

void BFS(tGrafo& G, int origen, int destino) {
    tCola Q; int vecino;
    int n = G.nVertex();
    int* padres = new int[n];
    for(int i=0; i<n; i++){
        padres[i] = -1;
    }
    int existe = 0;
    G.setMarkFalse();
    Q.enqueue(origen);
    G.setMark(origen, VISITADO);
    while (Q.getSize() != 0) {
        int front = Q.frontValue();
        Q.dequeue();
        if(front == destino){
            existe = 1;
            break;
        }
        if(G.cantVecinosV(front) != 0){
            G.setMark(front, VISITADO);
            vecino = G.first(front);
            for (int i = 0; i < G.cantVecinosV(front); i++) {
                if (G.getMark(vecino) == NOVISITADO) {
                    //cout<<"NODO A VISITAR: "<<vecino<<endl;
                    G.setMark(vecino, VISITADO);
                    padres[vecino - 1] = front;
                    //cout<<"VERTICE POR HACER ENQUEUE: "<<vecino<<endl;
                    Q.enqueue(vecino);
                }
                vecino = G.next(front);
            }
            G.volverInicio(front);
        }
    }
    if(existe==1){
        int* camino = new int[n];
        int largo = 0;
        int iterador = destino;
        while(iterador != origen){
            if(G.isEdge(padres[iterador-1], iterador)){
                camino[largo++] = iterador;
            }
            iterador = padres[iterador-1];
        }
        camino[largo++] = origen;
        for(int i=0; i<largo; i++){
            cout<<camino[i]<<endl;
        }
    }
}

int main(){
    fstream file;
    file.open("data1.txt",  ios::in);
    tGrafo grafo;
    grafo.leerArchivo(file);
    grafo.construirGrafo(file);
    BFS(grafo,20,24);
    //grafo.mostrarMarcas();
    //grafo.mostrarVecinos();
}