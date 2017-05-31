/***************************************************************************************************************

UPE - CARUARU - LP1
IZAIAS GONÇALVES

	As pilhas devem ter as funções de empilhar e desempilhar. 



***************************************************************************************************************/

// Bibliotecas 

#include <stdio.h>
#include <stdlib.h>

// Declarando a estrutura

	struct No
		{
			int num;
			struct No *prox;
		};

//Protótipos

void print(struct No * pilha, FILE * pilha_res);
void empilhar(struct No * pilha, int x);
int desempilhar(struct No * pilha);

// Função principal (main)

int main(int argc, char const *argv[])
{
	char op;
	int num, saiu;
	struct No * pilha; // Cabeça da pilha!
	pilha = malloc(sizeof(struct No));
	pilha->prox = NULL;

	// Abre o aquivo atravez do diretorio que foi passado por linha de comando (Leitura)

	FILE * fpilha = fopen(argv[1], "r");
	FILE * pilha_res = fopen(argv[2], "w");

	// Verifica se esta tudo OK com os arquivos
		
		if (fpilha == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

		if (pilha_res == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

	/* LEGENDA! (E) = Empilhar, (D) = Desempilhar e (P) imprimir. */

		while(fscanf(fpilha, "%c", &op) != EOF)
		{

			if (op == 'E')
			{
				fscanf(fpilha, "%d", &num);
				empilhar(pilha, num);
			}

			if (op == 'D')
			{
				saiu = desempilhar(pilha);
				fprintf(pilha_res, "O elemento %d saiu da pilha! \n",saiu);
			}

			if (op == 'P')
			{
				print(pilha, pilha_res);
			}

		}

	fclose(fpilha);
	fclose(pilha_res);

	return 0;

	
}

// Função empilhar

void empilhar(struct No * pilha, int x)
{
	struct No *novo;
	novo = malloc(sizeof(struct No));

	if(pilha->prox == NULL)
	{
		novo->num = x;
		novo->prox = pilha->prox;
		pilha->prox = novo;
	}else{
		
	struct No * ultimo = pilha;

	while(ultimo->prox != NULL)
	{
		ultimo = ultimo->prox;
	}

	novo->num = x;
	novo->prox = NULL;
	ultimo->prox = novo;
	}
}

// Função desempilhar

int desempilhar(struct No * pilha)
{

	struct No * penultimo = pilha;
	struct No * ultimo = pilha->prox;

	while(ultimo->prox != NULL)
	{
		ultimo = ultimo->prox;
		penultimo = penultimo->prox;
	}

	penultimo->prox = NULL;

	return ultimo->num;
}

// Função imprimir

void print(struct No * pilha, FILE * pilha_res)
{

	struct No * ultimo = pilha;

	if (ultimo->prox == NULL)
	{
		fprintf(pilha_res, "A pilha esta vazia! \n");
	}

	while(ultimo->prox != NULL)
	{
		ultimo = ultimo->prox;
		fprintf(pilha_res, "%d ", ultimo->num);
	}

	fprintf(pilha_res, "\n");

}