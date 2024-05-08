#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Definição da biblioteca para acesso aos números aleatórios

//Definição da estrutura básica de um nó
struct node {
    int info; //Campo do conteúdo da célula
    struct node *next; //Campo do endereço da célula seguinte
};

//Definição da estrutura básica de um descritor
//É uma estrutura cuja função é fornecer informações sobre a lista encadeada
struct descriptor {
    int size; //Tamanho total da lista (Número total de nós)
    struct node *first; //Ponteiro para o primeiro nó da lista
    struct node *last; //Ponteiro para o último nó da lista
};

// Protótipo da função sortedInsert, será inserida logo adiante
void sortedInsert(struct node **head_ref, struct node *new_node);

//Algoritmo ordenação está implementado em 2 funções:
//Percorre os nós da lista e chama a função sortedInsert para inserir cada nó na lista
void insertionSort(struct node **head_ref) {
    struct node *sorted = NULL;
    struct node *current = *head_ref;
    while (current != NULL) {
        struct node *next = current->next;
        sortedInsert(&sorted, current);
        current = next;
    }
    *head_ref = sorted;
}

//
void sortedInsert(struct node **head_ref, struct node *new_node) {
    struct node *current;
    if (*head_ref == NULL || (*head_ref)->info >= new_node->info) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        current = *head_ref;
        while (current->next != NULL && current->next->info < new_node->info) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

int main(int argc, char *argv[]) {
    struct node *lista, *p; //Definição de ponteiros auxiliares para manipulação dos nós
    struct descriptor *d; //Definição de um ponteiro auxiliar para manipulação do descritor
    int quantifyNode; //Definição de uma variável inteira para armazenar a quantidade de nós a serem inseridos na lista
    int count = 0; //Definição uma variável inteira para contagem de iterações
    
    //d recebe o endereço da memória onde uma nova instância da estrutura básica de um descritor está sendo alocada dinamicamente
    d = malloc(sizeof(struct descriptor));
    //Campos size, first e last são inicializados indicando que a lista está vazia
    d->size = 0;
    d->first = NULL;
    d->last = NULL;
    
    //Obtendo quantidade de nós:
    printf("Quantos nos voce deseja adicionar a lista? Digite um numero inteiro: ");
    scanf("%i", &quantifyNode);
    printf("\nAdicionando %d nos a lista: \n", quantifyNode);
        
    //Inicializa o gerador de números pseudoaleatórios (RNG - Random Number Generator)
    srand(time(NULL));
    
    //Inserção à esquerda:
    while(count < quantifyNode) {
        p = malloc(sizeof(struct node));
        p->info = rand()%100; // Número aleatório de 0 à 99
        p->next = d->first;
        d->first = p;

        // Atualizar last para apontar para o último nó inserido
        if (d->last == NULL)
            d->last = p;

        d->size++;
        count++;
        printf("%i ", p->info);
    }
    
    printf("\n");

    // Ordenação dos nós após a inserção
    insertionSort(&d->first);
    
    // Atualizar last para apontar para o novo último nó após a ordenação
    struct node *temp = d->first;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    d->last = temp;

    printf("\nLista ordenada:\n");
    // Imprimir a lista ordenada
    temp = d->first;
    while (temp != NULL) {
        printf("%i ", temp->info);
        temp = temp->next;
    }
    printf("\n");
    
    // Calcular o valor médio dos nós na lista
    temp = d->first;
    int soma = 0;
    while (temp != NULL) {
        soma += temp->info;
        temp = temp->next;
    }
    float media = (float)soma / d->size;
    printf("\nValor medio:\n");
    printf("%.2f\n", media);
    
    // Remover o primeiro nó com valor imediatamente superior ao valor médio
    struct node *anterior = NULL;
    struct node *atual = d->first;
    while (atual != NULL && atual->info <= media) {
        anterior = atual;
        atual = atual->next;
    }
    if (atual != NULL) {
        if (anterior == NULL) {
            d->first = atual->next;
        } else {
            anterior->next = atual->next;
        }
        if (atual == d->last)
            d->last = anterior;
        free(atual);
        d->size--;
    }
    
    printf("\nLista com descritor final:\n");
    // Imprimir a lista com descritor final
    temp = d->first;
    while (temp != NULL) {
        printf("%i ", temp->info);
        temp = temp->next;
    }
    printf("\n");

    return 0;
}
