#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct NODO{
	int valor;
	struct NODO *prox;
} nodo;


nodo * cria_nodo(int);
nodo * push(nodo **, nodo *);
nodo * pop(nodo **);
void imprime_pilha(nodo *);
nodo * pilha_arquivo(FILE * file, nodo * pilha);

int main(){
	int op = -1;
	nodo * pilha = NULL, *no = NULL;
	int conteudo;
	FILE * file;
	
	while (op != 5){
		system("cls");
		
		printf("******** Menu ********\n\n");
		printf("1 - Criar Nodo\n");
		printf("2 - Push\n");
		printf("3 - Pop\n");
		printf("4 - Imprimir pilha\n");
		printf("5 - Criar pilha via arquivo txt\n");
		printf("6 - Sair\n\n");
		printf("Opção: ");
		
		scanf("%d", &op);
		
		switch(op){
			case 1:
				printf("\nValor do Nodo a ser criado: ");
				scanf("%d", &conteudo);
				no = cria_nodo(conteudo);
				
				printf("\nNodo com o valor %d criado", (*no).valor);
				getch();
			break;
			case 2:
				push(&pilha, no);
				
				printf("\nÍtem empilhado com sucesso!");
				getch();
			break;
			case 3:
				no = pop(&pilha);
				
				printf("\nNodo de valor %d desempilhado com sucesso!", (*no).valor);
				free(no);
				
				getch();
			break;
			case 4:
				imprime_pilha(pilha);
				
				getch();
			break;
			case 5:
				pilha = pilha_arquivo(file, pilha);
				printf("\nPilha criada por leitura de um arquivo com sucesso!");
				
				getch();
			break;
		}
	}
	
	return 0;
}

nodo * cria_nodo(int valor){
	nodo *p;
	p = (nodo *) malloc (sizeof(nodo));
	p->valor = valor;
	p->prox = NULL;
	return p;
}

nodo * push(nodo **topo, nodo *no){
	if(*topo == NULL){
		*topo = no;
	}else{
		no->prox = *topo;
		*topo = no;
	}
	return *topo;
}

nodo * pop(nodo **topo){
	nodo *aux = *topo;
	if(aux == NULL){
		printf("PILHA VAZIA!");
		return NULL;
	}else{		
		aux = *topo;
		*topo = (*topo)->prox;		
		return aux;
	}
}

void imprime_pilha(nodo *topo){
	nodo *aux = topo;
	if(aux == NULL)
		printf("PILHA VAZIA!");

	while(aux != NULL){
		printf("%d ",aux->valor);
		aux = aux->prox;
	}
}

nodo * pilha_arquivo(FILE * file, nodo * pilha) {
	
	file = fopen("Pilha_nums.txt", "r");
	char arquivo_linha[20];
	
	if(file == NULL){
		printf("ERRO!!");
	} else {
		while(fgets(arquivo_linha, 20, file) != NULL){
			pilha = push(&pilha, cria_nodo(atoi(arquivo_linha)));
		}
  			
	}
	
	fclose(file);
	
	return pilha;
}

