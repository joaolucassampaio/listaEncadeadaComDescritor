
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Inclusão da biblioteca para acesso aos números aleatórios

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

int main(int argc, char *argv[]) {
	struct node *lista, *p; //Definição de ponteiros auxiliares para manipulação dos nós
	struct descriptor *d; //Definição de um ponteiro auxiliar para manipulação do descritor
	int quantifyNode; //Definição de uma variável inteira para armazenar a quantidade de nós a serem inseridos na lista
	int count = 0; //Definição uma variável inteira para contagem de iterações
	
	//Alocação dinâmica de memória para o descritor d e inicialização dos seus campos
	d = malloc(sizeof(struct descriptor));
	//Campos size, first e last são inicializados em 0 e NULl indicando que a lista está vazia
	d->size = 0;
	d->first = NULL;
	d->last = NULL;
	
	//Solicita ao usuário que insira a quantidade de nós a serem adicionados na lista
	printf("Quantos nos voce deseja adicionar a lista? Digite um numero inteiro: ");
	scanf("%i", &quantifyNode);
	//Confirmação da quantidade de nos escolhidas
	printf("\nAdicionando %d nos a lista: \n", quantifyNode);
		
	//Inicializa o gerador de números aleatórios
	srand(time(NULL));
	
	//Looping que continua até que o número desejado de nós seja inserido na lista encadeada
	while(count < quantifyNode) {
		//Alocação de memória para um novo nó p
		p = malloc(sizeof(struct node));
		//Atribuição de um valor aleatório ao campo info
		p->info = rand()%100; //0 à 99
		//Inserção à esquerda:
		p->next = lista;
		lista = p;
		
		//Ordenação dos nós da lista encadeada em ordem crescente, mantendo o descritor atualizado
		if(d->first == NULL || p->info <= d->first->info) { // Se a lista estiver vazia ou o valor for menor que o primeiro elemento
			p->next = d->first;
			d->first = p;
		} else {
			struct node *current = d->first;
			while(current->next != NULL && current->next->info < p->info) { //Encontra o ponto de inserção na lista
				current = current->next;
			}
			p->next = current->next;
			current->next = p;
		}
		
		//Incremento do tamanho da lista e do contador, e impressão do valor do nó adicionado
		d->size++;
		count++;
		printf("%i ", p->info);
	};
		
	//Exibição do total de nós na lista antes da remoção
	printf("\nTotal de nos: %d\n", d->size);
	
	//Encontra o último nó da lista
	struct node *lastNode = d->first;
	while (lastNode->next != NULL) { // percorre até o final da lista
	    lastNode = lastNode->next;
	}
	
	//Atribuí o último nó encontrado a d->last
	d->last = lastNode;
	
	printf("\nLista ordenada:\n");
	//Imprimir a lista ordenada
	struct node *temp = d->first;
	while(temp != NULL) {
		printf("%i ", temp->info);
		temp = temp->next;
	}	
	printf("\n");
	
	//Calcular o valor médio dos nós na lista
	temp = d->first;
    int soma = 0; 
    while (temp != NULL) { //Realiza um somatório
        soma += temp->info;
        temp = temp->next;
    }
    float media = (float)soma / d->size;
    printf("\nValor medio:\n");
	printf("%.2f\n", media);
	
	//Remover o primeiro nó com valor imediatamente superior ao valor médio
    struct node *anterior = NULL;
    struct node *atual = d->first;
    while (atual != NULL && atual->info <= media) { //Percorre a lista ate achar o valor maximo abaixo da media
        anterior = atual;
        atual = atual->next;
    }
    if (atual != NULL) { // Se fosse NULL, significa que estaria no final da lista.
        if (anterior == NULL) {
            d->first = atual->next;
        } else {
            anterior->next = atual->next; // Aponta para o nó seguinte
        }
        free(atual); // Libera o espaço
        d->size--; //Atualiza o tamanho da lista
    }
    
    printf("\nLista com descritor final:\n");
    //Imprimir a lista com descritor final
    temp = d->first;
    while (temp != NULL) {
        printf("%i ", temp->info);
        temp = temp->next;
    }
    printf("\n");
    printf("\nPrimeiro no: %d\n", d->first != NULL ? d->first->info : -1);
    printf("Ultimo no: %d\n", d->last != NULL ? d->last->info : -1);
    printf("Total de nos: %d\n", d->size);
	return 0;
}
