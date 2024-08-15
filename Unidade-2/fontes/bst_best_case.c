// binary_tree_best_case.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* node, int key) {
    if (node == NULL) return createNode(key);
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
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

Node* sortedArrayToBST(int* array, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;
    Node* root = createNode(array[mid]);

    root->left = sortedArrayToBST(array, start, mid - 1);
    root->right = sortedArrayToBST(array, mid + 1, end);

    return root;
}

unsigned long long measureTimeInNanoseconds(Node* root, int key) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    search(root, key);  // Best case: search for the root
    clock_gettime(CLOCK_MONOTONIC, &end);

    unsigned long long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    return elapsed_ns;
}

int main() {
    FILE *file;
    char filename[] = "binary_best_case_time.txt";
    int numExecutions = 10;
    int inicio = 100;
    int fim = 10000;
    int incremento = 100;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(file, "# Tamanho_do_Vetor Tempo_Total_de_Execucao_ns Tempo_Total_de_Execucao_us\n");

    srand(time(NULL));

    for (int tamanho = inicio; tamanho <= fim; tamanho += incremento) {
        int *vetor = (int*)malloc(tamanho * sizeof(int));
        if (vetor == NULL) {
            perror("Erro ao alocar memória");
            fclose(file);
            return 1;
        }

        for (int j = 0; j < tamanho; j++) {
            vetor[j] = j + 1;  // Best case: sorted array
        }

        unsigned long long t_total_ns = 0;

        for (int i = 0; i < numExecutions; i++) {
            Node* root = sortedArrayToBST(vetor, 0, tamanho - 1);  // Create balanced BST

            unsigned long long elapsed_ns = measureTimeInNanoseconds(root, vetor[(tamanho - 1) / 2]);
            t_total_ns += elapsed_ns;

            freeTree(root);
        }

        unsigned long long t_average_ns = t_total_ns / numExecutions;
        double t_average_us = (double)t_average_ns / 1000.0;  // Convert to microseconds with floating point

        fprintf(file, "%d %.3f\n", tamanho, t_average_us);

        free(vetor);
    }

    fclose(file);

    printf("Tempos de execução calculados e salvos em '%s'.\n", filename);

    return 0;
}
