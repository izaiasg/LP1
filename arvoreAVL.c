/* Izaias Goçalves // Árvore AVL; */

// Bibliotecas usada

#include <stdio.h>
#include <stdlib.h>

// Estrutura base

struct No
{
	int numero;
	struct No *fe;
	struct No *fd;
	int fb;
};

struct Nof
{
	struct No *no_arvore;
	struct Nof *prox;
};

// Protótipos

void inserir(struct No **raiz, struct No * novo);
void rotacao_direita(struct No **raiz);
void rotacao_esquerda(struct No **raiz);
void rotacao_esq_dir(struct No *raiz);
void rotacao_dir_esq(struct No *raiz);
void balancear(struct No *raiz);
void enfileirar(struct Nof **fila, struct No *no);
void imprimir(struct No *raiz, struct Nof *fila, FILE * favl_res);
struct No * desenfileirar(struct Nof **fila);
int altura(struct No *raiz);

// Main

int main(int argc, char const *argv[])
{

	// Declarando a raiz

	struct No *raiz = NULL; // raiz da árvore

	// Declarando a fila 

	struct Nof *lista = NULL; // Cabeça 



	// Abre o aquivo atravez do diretorio que foi passado por linha de comando (Leitura)

	FILE * favl = fopen(argv[1], "r");
	FILE * favl_res = fopen(argv[2], "w");

	// Verifica se esta tudo OK com os arquivos
		
		if (favl == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

		if (favl_res == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}


	// Lendo do arquivo e chamando as fuções

	int quantidade, i, num;

	fscanf(favl, "%d", &quantidade);

	printf("%d\n", quantidade);

	for (i = 0; i < quantidade; ++i)
	{
		fscanf(favl, "%d", &num);
		printf("%d\n", num);

		// Criar novo elemento

		struct No * novo;
		novo = malloc(sizeof(struct No));
		novo->numero = num;
		novo->fe = NULL;
		novo->fd = NULL;
		novo->fb = 0;

		inserir(&raiz, novo);
		balancear(raiz);
		imprimir(raiz, lista, favl_res);
		
	}


	fclose(favl);
	fclose(favl_res);

	return 0;
}


// Função inserir

void inserir(struct No **raiz, struct No * novo)
{
	if ((*raiz)!= NULL)
	{
		if ((*raiz)->numero > novo->numero)
		{
			inserir(&((*raiz)->fe), novo);
		}
		if ((*raiz)->numero < novo->numero)
		{
			inserir(&((*raiz)->fd), novo);
		}
	}else{
		(*raiz) = novo;
	}
}

// Função altura

int altura(struct No *raiz)
{

	if (raiz != NULL)
	{
		int altura_esq = altura(raiz->fe);
		int altura_dir = altura(raiz->fd);
		raiz->fb = altura_esq - altura_dir;

		if (altura_esq > altura_dir)
		{
			return 1 + altura_esq;

		}else{

				return 1 + altura_dir;
		}

		}else{

			return 0;
		}
}

// Rotação à direita

void rotacao_direita(struct No **raiz)
{
	struct No *aux;
	struct No *tmp;

	aux = (*raiz)->fe;
	tmp = aux->fd;
	aux->fd = (*raiz);
	(*raiz)->fe = tmp;
	(*raiz) = aux;
}

// Rotação à esquerda

void rotacao_esquerda(struct No **raiz)
{
	struct No *aux;
	struct No *tmp;

	aux = (*raiz)->fd;
	tmp = aux->fe;
	aux->fe = (*raiz);
	(*raiz)->fd = tmp;
	(*raiz) = aux;
}

// Rotação esquerda-direita

void rotacao_esq_dir(struct No *raiz)
{
	rotacao_esquerda(&(raiz->fe));
	rotacao_direita(&raiz);
}

// Rotação direita-esquerda

void rotacao_dir_esq(struct No *raiz)
{
	rotacao_direita(&(raiz->fd));
	rotacao_esquerda(&raiz);
}


// Balanceamento

void balancear(struct No *raiz)
{
	int tamanho_raiz, tamanho_raiz_fe, tamanho_raiz_fd;
	tamanho_raiz = altura(raiz);
	tamanho_raiz_fe = altura(raiz->fe);
	tamanho_raiz_fd = altura(raiz->fd);

	struct No * aux_fe = raiz->fe;
	struct No * aux_fd = raiz->fd;


	if (raiz->fb == 2)
	{
		if ((aux_fe->fb) == 1)
		{
			rotacao_direita(&raiz);
		}
		if ((aux_fe->fb) == -1)
		{
			rotacao_esq_dir(raiz);
		}
	}

	if (raiz->fb == -2)
	{
		if ((aux_fd->fb) == -1)
		{
			rotacao_esquerda(&raiz);
		}
		if ((aux_fd->fb) == 1)
		{
			rotacao_dir_esq(raiz);
		}
	}
}

// Função para enfileirar

void enfileirar(struct Nof **fila, struct No *no)
{

	if ((*fila) == NULL)
	{
		(*fila) = (struct Nof *) malloc (sizeof(struct Nof));
		(*fila)->no_arvore = no;
		(*fila)->prox = NULL;
		return;	
	}

	enfileirar(&((*fila)->prox), no);
}


// Função para desenfileirar

struct No * desenfileirar(struct Nof **fila)
{
	struct Nof *cabeca = (*fila);
	(*fila) = (*fila)->prox;

	struct No *resultado = cabeca->no_arvore;
	free(cabeca);
	return resultado;
}

// Função imprimir

void imprimir(struct No *raiz, struct Nof *fila, FILE * favl_res)
{
	if (raiz == NULL)
	{
	
		fprintf(favl_res, "X ");
		printf("X \n");
		printf("Acabou\n");
		if (fila == NULL)
		{
			printf("Lista vazia!\n");
			fprintf(favl_res, "\n");
		}
		return;
	
	}

	fprintf(favl_res, "%d ", raiz->numero);
	printf("%d \n", raiz->numero);
	enfileirar(&fila, raiz->fe);
	enfileirar(&fila, raiz->fd);


	while(fila)
	{
		printf("Ainda tem\n");
		struct No * saida = desenfileirar(&fila);
		imprimir(saida, fila, favl_res);
	}
}