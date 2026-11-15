#ifndef ALGORITMOSARBOL_H
#define ALGORITMOSARBOL_H

#include "Node.h"
#include <stack>
#include <queue>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>

// PROBLEMA 3: DFS ITERATIVO AVANZADO (Exclusivamente std::stack)
/*
 * Explicacion:
 * 1. Exploracion directa hasta las hojas: El problema requiere evaluar la suma
 *    completa desde la raiz hasta un nodo hoja. DFS profundiza por una sola
 *    rama hasta alcanzar una hoja antes de retroceder, permitiendo validar la
 *    condicion de suma K de forma natural al llegar al extremo de cada ruta.
 * 2. Eficiencia de memoria: En un arbol de altura h, DFS mantiene en la pila
 *    unicamente los nodos de la rama activa en exploracion, mientras que BFS
 *    almacenaria todos los nodos de un mismo nivel simultaneamente.
 * 3. Terminacion temprana: Si el camino valido se encuentra en las primeras
 *    ramas exploradas, DFS detiene su ejecucion inmediatamente sin recorrer
 *    el resto del arbol.
 */
template <typename T>
bool encontrarCaminoSumaK(Node<T>* root, T K, std::vector<T>& caminoResultado) {
    caminoResultado.clear();
    if (root == nullptr) return false;

    std::stack<std::tuple<Node<T>*, T, std::vector<T>>> pila;
    pila.push({root, root->data, {root->data}});

    while (!pila.empty()) {
        auto [actual, sumaActual, caminoActual] = pila.top();
        pila.pop();

        // Verificar si es nodo hoja
        if (actual->left == nullptr && actual->right == nullptr) {
            if (sumaActual == K) {
                caminoResultado = caminoActual;
                return true;
            }
        }

        if (actual->right != nullptr) {
            std::vector<T> nuevoCamino = caminoActual;
            nuevoCamino.push_back(actual->right->data);
            pila.push({actual->right, sumaActual + actual->right->data, nuevoCamino});
        }

        if (actual->left != nullptr) {
            std::vector<T> nuevoCamino = caminoActual;
            nuevoCamino.push_back(actual->left->data);
            pila.push({actual->left, sumaActual + actual->left->data, nuevoCamino});
        }
    }

    return false;
}

// PROBLEMA 4: BFS ITERATIVO AVANZADO (Exclusivamente std::queue)
/*
 * Justificacion
 * 1. Profundidad minima: BFS explora los nodos en orden estrictamente no
 *    decreciente respecto a su distancia desde la raiz (niveles 0, 1, 2...).
 *    Por induccion sobre los niveles, el primer nodo hoja desencolado garantiza
 *    la menor profundidad posible.
 * 2. Ancho maximo: Una cola FIFO agrupa todos los nodos de un mismo nivel k
 *    antes de procesar el nivel k + 1, por lo que el tamano de la cola al
 *    iniciar cada nivel mide exactamente su ancho.
 * 3. Arbol completo: Un arbol binario de altura h es completo si todos los
 *    niveles 0, ..., h-1 estan llenos y los nodos del nivel h estan agrupados a
 *    la izquierda. Al recorrer por niveles incluyendo punteros nulos, esto
 *    equivale a verificar que todos los punteros validos aparezcan de forma
 *    contigua antes del primer nullptr.
 */

template <typename T>
bool esArbolCompleto(Node<T>* root) {
    if (root == nullptr) return true;

    std::queue<Node<T>*> cola;
    cola.push(root);
    bool seVioNulo = false;

    while (!cola.empty()) {
        Node<T>* actual = cola.front();
        cola.pop();

        if (actual == nullptr) {
            seVioNulo = true;
        } else {
            if (seVioNulo) return false;
            cola.push(actual->left);
            cola.push(actual->right);
        }
    }
    return true;
}

template <typename T>
int anchoMaximo(Node<T>* root) {
    if (root == nullptr) return 0;

    std::queue<Node<T>*> cola;
    cola.push(root);
    int maxAncho = 0;

    while (!cola.empty()) {
        int tamanoNivel = static_cast<int>(cola.size());
        maxAncho = std::max(maxAncho, tamanoNivel);

        for (int i = 0; i < tamanoNivel; ++i) {
            Node<T>* actual = cola.front();
            cola.pop();

            if (actual->left != nullptr) cola.push(actual->left);
            if (actual->right != nullptr) cola.push(actual->right);
        }
    }
    return maxAncho;
}

template <typename T>
int profundidadMinima(Node<T>* root) {
    if (root == nullptr) return 0;

    std::queue<std::pair<Node<T>*, int>> cola;
    cola.push({root, 1});

    while (!cola.empty()) {
        auto [actual, profundidad] = cola.front();
        cola.pop();

        if (actual->left == nullptr && actual->right == nullptr) {
            return profundidad;
        }

        if (actual->left != nullptr) cola.push({actual->left, profundidad + 1});
        if (actual->right != nullptr) cola.push({actual->right, profundidad + 1});
    }
    return 0;
}

#endif // ALGORITMOSARBOL_H