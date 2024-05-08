#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Defini��o da biblioteca para acesso aos n�meros aleat�rios

//Defini��o da estrutura b�sica de um n�
struct node {
    int info; //Campo do conte�do da c�lula
    struct node *next; //Campo do endere�o da c�lula seguinte
};

//Defini��o da estrutura b�sica de um descritor
//� uma estrutura cuja fun��o � fornecer informa��es sobre a lista encadeada
struct descriptor {
    int size; //Tamanho total da lista (N�mero total de n�s)
    struct node *first; //Ponteiro para o primeiro n� da lista
    struct node *last; //Ponteiro para o �ltimo n� da lista
};

// A fun��o insertionSort realiza a ordena��o da lista encadeada utilizando o algoritmo de ordena��o por inser��o.
void insertionSort(struct node **head_ref) {
    struct node *sorted = NULL;
    struct node *current = *head_ref;
    while (current != NULL) {
        struct node *next = current->next;
        sortedInsert(&sorted, current);
        current = next;
    }
    *head_ref = sorted;
};

int main(int argc, char *argv[]) {
    struct node *lista, *p; //Defini��o de ponteiros auxiliares para manipula��o dos n�s
    struct descriptor *d; //Defini��o de um ponteiro auxiliar para manipula��o do descritor
    int quantifyNode; //Defini��o de uma vari�vel inteira para armazenar a quantidade de n�s a serem inseridos na lista
    int count = 0; //Defini��o uma vari�vel inteira para contagem de itera��es
    
    //d recebe o endere�o da mem�ria onde uma nova inst�ncia da estrutura b�sica de um descritor est� sendo alocada dinamicamente
    d = malloc(sizeof(struct descriptor));
    //Campos size, first e last s�o inicializados indicando que a lista est� vazia
    d->size = 0;
    d->first = NULL;
    d->last = NULL;
    
    //Obtendo quantidade de n�s:
    printf("Quantos nos voce deseja adicionar a lista? Digite um numero inteiro: ");
    scanf("%i", &quantifyNode);
    printf("\nAdicionando %d nos a lista: \n", quantifyNode);
        
    //Inicializa o gerador de n�meros pseudoaleat�rios (RNG - Random Number Generator)
    srand(time(NULL));
    
    //Inser��o � esquerda:
    while(count < quantifyNode) {
        p = malloc(sizeof(struct node));
        p->info = rand()%100; // N�mero aleat�rio de 0 � 99
        p->next = d->first;
        d->first = p;

        // Atualizar last para apontar para o �ltimo n� inserido
        if (d->last == NULL)
            d->last = p;

        d->size++;
        count++;
        printf("%i ", p->info);
    }
    
    printf("\n");

    // Ordena��o dos n�s ap�s a inser��o
    insertionSort(&d->first);
    
    // Atualizar last para apontar para o novo �ltimo n� ap�s a ordena��o
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
    
    // Calcular o valor m�dio dos n�s na lista
    temp = d->first;
    int soma = 0;
    while (temp != NULL) {
        soma += temp->info;
        temp = temp->next;
    }
    float media = (float)soma / d->size;
    printf("\nValor medio:\n");
    printf("%.2f\n", media);
    
    // Remover o primeiro n� com valor imediatamente superior ao valor m�dio
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
