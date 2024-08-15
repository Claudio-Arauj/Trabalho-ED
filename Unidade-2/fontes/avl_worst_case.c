// avl_worst_case.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int height(Node *N) {
    return (N == NULL) ? 0 : N->height;
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
    return (N == NULL) ? 0 : height(N->left) - height(N->right);
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

void generateRandomArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i + 1;  // Use a sorted array of unique values
    }
    // Shuffle the array to create randomness
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

uint64_t measureSearchTime(Node *root, int key) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    search(root, key);
    clock_gettime(CLOCK_MONOTONIC, &end);
    return (uint64_t)(end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);  // nanoseconds
}

void measureWorstCase() {
    FILE *file = fopen("avl_worst_case.txt", "w");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    const int numExecutions = 10;  // Number of executions for averaging
    const int startSize = 100;
    const int endSize = 10000;
    const int increment = 100;

    fprintf(file, "# Tamanho_do_Vetor Tempo_Total_de_Execucao\n");

    for (int tamanho = startSize; tamanho <= endSize; tamanho += increment) {
        Node* root = NULL;
        uint64_t total_time = 0;

        // Inserir elementos na árvore AVL
        int *vetor = (int*)malloc(tamanho * sizeof(int));
        if (vetor == NULL) {
            perror("Erro ao alocar memória");
            fclose(file);
            return;
        }
        generateRandomArray(vetor, tamanho);
        for (int i = 0; i < tamanho; i++) {
            root = insert(root, vetor[i]);
        }
        free(vetor);

        // Medir o tempo de busca para uma chave que está em um nível profundo da árvore
        // O pior caso é buscar um valor ausente que está além do maior valor inserido
        for (int i = 0; i < numExecutions; i++) {
            int nonExistentKey = tamanho + 100;  // Uma chave que não está na árvore
            total_time += measureSearchTime(root, nonExistentKey);
        }

        // Converter nanosegundos para microsegundos
        double average_time = (double)total_time / (numExecutions * 1000);
        fprintf(file, "%d %.3f\n", tamanho, average_time);

        freeTree(root);
    }

    fclose(file);

    printf("Tempos de execução para o pior caso calculados e salvos em 'avl_worst_case.txt'.\n");
}

int main() {
    measureWorstCase();
    return 0;
}
