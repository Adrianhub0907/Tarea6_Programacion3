#include <iostream>
#include <vector>
#include <queue>
#include "Node.h"
#include "AlgoritmosArbol.h"
#include "BST.h"
#include "RedBlackTree.h"

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
    std::cout << "PROBLEMA 1: BST ITERATIVO\n";
    BST<int> bstPrueba;
    int datos[20] = {50, 25, 75, 10, 35, 60, 90, 5, 15, 30, 40, 55, 65, 80, 95, 1, 12, 28, 45, 100};
    for (int x : datos) {
        bstPrueba.insert(x);
    }
    std::cout << "In-order tras insertar 20 elementos:\n";
    bstPrueba.inOrder();
    bstPrueba.remove(25);
    bstPrueba.remove(100);
    std::cout << "In-order tras eliminar 25 y 100:\n";
    bstPrueba.inOrder();
    std::cout << "Altura del BST: " << bstPrueba.height() << "\n";

    std::cout << "PROBLEMA 2: RED-BLACK TREE VS BST\n";
    BST<int> bstOrdenado;
    RedBlackTree<int> rbtOrdenado;

    for (int i = 1; i <= 20; ++i) {
        bstOrdenado.insert(i);
        rbtOrdenado.insert(i);
    }

    std::cout << "Propiedades Red-Black Tree validas?: "
              << (rbtOrdenado.verifyProperties() ? "Si" : "No") << "\n";
    std::cout << "Altura BST (20 datos ascendentes): " << bstOrdenado.height() << "\n";
    std::cout << "Altura RBT (20 datos ascendentes): " << rbtOrdenado.height() << "\n";

    std::cout << "\nPre-Orden BST:\n";
    bstOrdenado.preOrder();

    std::cout << "Pre-Orden Red-Black Tree:\n\n";
    rbtOrdenado.preOrder();

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