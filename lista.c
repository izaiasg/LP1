/***************************************************************************************************************

UPE - CARUARU - LP1
IZAIAS GONÇALVES


	Lista simplesmente encadeada.


		# Será passado um arquivo onde:

	F = inserir na frente;
	A = inserir atrás;
	R = remover; //Caso o elemento solicitado não exista retorna "X" e Para remover é preciso buscar;
	C = contar quantos tem e imprimir o resultado na tela;
	P = imprime todos os elementos.
		
		# Exemplo:
		
	Entrada  Saída

	F 1    | 1 20  // 3º comando no caso o (P)
	A 20   | 20    // 5º comando (P) que imprime apenas o 20 pois o 1 foi removido
	P      | 1     // 6º comando (C) que imprime a quantidade de elementos
	R 1    | x     // 7º comando (R) que imprime "X" porque o elemento solicitado a remoção não existe
	P      |
	C      |
	R 3    |



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

struct No * buscar(struct No * cabeca, int x);
void inserirf(struct No * cabeca, int x);
void inserirb(struct No * cabeca, int x);
void remover(struct No * cabeca, int x, FILE * lista_res);
void print(struct No * cabeca, FILE * lista_res);
int contar(struct No * cabeca);


// Função principal (main)

int main(int argc, char const *argv[])
{

// Aloca dinamicamente a cabeca da lista

	int quantidade, num;
	char op;
	struct No *cabeca;
	cabeca = malloc (sizeof(struct No));
	cabeca->prox = NULL;

// Abre o aquivo atravez do diretorio que foi passado por linha de comando (Leitura)

	FILE * lista = fopen(argv[1], "r");
	FILE * lista_res = fopen(argv[2], "w");

	// Verifica se esta tudo OK com os arquivos
		
		if (lista == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

		if (lista_res == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}


		while(fscanf(lista, "%c", &op) != EOF)
		{

			if (op == 'F')
			{
				fscanf(lista, "%d", &num);
				inserirf(cabeca, num);
			}

			if (op == 'A')
			{
				fscanf(lista, "%d", &num);
				inserirb(cabeca, num);
			}

			if (op == 'R')
			{
				fscanf(lista, "%d", &num);
				remover(cabeca, num, lista_res);
			}

			if (op == 'C')
			{
				quantidade = contar(cabeca);
				fprintf(lista_res, "%d\n", quantidade);
			}

			if (op == 'P')
			{
				print(cabeca, lista_res);
			}


		}

	fclose(lista);
	fclose(lista_res);

	return 0;
}


// Função insere no começo

void inserirf(struct No * cabeca, int x)
{
	
	struct No *novo;
	novo = malloc(sizeof(struct No));
	novo->num = x;
	novo->prox = cabeca->prox;
	cabeca->prox = novo;

}


// Função inserir atrás

void inserirb(struct No * cabeca, int x)
{
	struct No * novo;
	
	if(cabeca->prox == NULL)
	{
		inserirf(cabeca, x);
	}else{
		
		struct No * ultimo = cabeca;

		while(ultimo->prox != NULL)
		{
			ultimo = ultimo->prox;
		}

		novo = malloc(sizeof(struct No));
		novo->num = x;
		novo->prox = NULL;
		ultimo->prox = novo;
	}

}


// Função print

void print(struct No * cabeca, FILE * lista_res)
{

	struct No * ultimo = cabeca;

	while(ultimo->prox != NULL)
	{
		ultimo = ultimo->prox;
		fprintf(lista_res, "%d ", ultimo->num);
	}

	fprintf(lista_res, "\n");


}

// Função Contar

int contar(struct No * cabeca)
{

	int quantidade = 0;

	struct No * ultimo = cabeca;

	while(ultimo->prox != NULL)
	{
		ultimo = ultimo->prox;
		++quantidade;
	}

	return quantidade;

}

// Função Buscar

struct No * buscar(struct No * cabeca, int x)
{

	struct No * ultimo = cabeca;

	while(ultimo->prox != NULL)
	{
		ultimo = ultimo->prox;
		if (ultimo->num == x)
		{
			break;
		}
	}

	return ultimo;


}


// Função Remover

void remover(struct No * cabeca, int x, FILE * lista_res)
{

	struct No * percorre;
	struct No * proximo;
	struct No * verifica;
	percorre = cabeca;
	proximo = cabeca->prox;

	verifica = buscar(cabeca, x);

	if (verifica->num != x)
	{
		fprintf(lista_res, "x \n");
	}

	while(proximo != NULL && proximo->num != x)
	{
		percorre = proximo;
		proximo = proximo->prox;
	}
	if (proximo != NULL)
	{
		percorre->prox = proximo->prox;
		free(proximo);
	}

}