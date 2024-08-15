#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int height(Node *N) {
    if (N == NULL) return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(Node *N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (root->key < key) return search(root->right, key);
    return search(root->left, key);
}

void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

unsigned long long measureBestCaseTime(Node *root) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    search(root, root->key); // Melhor caso: busca pela raiz
    clock_gettime(CLOCK_MONOTONIC, &end);

    unsigned long long start_ns = start.tv_sec * 1000000000L + start.tv_nsec;
    unsigned long long end_ns = end.tv_sec * 1000000000L + end.tv_nsec;
    return end_ns - start_ns;
}

void measureBestCase() {
    FILE *file = fopen("avl_best_case.txt", "w");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    const int numExecutions = 10;
    const int startSize = 100;
    const int endSize = 10000;
    const int increment = 100;

    fprintf(file, "# Tamanho_do_Vetor Tempo_Total_de_Execucao\n");

    for (int tamanho = startSize; tamanho <= endSize; tamanho += increment) {
        Node* root = NULL;
        unsigned long long total_time = 0;

        // Inserir elementos na árvore AVL
        for (int i = 1; i <= tamanho; i++) {
            root = insert(root, i);
        }

        // Medir o tempo para buscar o elemento da raiz
        for (int i = 0; i < numExecutions; i++) {
            total_time += measureBestCaseTime(root);
        }

        unsigned long long average_time = total_time / numExecutions;
        float time_microsseconds = (float)average_time / 1000.0;
        fprintf(file, "%d %.3f\n", tamanho, time_microsseconds);

        freeTree(root);
    }

    fclose(file);

    printf("Tempos de execução para o melhor caso calculados e salvos em 'avl_best_case.txt'.\n");
}

int main() {
    measureBestCase();
    return 0;
}
