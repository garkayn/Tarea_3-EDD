#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#define NOVISITADO false
#define VISITADO true
#define INFINITO 2147483647
typedef int tVertice;

// ============================================================
// Sección 1: TDA Lista para implementación de grafos y caminos
// ============================================================

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
        ~tLista() {
            tNodoLista* temp;
            while (head != nullptr) {
                temp = head;
                head = head->next;
                delete temp;
            }
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
                cout<<temp->id;
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

// ==============================================
// Sección 2: TDA Cola para implementación en BFS
// ==============================================

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

// ====================
// Sección 3: TDA Grafo
// ====================

class tGrafo {
    private:
        tLista* adyLista;
        bool* marcas;
        int numeroNodos;
        int cantidadConductores;
        int cantidadVertices;
        int cantidadEnlaces;
    public:
        ~tGrafo(){
            delete[] marcas;
            for(int i=0; i<cantidadVertices ; i++){
                adyLista[i].~tLista();
            }
            delete[] adyLista;
        }

        void leerArchivo(fstream &file){
            file>>cantidadVertices;
            file>>cantidadEnlaces;
            file>>cantidadConductores;
        }

        /*****
        * void construirGrafo
        ******
        * Lee y carga la parte del archivo donde se almacenan los enlaces entre los nodos.
        * Asigna memoria dinámica para dos arreglos, uno que contendrá las listas de adyacencia, se trabaja de tal forma que el índice del arreglo
        * represente al vértice i-1, es decir, para el vértice 1, su lista de adyacencia de encuentra en el índice 0 del arreglo. Y otro arreglo con
        * las marcas de los nodos, para verificar si están o no visitados, primeramente se inicializan en no visitados y su manejo de los índices es idéntica al anterior.
        ******
        * Input:
        * fstream &file : Archivo ya abierto en modo lectura
        ******
        * Efecto:
        * Construye la lista de adyacencia de cada vértice e inicializa las marcas de cada uno en no visitado.
        *****/
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

        void mostrarVecinos(){ //borrable
            for(int i=0; i<cantidadVertices; i++){
                cout<<"VERTICE: "<<i+1<<endl;
                cout<<"QUE TIENE LOS SIGUIENTES VECINOS: "<<endl;
                for(int j=0; j<adyLista[i].length(); j++) { 
                    cout<<adyLista[i].currValue()<<endl;
                    adyLista[i].next();
                }
                adyLista[i].moveToStart();
                cout<<"ME DEVOLVI AL VECINO: "<<adyLista[i].currValue()<<endl;
            }
        }

        void mostrarMarcas(){ //borrable
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
        int mostrarCantConductores(){
            return cantidadConductores;
        }
};

// =============================================================
// Sección 4: Implementación del BFS y reconstrucción del camino
// =============================================================

/*****
* tLista solicitar_uber
******
* La primera parte, visita los nodos en el orden de un BFS, y guarda en el arreglo padres, al vértice que encoló al otro, es decir, si 1 tiene como vecinos a 2, 3 y 4,
* en la posicíon 1 2 y 3, respectivamente, se guardaría a 1, que encoló y desde ese vértice se visitó a 2, 3 y 4.
* La segunda parte, reconstruye el camino que buscamos, teniendo en cuenta los parámetros de origen y destino.
* Explicar como se reconstruye el camino
******
* Input:
* tGrafo& G : TDA Grafo recibido por referencia
* int origen : Vértice de origen del camino buscado
* int destino : Vértice de destino del camino buscado
******
* Returns:
* tLista , el camino más corto desde un origen hacia un destino dado, en caso de que dicho camino no exista, una lista con único elemento un -1
*****/

tLista solicitar_uber(tGrafo& G, int origen, int destino) {
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
                    G.setMark(vecino, VISITADO);
                    padres[vecino - 1] = front;
                    Q.enqueue(vecino);
                }
                vecino = G.next(front);
            }
            G.volverInicio(front);
        }
    }
    tLista camino;
    if(existe==1){    
        int iterador = destino;
        while(iterador != origen){
            if(G.isEdge(padres[iterador-1], iterador)){ //iterador representa el valor en si del nodo
                camino.append(iterador);
            }
            iterador = padres[iterador-1];
        }
        camino.append(origen);
    }else{
        camino.append(-1);
    }
    delete[] padres;
    return camino;
}


int main(){
    int cantConductores;
    int inicio,fin;
    fstream file;
    file.open("data1.txt",  ios::in);
    tGrafo grafo;
    grafo.leerArchivo(file);
    grafo.construirGrafo(file);
    cantConductores = grafo.mostrarCantConductores(); 
    int* posicionConductores = new int[cantConductores];
    for(int i=0; i<cantConductores;i++){
        file>>posicionConductores[i];
    }

    while(inicio != -1 && fin != -1){
        bool conductorDisponible = false;
        int dConductor = INFINITO;
        cout<<"Ingrese viaje: "<<endl;
        cin>>inicio;
        cin>>fin;
        int conductorCercano;
        tLista ruta = solicitar_uber(grafo,inicio,fin);
        tLista recorridoConductor;
        for(int i=0; i<cantConductores;i++){
            recorridoConductor = solicitar_uber(grafo,posicionConductores[i],inicio);
            if (recorridoConductor.length() < dConductor && recorridoConductor.currValue() != -1){
                dConductor = recorridoConductor.length(); 
                conductorCercano = i;
                conductorDisponible = true;
            }
        }

        int dViaje = ruta.length();
        int costo = 300*(dConductor-1) + 500*(dViaje-1);

        

        if (ruta.currValue() != -1 && conductorDisponible == true){
            cout<<"Ruta: {";
            ruta.moveToStart();
            posicionConductores[conductorCercano] = fin;
            ruta.moveToEnd();
            cout<<ruta.currValue();
            for(int i = 0; i < ruta.length()-1; i++){   
                ruta.prev();  
                cout<<", ";    
                cout<<ruta.currValue();       
            }

            cout<<"} - Costo: "<<costo<<endl;
        } else if(inicio != -1 && fin != -1){
            cout<<"Ruta: {";
            ruta.moveToStart();
            cout<<"} - Costo: "<<-1<<endl;
        } else {
            cout<<"Gracias por preferir Uber."<<endl;
        }

    }
    delete [] posicionConductores;

}