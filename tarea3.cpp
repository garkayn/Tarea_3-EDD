#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct NodoLista {
    int id;
    NodoLista* next;
};

class tLista{
    private:
        NodoLista* head;
        NodoLista* tail;
        NodoLista* curr;
        unsigned int listSize;
        unsigned int pos;
    public:
        tLista() {
            head = tail = curr = nullptr;
            listSize = 0; pos = 0;
        }
        void clear() {
            NodoLista* temp;
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
            NodoLista* nuevo = new NodoLista();
            nuevo->id = id_nuevo;
            nuevo->next = nullptr;
            if(head == nullptr){
                head = tail = curr = nuevo;
            } else {
                tail->next = nuevo;
                tail = nuevo;
            }
            listSize++;
        }
        void imprimirLista(){
            NodoLista* temp = head;
            while(temp != nullptr){
                cout<<temp->id<<endl;
                temp = temp->next;
            }
        }
        bool buscar(int id){
            NodoLista* temp = head;
            while (temp != nullptr) {
                if (temp->id == id) {
                    return true;
                }
                temp = temp->next;      
            }
            return false;
        }
        int getValue(){
            return curr->id;
        }
        int length(){
            return listSize;
        }
        int currPos(){
            return pos;
        }
        void prev() {
            NodoLista* temp;
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

class Grafo {
    private:
        tLista* adylista;
        int numeroNodos;
    public:
};

int main(){

}