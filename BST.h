#ifndef TAREA6_PROGRAMACION3_BFS_H
#define TAREA6_PROGRAMACION3_BFS_H

#include "Node.h"
#include <iostream>
#include <stack>
#include <queue>

// EJERCICIO 1: BST ITERATIVO Y ANALISIS DE DEGRADACION
/*
 Explicacion matematica de la degradacion a O(n):
1. Costo de insercion: El costo de insertar el i-esimo elemento en un BST de
    altura h_{i-1} esta acotado por el numero de comparaciones desde la raiz
    hasta una hoja: T_ins(i) = h_{i-1} + 1.
2. Peor caso (secuencia ordenada x_1 < x_2 < ... < x_n): Por la invariante
    del BST, cada nuevo elemento x_i es mayor que todos los anteriores y desciende
    exclusivamente por los punteros 'right'.
3. Recurrencia de altura: Con h_1 = 1 (medida en nodos; o h_1 = 0 en aristas),
    cada insercion agrega un nodo al final de la unica rama existente:
    h_i = h_{i-1} + 1  ==>  h_n = n  (en nodos)  o  h_n = n - 1  (en aristas).
4. Complejidad:
    - Una operacion individual (busqueda, insercion o eliminacion) recorre la
        rama unica de longitud n, tomando Theta(n) comparaciones.
    - El costo total de insertar n elementos ordenados es:
        T(n) = sum_{i=1}^{n} i = n(n + 1) / 2 = Theta(n^2)
        lo que implica un costo promedio/amortizado de Theta(n^2)/n = Theta(n)
        por insercion, degradandose de O(log n) a O(n).
 */

template <typename T>
class BST {
private:
    Node<T>* root;
    void destruirArbol() {
        if (root == nullptr) return;
        std::queue<Node<T>*> cola;
        cola.push(root);
        while (!cola.empty()) {
            Node<T>* actual = cola.front();
            cola.pop();
            if (actual->left != nullptr) cola.push(actual->left);
            if (actual->right != nullptr) cola.push(actual->right);
            delete actual;
        }
        root = nullptr;
    }
public:
    BST() : root(nullptr) {}
    ~BST() { destruirArbol(); }

    Node<T>* getRoot() const { return root; }

    void insert(T val) {
        Node<T>* nuevo = new Node<T>(val);
        if (root == nullptr) {
            root = nuevo;
            return;
        }
        Node<T>* curr = root;
        Node<T>* parent = nullptr;

        while (curr != nullptr) {
            parent = curr;
            if (val < curr->data) {
                curr = curr->left;
            } else if (val > curr->data) {
                curr = curr->right;
            } else {
                delete nuevo;
                return;
            }
        }
        if (val < parent->data) {
            parent->left = nuevo;
        } else {
            parent->right = nuevo;
        }
    }

    bool remove(T val) {
        Node<T>* curr = root;
        Node<T>* parent = nullptr;

        while (curr != nullptr && curr->data != val) {
            parent = curr;
            if (val < curr->data) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        if (curr == nullptr) return false;
        if (curr->left != nullptr && curr->right != nullptr) {
            Node<T>* succParent = curr;
            Node<T>* succ = curr->right;
            while (succ->left != nullptr) {
                succParent = succ;
                succ = succ->left;
            }
            curr->data = succ->data;
            curr = succ;
            parent = succParent;
        }

        Node<T>* child = (curr->left != nullptr) ? curr->left : curr->right;

        if (parent == nullptr) {
            root = child;
        } else if (parent->left == curr) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        delete curr;
        return true;
    }

    void inOrder() const {
        std::stack<Node<T>*> pila;
        Node<T>* curr = root;

        while (curr != nullptr || !pila.empty()) {
            while (curr != nullptr) {
                pila.push(curr);
                curr = curr->left;
            }
            curr = pila.top();
            pila.pop();
            std::cout << curr->data << " ";
            curr = curr->right;
        }
        std::cout << "\n";
    }

    void preOrder() const {
        if (root == nullptr) {
            std::cout << "\n";
            return;
        }
        std::stack<Node<T>*> pila;
        pila.push(root);
        while (!pila.empty()) {
            Node<T>* curr = pila.top();
            pila.pop();
            std::cout << curr->data << " ";
            if (curr->right != nullptr) pila.push(curr->right);
            if (curr->left != nullptr) pila.push(curr->left);
        }
        std::cout << "\n";
    }
    int height() const {
        if (root == nullptr) return 0;
        std::queue<Node<T>*> cola;
        cola.push(root);
        int altura = 0;
        while (!cola.empty()) {
            int tamNivel = static_cast<int>(cola.size());
            ++altura;
            for (int i = 0; i < tamNivel; ++i) {
                Node<T>* actual = cola.front();
                cola.pop();
                if (actual->left != nullptr) cola.push(actual->left);
                if (actual->right != nullptr) cola.push(actual->right);
            }
        }
        return altura;
    }
};



#endif //TAREA6_PROGRAMACION3_BFS_H