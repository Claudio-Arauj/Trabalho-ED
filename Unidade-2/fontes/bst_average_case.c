// binary_tree_average_case.c

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

unsigned long long measureExecutionTime(Node* root, int* searchKeys, int numSearches) {
    clock_t start = clock();
    for (int i = 0; i < numSearches; i++) {
        search(root, searchKeys[i]);
    }
    clock_t end = clock();
    return (end - start) * 1000000 / CLOCKS_PER_SEC;  // microseconds
}

int main() {
    FILE *file;
    char filename[] = "binary_average_case_time.txt";
    int numExecutions = 10;
    int numSearches = 100;  // Reduced number of searches for more realistic average case
    int inicio = 100;
    int fim = 10000;
    int incremento = 100;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(file, "# Tamanho_do_Vetor Tempo_Total_de_Execucao\n");

    srand(time(NULL));

    for (int tamanho = inicio; tamanho <= fim; tamanho += incremento) {
        int *vetor = (int*)malloc(tamanho * sizeof(int));
        if (vetor == NULL) {
            perror("Erro ao alocar memória");
            fclose(file);
            return 1;
        }

        generateRandomArray(vetor, tamanho);

        unsigned long long t_total = 0;

        for (int i = 0; i < numExecutions; i++) {
            Node* root = NULL;
            for (int j = 0; j < tamanho; j++) {
                root = insert(root, vetor[j]);
            }

            int *searchKeys = (int*)malloc(numSearches * sizeof(int));
            if (searchKeys == NULL) {
                perror("Erro ao alocar memória");
                freeTree(root);
                free(vetor);
                fclose(file);
                return 1;
            }

            // Pick random search keys from the tree
            for (int k = 0; k < numSearches; k++) {
                searchKeys[k] = vetor[rand() % tamanho];
            }

            t_total += measureExecutionTime(root, searchKeys, numSearches);

            free(searchKeys);
            freeTree(root);
        }

        unsigned long long t_average = t_total / numExecutions;
        fprintf(file, "%d %llu\n", tamanho, t_average);

        free(vetor);
    }

    fclose(file);

    printf("Tempos de execução calculados e salvos em '%s'.\n", filename);

    return 0;
}
