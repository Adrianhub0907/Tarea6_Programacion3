#ifndef TAREA6_PROGRAMACION3_REDBLACKTREE_H
#define TAREA6_PROGRAMACION3_REDBLACKTREE_H

#include <iostream>
#include <algorithm>
#include <stack>

// PROBLEMA 2: IMPLEMENTACION DE RED-BLACK TREE
// /*
//   Explicacion matematica de por que la altura esta acotada por O(log n):
//   1. Lema de altura negra: Todo subarbol con raiz en un nodo x contiene al menos
//      2^{bh(x)} - 1 nodos internos, donde bh(x) es la altura negra de x (numero
//      de nodos negros en cualquier camino desde x hasta una hoja NIL, sin incluir x).
//      - Caso base: Si h(x) = 0, x es NIL, bh(x) = 0 y 2^0 - 1 = 0 nodos internos.
//      - Paso inductivo: Si h(x) > 0, cada hijo c de x tiene bh(c) = bh(x) (si c es rojo)
//        o bh(c) = bh(x) - 1 (si c es negro), por lo que bh(c) >= bh(x) - 1.
//        Por hipotesis inductiva sobre ambos hijos:
//           Nodos(x) >= (2^{bh(x)-1} - 1) + (2^{bh(x)-1} - 1) + 1 = 2^{bh(x)} - 1.
//   2. Relacion entre altura h y bh(root): Por la Propiedad 3 (ningun nodo rojo puede
//      tener hijo rojo), en todo camino simple de longitud h desde la raiz hasta una
//      hoja, al menos la mitad de los nodos (sin contar la raiz) son negros:
//           bh(root) >= h / 2.
//   3. Cota logaritmica: Aplicando el lema a la raiz de un arbol con n nodos internos:
//           n >= 2^{bh(root)} - 1 >= 2^{h/2} - 1
//           2^{h/2} <= n + 1  ==>  h / 2 <= log_2(n + 1)  ==>  h <= 2 log_2(n + 1) = O(log n).
//  */

enum Color { RED, BLACK };
template <typename T>
struct RBNode {
    T data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    RBNode(T val, Color c, RBNode* nilNode)
        : data(val), color(c), left(nilNode), right(nilNode), parent(nilNode) {}
};

template <typename T>
class RedBlackTree {
private:
    RBNode<T>* root;
    RBNode<T>* NIL;
    void leftRotate(RBNode<T>* x) {
        RBNode<T>* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rightRotate(RBNode<T>* y) {
        RBNode<T>* x = y->left;
        y->left = x->right;
        if (x->right != NIL) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == NIL) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
    }
    void fixInsert(RBNode<T>* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode<T>* uncle = z->parent->parent->right;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                RBNode<T>* uncle = z->parent->parent->left;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    int verificarSubarbol(RBNode<T>* node) const {
        if (node == NIL) {
            return (NIL->color == BLACK) ? 1 : -1;
        }

        if (node->color != RED && node->color != BLACK) return -1;

        if (node->color == RED) {
            if (node->left->color == RED || node->right->color == RED) {
                return -1;
            }
        }

        int bhLeft = verificarSubarbol(node->left);
        int bhRight = verificarSubarbol(node->right);

        if (bhLeft == -1 || bhRight == -1 || bhLeft != bhRight) {
            return -1;
        }
        return bhLeft + (node->color == BLACK ? 1 : 0);
    }

    int calcularAltura(RBNode<T>* node) const {
        if (node == NIL) return 0;
        return 1 + std::max(calcularAltura(node->left), calcularAltura(node->right));
    }

    void destruir(RBNode<T>* node) {
        if (node == NIL) return;
        destruir(node->left);
        destruir(node->right);
        delete node;
    }

public:
    RedBlackTree() {
        NIL = new RBNode<T>(T{}, BLACK, nullptr);
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = NIL;
        root = NIL;
    }

    ~RedBlackTree() {
        destruir(root);
        delete NIL;
    }

    void insert(T val) {
        RBNode<T>* z = new RBNode<T>(val, RED, NIL);
        RBNode<T>* y = NIL;
        RBNode<T>* x = root;

        while (x != NIL) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else if (z->data > x->data) {
                x = x->right;
            } else {
                delete z;
                return;
            }
        }
        z->parent = y;
        if (y == NIL) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }
        fixInsert(z);
    }

    bool verifyProperties() const {
        if (NIL->color != BLACK) return false;
        if (root != NIL && root->color != BLACK) return false;
        return verificarSubarbol(root) != -1;
    }

    int height() const {
        return calcularAltura(root);
    }
    void preOrder() const {
        if (root == NIL) {
            std::cout << "\n";
            return;
        }
        std::stack<RBNode<T>*> pila;
        pila.push(root);
        while (!pila.empty()) {
            RBNode<T>* curr = pila.top();
            pila.pop();
            std::cout << curr->data << "(" << (curr->color == RED ? "R" : "B") << ") ";
            if (curr->right != NIL) pila.push(curr->right);
            if (curr->left != NIL) pila.push(curr->left);
        }
        std::cout << "\n";
    }
};


#endif //TAREA6_PROGRAMACION3_REDBLACKTREE_H