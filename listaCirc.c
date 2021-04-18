#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <locale.h>
#include <ctype.h>

#include "listaCirc.h"

#ifndef _LISTACIRC_C_
#define _LISTACIRC_C_

struct no
{
	int id;
	int idade;
	int cpf;
	int conta;
	int saldo;
	struct no *proximoNo;
};

No *criarNo(int id){
	
	No *no = (No*)malloc(sizeof(No));
	if(no){
		no->id = id;
		no->idade = 0;
		no->cpf = 0;
		no->conta = 0;
		no->saldo = 0;
		no->proximoNo = NULL;
	}
	return no;
}

int listaVazia(No *cabecaLista){//verifica se a lista está vazia
	return (cabecaLista == NULL);
}

int tamanhoLista(No **cabecaLista){//calcula o tamanho da lista
	
	if(!cabecaLista || !*cabecaLista)//se lista inválida ou vazia retorna 0
		return 0;
	int tamanho = 0;
	No *no = *cabecaLista;
	do{//se existir apenas um elemento na lista
		tamanho++;
		no = no->proximoNo;
	}while(no != *cabecaLista);//se existir mais elementos na lista

	return tamanho;
}

int inserir(No **cabecaLista, int id){
	
	No *no = criarNo(id);
	if(no){
		if(!(*cabecaLista)){//lista vazia insere no inicio
			*cabecaLista = no;
			no->proximoNo = no;
		}else{
			No *aux = *cabecaLista;
			while(aux->proximoNo != (*cabecaLista))//percorre a lista até o final
				aux = aux->proximoNo;
			//insere o elemento no início da lista
			aux->proximoNo = no;
			no->proximoNo = *cabecaLista;
			*cabecaLista = no;
		}
		return 1;
	}
	return 0;
}

int inserir_final(No **cabecaLista, int id){
	
	No *no = criarNo(id);
	if(no){
		if(!(*cabecaLista)){//lista vazia insere no inicio
			return inserir(cabecaLista,id);
		}else{
			No *aux = *cabecaLista;
			while(aux->proximoNo != (*cabecaLista))//procura o final da lista
				aux = aux->proximoNo;
			//insere o elemento
			aux->proximoNo = no;
			no->proximoNo = *cabecaLista;
		}
		return 1;
	}
	return 0;
}

int inserir_ordenado(No **cabecaLista, int id){

	No *no = criarNo(id);
	if(no){
		if(!(*cabecaLista) || (*cabecaLista)->id > id){//lista vazia ou elemento maior na primeira posição insere no inicio
			return inserir(cabecaLista,id);
		}else{//
			No *ant = *cabecaLista, *atual = (*cabecaLista)->proximoNo;
			while(atual != *cabecaLista && atual->id < id){//percorre a lista até completar uma volta na lista ou achar o elemento
				ant = atual;
				atual = atual->proximoNo;
			}//insere entre o ant e o atual
			ant->proximoNo = no;
			no->proximoNo = atual;
		}//fim do else
		return 1;
	}
	return 0;
}

int buscaElemento(No **cabecaLista, int id)//busca elemento na lista
{
	if(listaVazia(*cabecaLista))//se lista vazia
		return 0;
	
	No *no = *cabecaLista;
	while(no->proximoNo != (*cabecaLista) && no->id != id)//percorre a lista
		no = no->proximoNo;
	if(no->id != id)//se não encontrou retorna 0
		return 0;
	else
		return 1;		
}

void imprimeLista(No **cabecaLista, char *mensagem){//imprime a lista
	
	printf("%s", mensagem);
	
		if(cabecaLista && *cabecaLista){//se lista válida ou não vazia
			No *no = *cabecaLista;
			if(no == *cabecaLista){
				printf("%d -> ", no->id);
				while(no->proximoNo != (*cabecaLista)){//percorre a lista
					printf("%d -> ", no->proximoNo->id);//e imprime a lista
					no = no->proximoNo;
				}
			}
		}
	printf(" NULL\n\n");
}

void limparLista(No **cabecaLista){//limpa a lista
	
	if(cabecaLista && (*cabecaLista)){
		No *prox = NULL;
		No *aux = *cabecaLista;
		while(aux->proximoNo != *(cabecaLista)){//percorre a lista e libera a memória alocada
			prox = aux->proximoNo;
			free(aux);
			aux = prox;
		}
		free(prox);
		*cabecaLista = NULL;
	}
}

int removeElemento(No **cabecaLista, int id){
	
	if(!cabecaLista || !(*cabecaLista))//lista inválida ou vazia
		return 0;
		
	No *no = *cabecaLista;
	if(no->id == id){//remoção no inicio
		if(no == no->proximoNo){//lista tem um único elemento
			free(no);
			*cabecaLista = NULL;
		}else{//lista possui mais de um elemento
			No *atual = *cabecaLista;
			while(atual->proximoNo != (*cabecaLista)){//busca último elemento da lista
				atual = atual->proximoNo;
			}//faz a remoção da lista	
			atual->proximoNo = (*cabecaLista)->proximoNo;
			*cabecaLista = (*cabecaLista)->proximoNo;
			free(no);
		}
		return 1;
	}//fim remoção no início
	
	No *ant = no;
	no = no->proximoNo;
	while(no != (*cabecaLista) && no->id != id){//procura o elemento na lista
		ant = no;
		no = no->proximoNo;
	}
	if(no == *cabecaLista)//deu a volta completa na lista, não encontrou
		return 0;
	ant->proximoNo = no->proximoNo;//faz a remoção da lista
	free(no);
	
	return 1;
}

int validarResp(char *mensagem, int padrao) {
   int op;
   char cPadrao = (padrao ? 's' : 'n');

   do {
      printf("%s [S ou N] %c", mensagem, cPadrao);
      op = getch();
      printf("\n" );
   } while (op != 's' && op != 'S' && op != 'n' && op != 'N' && op != 13);

    if(op == 13)
        return padrao;

   return ((op == 's' || op == 'S') ? 1 : 0);
}

#endif
