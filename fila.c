/***************************************************************************************************************

UPE - CARUARU - LP1
IZAIAS GONÇALVES


 	As filas contém funções de enfileirar e desenfileirar.



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

void print(struct No * fila, FILE * fila_res);
void enfileirar(struct No * fila, int x);
int desenfileirar(struct No * fila);


// Função principal (main)

int main(int argc, char const *argv[])
{
	char op;
	int num, saiu;
	struct No * fila; // Cabeça da fila!
	fila = malloc(sizeof(struct No));
	fila->prox = NULL;

	// Abre o aquivo atravez do diretorio que foi passado por linha de comando (Leitura)

	FILE * ffila = fopen(argv[1], "r");
	FILE * fila_res = fopen(argv[2], "w");

	// Verifica se esta tudo OK com os arquivos
		
		if (ffila == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

		if (fila_res == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

	/* LEGENDA! (E) = enfileirar, (D) = Desenfileirar e (P) imprimir. */

		while(fscanf(ffila, "%c", &op) != EOF)
		{

			if (op == 'E')
			{
				fscanf(ffila, "%d", &num);
				enfileirar(fila, num);
			}

			if (op == 'D')
			{
				saiu = desenfileirar(fila);
				fprintf(fila_res, "O elemento %d saiu da fila! \n",saiu);
			}

			if (op == 'P')
			{
				print(fila, fila_res);
			}

		}

	fclose(ffila);
	fclose(fila_res);

	return 0;

}

// Função para enfileirar

void enfileirar(struct No * fila, int x)
{
	struct No * novo;
	novo = malloc(sizeof(struct No));

	if(fila->prox == NULL)
	{
		novo->num = x;
		novo->prox = fila->prox;
		fila->prox = novo;
	}else{
		
	struct No * ultimo = fila;

	while(ultimo->prox != NULL)
	{
		ultimo = ultimo->prox;
	}

	novo->num = x;
	novo->prox = NULL;
	ultimo->prox = novo;
	}

}

// Função para desenfileirar

int desenfileirar(struct No * fila)
{
	// Retornar o que fila está apontando 
	// Revomer-lo, ou seja, dizer que o primeiro agora é o segundo

	struct No *novo;
	novo = malloc(sizeof(struct No));

	novo = fila->prox;

	fila->prox = novo->prox;

	return novo->num;

}

// Função que imprime todos os elementos da fila

void print(struct No * fila, FILE * fila_res)
{

	struct No * ultimo = fila;

	if (ultimo->prox == NULL)
	{
		fprintf(fila_res, "A fila esta vazia! \n");
	}

	while(ultimo->prox != NULL)
	{
		ultimo = ultimo->prox;
		fprintf(fila_res, "%d ", ultimo->num);
	}

	fprintf(fila_res, "\n");

}