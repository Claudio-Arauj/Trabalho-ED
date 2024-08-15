#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de Nó
typedef struct node {
    int value;
    struct node* next;
} Node;

// Estrutura de Tabela Hash
typedef struct hashTable {
    unsigned int m; // Tamanho da tabela
    unsigned int n; // Quantidade de Elementos
    Node** nodes;
} HashTable;

// Protótipos das funções
void insert(HashTable* hashTable, int value);
void reHash(HashTable *hashTable);
int search(HashTable *hashTable, int value);

// Função Hash
unsigned int hash(int value, int m) {
    return value % m < 0 ? (value % m) + m : value % m;
}

// Função Re-hash
void reHash(HashTable* hashTable) {
    unsigned int old_m = hashTable->m;
    Node** old_nodes = hashTable->nodes;

    // Reconfigurar Tabela e Dobrar o Tamanho
    hashTable->m *= 2;  
    hashTable->n = 0;
    hashTable->nodes = (Node**)malloc(sizeof(Node*) * hashTable->m);

    for(int i = 0; i < hashTable->m; i++) {
        hashTable->nodes[i] = NULL;
    }

    for(int i = 0; i < old_m; i++) {
        Node* aux = old_nodes[i];
        while(aux != NULL) {
            insert(hashTable, aux->value);
            Node* toFree = aux;
            aux = aux->next;
            free(toFree);
        }
    }
    free(old_nodes);
}

// Função para calcular o fator de carga
float loadFactor(HashTable* hashTable) {
    return (float)hashTable->n / hashTable->m;
}

// Criando um novo nó
Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

// Inicialização de Tabela Hash
HashTable* create_table(unsigned int m) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->m = m;
    hashTable->n = 0;
    hashTable->nodes = (Node**)malloc(sizeof(Node*) * m);

    for(int i = 0; i < m; i++) {
        hashTable->nodes[i] = NULL;
    }

    return hashTable;
}

// Inserindo elementos na Tabela Hash
void insert(HashTable* hashTable, int value) {
    unsigned int key = hash(value, hashTable->m);

    if(loadFactor(hashTable) < 1) {
        unsigned int index = hash(key, hashTable->m);
        Node* new_node = create_node(value);

        if(hashTable->nodes[index] == NULL) {
            hashTable->nodes[index] = new_node;
        } else {
            Node* index_node = hashTable->nodes[index];
            while(index_node->next != NULL) {
                index_node = index_node->next;
            }
            index_node->next = new_node;
        }
        hashTable->n++;
    } else {
        reHash(hashTable);
        insert(hashTable, value);
    }
}

// Procurando elementos na tabela Hash
int search(HashTable* hashTable, int value) {
    unsigned int index = hash(value, hashTable->m); 
    Node* aux = hashTable->nodes[index];   

    while(aux != NULL) {
        if(aux->value == value) {
            return index;
        }
        aux = aux->next;
    }
    return -1;
}

int main() {
    // Tamanho fixo da tabela
    unsigned int n = 10000;

    // Arquivo para armazenar os resultados
    FILE *file = fopen("hash_average_case.txt", "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(file, "# Tamanho_da_Tabela Tempo_de_Execucao\n");

    // Criando tabela hash
    HashTable* hashTable = create_table(n);

    // Inicializador de randomização
    srand(time(NULL));

    for (int i = 100; i <= n; i += 100) {
        unsigned long long total_time = 0;

        for (int j = 0; j < 10; j++) {
            int random_value = rand() % (n * 10) + 1;
            insert(hashTable, random_value);

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);
            search(hashTable, random_value);
            clock_gettime(CLOCK_MONOTONIC, &end);

            unsigned long long time_taken = (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
            total_time += time_taken;
        }

        unsigned long long average_time = total_time / 10;
        double t_average_us = (double)average_time / 1000.0;
        fprintf(file, "%d %.3f\n", i, t_average_us);
    }

    fclose(file);
    printf("Tempos de execução calculados e salvos em 'hash_average_case.txt'.\n");

    return 0;
}
