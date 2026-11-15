#include <iostream>
#include <vector>
#include <queue>
#include "Node.h"
#include "AlgoritmosArbol.h"

template <typename T>
void liberarArbol(Node<T>* root) {
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
}

int main() {
    /*
     * Arbol de prueba:
     *           10
     *          /  \
     *         5    15
     *        / \     \
     *       3   7     20
     */
    Node<int>* root = new Node<int>(10);
    root->left = new Node<int>(5);
    root->right = new Node<int>(15);
    root->left->left = new Node<int>(3);
    root->left->right = new Node<int>(7);
    root->right->right = new Node<int>(20);

    std::cout << " PROBLEMA 3: DFS ITERATIVO AVANZADO\n";
    std::vector<int> camino;
    int K = 22; // 10 -> 5 -> 7

    if (encontrarCaminoSumaK(root, K, camino)) {
        std::cout << "Camino raiz-hoja con suma " << K << ": ";
        for (size_t i = 0; i < camino.size(); ++i) {
            std::cout << camino[i] << (i + 1 < camino.size() ? " -> " : "");
        }
        std::cout << "\n";
    } else {
        std::cout << "No existe camino con suma " << K << "\n";
    }

    std::cout << "\n PROBLEMA 4: BFS ITERATIVO AVANZADO\n";
    std::cout << "Es arbol completo?: " << (esArbolCompleto(root) ? "Si" : "No") << "\n";
    std::cout << "Ancho maximo: " << anchoMaximo(root) << "\n";
    std::cout << "Profundidad minima: " << profundidadMinima(root) << "\n";

    liberarArbol(root);
    return 0;
}