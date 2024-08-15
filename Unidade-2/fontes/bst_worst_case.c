// binary_tree_worst_case.c

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

// Insere sempre à direita para criar uma árvore desbalanceada
Node* insert(Node* node, int key) {
    if (node == NULL) return createNode(key);
    node->right = insert(node->right, key); // Insere sempre à direita
    return node;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    return search(root->right, key); // Busca sempre à direita
}

void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->right); // Libera os nós da árvore desbalanceada
    free(node);
}

int main() {
    FILE *file;
    char filename[] = "binary_worst_case_time.txt";
    int numExecutions = 10;
    int inicio = 100;
    int fim = 10000;
    int incremento = 100;

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(file, "# Tamanho_do_Vetor Tempo_de_Execucao\n");

    for (int tamanho = inicio; tamanho <= fim; tamanho += incremento) {
        unsigned long long t_total = 0;

        for (int i = 0; i < numExecutions; i++) {
            Node* root = NULL;
            for (int j = 1; j <= tamanho; j++) {
                root = insert(root, j); // Insere sempre à direita para criar uma árvore desbalanceada
            }

            clock_t start = clock();
            search(root, tamanho); // Pior caso: busca pelo último elemento
            clock_t end = clock();

            unsigned long long t = (end - start) * 1000000 / CLOCKS_PER_SEC; // microseconds
            t_total += t;

            freeTree(root);
        }

        unsigned long long t_average = t_total / numExecutions;
        fprintf(file, "%d %llu\n", tamanho, t_average);
    }

    fclose(file);

    printf("Tempos de execução calculados e salvos em '%s'.\n", filename);

    return 0;
}
