#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Árvore
typedef struct No{
    int num;
    struct No *esq, *dir;
} No;

typedef struct Arvore{
    struct No *raiz;
} Arvore;

// Pilha auxiliar
typedef struct Elemento{
	struct No *num;
	struct Elemento *prox;
} Elemento;

typedef struct Pilha{
    struct Elemento *topo;
} Pilha;

Arvore* cria_arvore();
Pilha* cria_pilha();
void insere_elemento(Arvore *arv, int num);
void consulta_no(Arvore *arv);
void consulta_arvore_ordem(Arvore *arv, Pilha *pi);
void consulta_arvore_pre_ordem(Arvore *arv, Pilha *pi);
void consulta_arvore_pos_ordem(Arvore *arv, Pilha *pi);
void remove_elemento(Arvore *arv);
void esvaziar_arvore(Arvore *arv, Pilha *pi);

void criar_arvore_arquivo(Arvore *arv, FILE * file);

No *aux;
No *aux1;
No *novo;
No *anterior;

Elemento *aux2;

int main(){
    Arvore *arv = cria_arvore();
    Pilha *pi = cria_pilha();
    
    FILE * file;
    int op, num;
    
    do{
		system("cls");
    	printf("-- Menu --\n\n");
    	printf("1 - Inserir\n2 - Consultar\n3 - Consulta (ordem)\n4 - Consulta (pre-ordem)\n5 - Consulta (pos-ordem)\n");
    	printf("6 - Remover elemento\n7 - Esvaziar Arvore\n8 - Criar Arvore via arquivo txt\n0 - Sair\n");
        printf("----------\nOpcao: ");
        scanf("%d", &op);
        
        switch(op){
        	case 1:
				printf("Digite o numero a ser inserido na arvore: ");
				scanf("%d",&num);
				
        		insere_elemento(arv, num);
        	break;
        	case 2:
        		consulta_no(arv);
        	break;
        	case 3:
        		consulta_arvore_ordem(arv, pi);
        	break;
        	case 4:
        		consulta_arvore_pre_ordem(arv, pi);
        	break;
        	case 5:
        		consulta_arvore_pos_ordem(arv, pi);
        	break;
        	case 6:
        		remove_elemento(arv);
        	break;
        	case 7:
        		esvaziar_arvore(arv, pi);
        	break;
        	case 8:
        		criar_arvore_arquivo(arv, file);
        	break;
		}
	} while(op != 0);

    return 0;
}

Arvore* cria_arvore(){
    Arvore* arv = (Arvore*) malloc(sizeof(Arvore));
    if(arv != NULL){
        arv->raiz= NULL;
    }
    return arv;
}

Pilha* cria_pilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi != NULL){
        pi->topo= NULL;
    }
    return pi;
}

void insere_elemento(Arvore *arv, int num){
	
	No *novo =(No*) malloc(sizeof(No));
	novo->num = num;
	novo->esq = NULL;
	novo->dir = NULL;
	
	if(arv->raiz == NULL){
		arv->raiz = novo;
	}else{
		int achou;
		aux = arv->raiz;
		achou = 0;
		
		while(achou == 0){
			// Vai pra esquerda
			if(novo->num < aux->num){
				if(aux->esq == NULL){
					aux->esq = novo;
					achou = 1;
				}else{
					aux = aux->esq;
				}
			// Vai para a direita
			}else if(novo->num >= aux->num){
				if(aux->dir == NULL){
					aux->dir = novo;
					achou = 1;
				}else{
					aux = aux->dir;
				}
			}
		}
	}
	printf("\nNumero inserido na arvore!");
	getch();
}

void consulta_no(Arvore *arv){
	
	if(arv->raiz == NULL){
		printf("\nArvore Vazia!!");
	}else{
	    int numero, achou;
		printf("Digite o numero a ser consultado: ");
		scanf("%d", &numero);
		achou = 0;
		
		aux = arv->raiz;
		
		while(aux != NULL && achou == 0){
			
			if(aux->num == numero){
				printf("Numero %d encontrado!", numero);
				achou = 1;
			}else if(numero < aux->num){
				aux = aux->esq;
				}else{
					aux = aux->dir;
				}
        }
        if(achou == 0) printf("Número não encontrado!");
    }

	getch();
}

void consulta_arvore_ordem(Arvore *arv, Pilha *pi){
	
	if(arv->raiz == NULL){
		printf("\nArvore Vazia!!");
	}else{
		aux = arv->raiz;
		pi->topo = NULL;
		do{
			while(aux != NULL){
				Elemento *aux_pilha =(Elemento*) malloc(sizeof(Elemento));
				aux_pilha->num = aux;
				aux_pilha->prox = pi->topo;
				pi->topo = aux_pilha;
				aux = aux->esq;
			}
			
			if(pi->topo != NULL){
				aux2 = pi->topo;
				printf("%d ", aux2->num->num);
				
				aux = pi->topo->num->dir;
				pi->topo = pi->topo->prox;
			}
		}while(pi->topo != NULL || aux != NULL);
	}
	getch();
}

void consulta_arvore_pre_ordem(Arvore *arv, Pilha *pi){
	
	Elemento *aux_pilha;
	
	if(arv->raiz == NULL){
		printf("\nArvore Vazia!!");
	}else{
		aux = arv->raiz;
		pi->topo = NULL;
		do{
			while(aux != NULL){
				aux_pilha =(Elemento*) malloc(sizeof(Elemento));
				printf("%d ", aux->num);
				
				aux_pilha->num = aux;
				aux_pilha->prox = pi->topo;
				pi->topo = aux_pilha;
				aux = aux->esq;
			}
			
			if(pi->topo != NULL){
				aux_pilha = pi->topo;
				pi->topo = pi->topo->prox;
				aux = aux_pilha->num->dir;
			}
		}while(pi->topo != NULL || aux != NULL);
	}
	getch();
}

void consulta_arvore_pos_ordem(Arvore *arv, Pilha *pi){
	
	if(arv->raiz == NULL){
		printf("\nArvore Vazia!!");
    }else{
        aux = arv->raiz;
        pi->topo = NULL;
        do{
            do{
				while(aux != NULL){
					Elemento *aux_pilha = (Elemento*) malloc(sizeof(Elemento));
					aux_pilha->num = aux;
					aux_pilha->prox =pi-> topo;
					pi->topo = aux_pilha;
					aux = aux->esq;
				}
				
				if(pi->topo->num->dir != NULL){
					aux = pi->topo->num->dir;
				}
			}while(aux != NULL);
			if(pi->topo!= NULL){
				
				printf("%d ", pi->topo->num->num);
				
				if(pi->topo->prox != NULL){
					if(pi->topo->prox->num->dir != NULL && pi->topo->prox->num->dir != pi->topo->num){
						aux = pi->topo->prox->num->dir;
						pi->topo = pi->topo->prox;
					}else{
						while(pi->topo->prox != NULL && pi->topo->prox->num->dir == pi->topo->num){
							pi->topo = pi->topo->prox;
							printf("%d ", pi->topo->num->num);
						}
						
						pi->topo = pi->topo->prox;
						
						if(pi->topo != NULL){
							aux  = pi->topo->num->dir;
						}else{
							aux = NULL;
						}
					}
					
				}else{
					pi->topo = pi->topo->prox;
					aux = NULL;
				}
			}
		}while(pi->topo != NULL || aux != NULL);

	}
	getch();
}

void remove_elemento(Arvore *arv){
	
	if(arv->raiz == NULL){
		printf("\nArvore Vazia!!");
	}else{
        int numero, achou;
        printf("Digite o numero a ser removido da arvore: ");
        scanf("%d", &numero);
        
        aux = arv->raiz;
        achou = 0;
        
        while(aux != NULL && achou == 0){
            if(aux->num == numero){
                achou = 1;
             }else if(aux->num > numero){
                    aux = aux->esq;
                }else{
                    aux = aux->dir;
                }
        }
        
        if(achou == 0){
            printf("Numero nao encontrado!");
        }else{
            if(aux != arv->raiz){
                anterior = arv->raiz;
                while(anterior->dir != aux && anterior->esq != aux){
                    if(anterior->num > numero){
                        anterior = anterior->esq;
                    }else{
                        anterior = anterior->dir;
                    }
                }
                if(aux->dir == NULL && aux->esq == NULL){
                    if(anterior->dir == aux){
                        anterior->dir = NULL;
                    }else{
                        anterior->esq = NULL;
                    }
                    free(aux);
                }else{
                    if(aux->dir != NULL  && aux->esq == NULL){
                        if(anterior->esq == aux){
                            anterior->esq = aux->dir;
                        }else{
                            anterior->dir = aux->dir;
                        }
                        free(aux);
                    }else if(aux->esq != NULL && aux->dir == NULL){
                        if(anterior->esq == aux){
                            anterior->esq = aux->esq;
                        }else{
                            anterior->dir = aux->esq;
                        }
                        free(aux);
                    }else if(aux->esq != NULL && aux->dir != NULL){
                        if(anterior->dir == aux){
                            anterior->dir = aux->dir;
                            aux1 = aux->esq;
                        }else{
                            anterior->esq = aux->dir;
                            aux1 = aux->esq;
                        }
                        free(aux);
                        aux = anterior;
                        while(aux != NULL){
                        	
                            if(aux->num < aux1->num){
                                if(aux->dir == NULL){
                                    aux->dir = aux1;
                                    aux = NULL;
                                }else{
                                    aux = aux->dir;
                                }
                            }else if(aux->num > aux1->num){
                                if(aux->esq == NULL){
                                    aux->esq = aux1;
                                    aux = NULL;
                                }else{
                                    aux = aux->esq;
                                }
                            }
                        }
                    }
                }
            }else{
                if(aux->dir == NULL && aux->esq == NULL){
                    free(aux);
                    arv->raiz = NULL;
                }else{
                    if(aux->dir != NULL && aux->esq == NULL){
                        arv->raiz = aux->dir;
                        free(aux);
                    }else if(aux->esq != NULL && aux->dir == NULL){
                        arv->raiz = arv->raiz->esq;
                        free(aux);
                    }else if(aux->dir != NULL && aux->esq != NULL){
                        arv->raiz = aux->dir;
                        aux1 = aux->esq;
                        free(aux);
                        aux = arv->raiz;
                        
                        while(aux != NULL){
                        	
                            if(aux->num < aux1->num){
                                if(aux->dir == NULL){
                                    aux->dir = aux1;
                                    aux = NULL;
                                }else{
                                    aux = aux->dir;
                                }
                            }else if(aux->num > aux1->num){
                                if(aux->esq == NULL){
                                    aux->esq = aux1;
                                    aux = NULL;
                                }else{
                                    aux = aux->esq;
                                }
                            }
                        }
                    }
                }
            }
            printf("Numero excluido da Arvore!");
        }
    }
    getch();
}

void esvaziar_arvore(Arvore *arv, Pilha *pi){
	
	if(arv->raiz == NULL){
		printf("\nArvore Vazia!!");
	}else{
        aux = arv->raiz;
        pi->topo = NULL;
        do{
            while(aux != NULL){
                Elemento *aux_pilha =(Elemento*) malloc(sizeof(Elemento));
                printf("%d ", aux->num);
                
                aux_pilha->num = aux;
                aux_pilha->prox = pi->topo;
                pi->topo = aux_pilha;
                aux = aux->esq;
            }
            
            if(pi->topo != NULL){
                aux2 = pi->topo;
                pi->topo = pi->topo->prox;
                aux = aux2->num->dir;
            }
        }while(pi->topo != NULL || aux != NULL);
        
        aux2 = pi->topo;
        
        while(aux2 != NULL){
            pi->topo = pi->topo->prox;
            free(pi->topo->num);
            free(aux2);
            aux2 = pi->topo;
        }
        
        arv->raiz = NULL;
        printf("\nArvore esvaziada");
	}
	
	getch();
	
}

void criar_arvore_arquivo(Arvore *arv, FILE * file){
	file = fopen("Arvore_nums.txt", "r");
	char arquivo_linha[20];
	
	if(file == NULL){
		printf("ERRO!!");
	} else {
		while(fgets(arquivo_linha, 20, file) != NULL){
			insere_elemento(arv, atoi(arquivo_linha));
		}
  			
	}
	
	fclose(file);
}
