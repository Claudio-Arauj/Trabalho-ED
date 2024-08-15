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
int search(HashTable* hashTable, int value);

// Função Hash - Para transformar o valor da chave dada em uma chave da lista
unsigned int hash(int value, int m) {
    return value % m < 0 ? (value % m) + m : value % m;
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

// Inserindo elementos na Tabela Hash (Pior Caso)
void insert(HashTable* hashTable, int value) {
    unsigned int key = hash(value, hashTable->m);
    unsigned int index = hash(key, hashTable->m);
    Node* new_node = create_node(value);

    if (hashTable->nodes[index] == NULL) {
        hashTable->nodes[index] = new_node;
    } else {
        Node* index_node = hashTable->nodes[index];
        while(index_node->next != NULL) {
            index_node = index_node->next;
        }
        index_node->next = new_node;
    }

    hashTable->n++;
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

    unsigned int n = 10000;

    // Arquivo para armazenar os resultados
    FILE *file = fopen("hash_worst_case.txt", "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(file, "# Tamanho_da_Tabela Tempo_de_Execucao\n");

    for (int size = 100; size <= n; size += 100) {
        HashTable* hashTable = create_table(size);

        // Inicializador de randomização
        srand(time(NULL));

        // Inserindo elementos na tabela hash para simular o pior caso
        unsigned int last = 1;
        for (int i = 0; i < size; i++) {
            last = (rand() % (size * 10)) + 1;
            insert(hashTable, last);
        }

        // Inicializando variáveis de tempo
        struct timespec start, end;

        // Guardando valores de tempo
        clock_gettime(CLOCK_MONOTONIC, &start);
        int aux = search(hashTable, last);
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Calculando o tempo
        unsigned long long time = (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
        float time_microsseconds = (float)time / 1000.0;

        // Salvando o tempo no arquivo
        fprintf(file, "%d %.3f\n", size, time_microsseconds);

        // Liberando memória
        for (int i = 0; i < size; i++) {
            Node* node = hashTable->nodes[i];
            while (node != NULL) {
                Node* temp = node;
                node = node->next;
                free(temp);
            }
        }
        free(hashTable->nodes);
        free(hashTable);
    }

    fclose(file);
    printf("Tempos de execução calculados e salvos em 'hash_worst_case.txt'.\n");

    return 0;
}
