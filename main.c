/*
	UFPB - Universidade Federal da Paraíba
	
	Exercício de fixação da disciplina de Estrutura de dados
	Lista Dinâmica Circular
	Professor: Leandro
	Aluno: Luis Henrique Pontes
	Mátricula: 20180163467
*/

#include "listaCirc.c"

int main(void)
{
	int id = 0;
	int continuar;
	
	setlocale(LC_ALL, "Portuguese");
	
	No *cabecaLista = NULL;
	
	char opcao_char = ' ';
	int opcao = opcao_char;
	
    while(opcao){
        printf(" *** Lista Encadeada ***\n\n");
        printf("1) Inserir registro no incio da Lista\n");//49
        printf("2) Inserir registro no fim da Lista\n");//50
        printf("3) Inserir registro ordenado na Lista\n");//51
        printf("4) Remover registro da Lista\n");//52
        printf("5) Buscar registro na Lista\n");//53
        printf("6) Tamanho da Lista\n");//54
        printf("7) Imprimir Lista\n");//55
        printf("8) Limpar Lista\n");//56
        printf("0) Encerrar\n");//48

        do{
        	fflush(stdin);
            printf("Opção:");
            scanf("%c", &opcao_char);
            fflush(stdin);
            opcao = opcao_char;
            if(opcao == 48){
            	if(!cabecaLista){
            		return EXIT_SUCCESS;
				}
            	free(cabecaLista);
				printf("Memória liberada com sucesso");
            	return EXIT_SUCCESS;
			}
        }while((opcao < 49 || opcao > 57));
  
        fflush(stdin);
        system("CLS");//limpa a tela

        switch(opcao){
            case 49:
            	printf("Digite id: ");
            	scanf("%d", &id);
                inserir(&cabecaLista, id); 
                imprimeLista(&cabecaLista, "Lista de ID: ");
            break;
            
            case 50:
            	printf("Digite id: ");
            	scanf("%d", &id);
                inserir_final(&cabecaLista, id); 
                imprimeLista(&cabecaLista, "Lista de ID: ");
            break;
            
            case 51:
            	printf("Digite id: ");
            	scanf("%d", &id);
            	inserir_ordenado(&cabecaLista, id);
				imprimeLista(&cabecaLista, "Lista de ID: "); 
            break;
            
            case 52:
            	continuar = validarResp("Confirma Remover elemento?", 1);//Retorna 1 se a resposta for verdadeira
    			system("CLS");
    			imprimeLista(&cabecaLista, "Lista de ID: ");
    			if(continuar){
    				printf("Digite ID: ");
	            	scanf("%d", &id);
	                if(!removeElemento(&cabecaLista, id)){
	                	printf("ID %d não pertence a lista\n");
					}else{
						printf("Elemento excluido com sucesso!!!\n\n");
	                	imprimeLista(&cabecaLista, "Lista de ID: ");
	                	if(listaVazia(cabecaLista)){
	    					id = 0;
						}
					}
				}
            break;
            
            case 53:
            	
                printf("\nDigite o elemento para busca: ");
                scanf("%d", &id);
                if(listaVazia(cabecaLista)){
                	printf("Lista vazia!!!\n");
				}else{
					if(buscaElemento(&cabecaLista, id)){
                		printf("%d pertence a lista\n", id);
					}else{
						printf("%d não pertence a lista\n", id);
					}
				}
            break;
            
            case 54:
                printf("A lista possui %d elementos\n\n", tamanhoLista(&cabecaLista));
                
            break;
            
            case 55:
            	imprimeLista(&cabecaLista, "Lista de ID: ");  
            break;
          
            case 56:
            	imprimeLista(&cabecaLista, "Lista de ID: ");
            	limparLista(&cabecaLista);
            	imprimeLista(&cabecaLista, "Lista de ID: ");
            break;
          
        }
    }//fim do while

}
