/***************************************************************************************************************

UPE - CARUARU - LP1


Arquivo TXT para teste:

I rhuan rins recife 26558965425 13012017 56 59
I jaco figado jupi 58965256987 14012017 45 68
I lucas coracao caruaru 58965256987 15012017 45 68
I lucas rins caruaru 58965256987 15012017 45 68
I paulo medula recife 58965256987 16012017 45 68
I jeremias pancreas jupi 58965256987 17012017 45 68
I alfredo cornea arcoverde 58965256987 18012017 45 68
I matheus coracao caruaru 58965256987 19012017 45 68
I romulo rins recife 58965256987 20012017 45 68
I maria rins arcoverde 58965256987 21012017 45 68
I lilian medula bezerros 58965256987 22012017 45 68
I jessica rins arcoverde 58965256987 23012017 45 68
I ester cornea bezerros 58965256987 24012017 45 68
I lucia rins jupi 58965256987 25012017 45 68
I flavia figado bezerros 58965256987 26012017 45 68
D romildo rins caruaru 15455865224 12012017 52 56
D juvani coracao arcoverde 15455865224 12012017 52 56
D lucia medula recife 15455865224 12012017 52 56
D izaias rins jupi 15455865224 12012017 52 56
D lilian coracao caruaru 15455865224 12012017 52 56
D rhuan rins recife 26558965425 13012017 56 59


***************************************************************************************************************/

// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarando a estrutura

	struct No_fila
	{
		char nome[15];
		char orgao[15];
		char cidade[15];
		char cpf[15];
		char data[15];
		int lat, longi;
		struct No_fila *prox;
	};

	// Tabela de tabelas hash

	struct hash_cidade
	{
		int qtd, tam_tabela;
		struct hash_orgao **tabela_de_tabela;
	};

	// Tabelas de lista de orgão

	struct hash_orgao
	{
		int qtd, tam_tabela;
		struct No_fila **lista_orgaos;
	};


//Protótipos

int chave_hash_cidade(char cidade[15]);
int chave_hash_orgao(char orgao[15]);
struct hash_cidade * criar_t_hash_cidades(int quant_cidade);
struct hash_orgao * criar_t_hash_orgaos(int quant_orgao);
void cadastrar_na_tabela(struct hash_cidade * t_hash_cidade, struct No_fila * nnovo);
void cadastrar_na_lista_de_orgaos(struct hash_orgao * t_hash, struct No_fila * nnovo);
struct No_fila * cria_no_lista(int nlat, int nlongi, char nnome[15], char norgao[15], char ncidade[15], char ncpf[15], char ndata[15]);
void inserir_na_lista(struct No_fila * fila, struct No_fila * novo);
struct No_fila * busca(struct hash_cidade * t_hash, struct No_fila * ndoador);
struct No_fila * buscar_na_lista(struct hash_orgao * t_hash, struct No_fila * ndoador);


// Função principal (main)

int main(int argc, char const *argv[])
{
	char op;
	int lat; 
	int longi;
	char nome[15];
	char orgao[15];
	char cidade[15];
	char cpf[15];
	char data[15];	
	struct No_fila * saiu;
	struct No_fila * fila; // Cabeça da fila!
	fila = malloc(sizeof(struct No_fila));
	fila->prox = NULL;

	int quant_cidade = 5;
	int quant_orgao = 6;
	
	struct hash_cidade * t_hash_cidade; //Cabeça da tabela hash de tabela (tabela de cidades)!

	struct hash_orgao * t_hash_orgaos_caruaru;
	struct hash_orgao * t_hash_orgaos_recife;
	struct hash_orgao * t_hash_orgaos_jupi;
	struct hash_orgao * t_hash_orgaos_bezerros;
	struct hash_orgao * t_hash_orgaos_arcoverde;



	// Criando as tabelas hash

	t_hash_cidade = criar_t_hash_cidades(quant_cidade);
	
	t_hash_orgaos_caruaru = criar_t_hash_orgaos(quant_orgao);
	t_hash_orgaos_recife = criar_t_hash_orgaos(quant_orgao);
	t_hash_orgaos_jupi = criar_t_hash_orgaos(quant_orgao);
	t_hash_orgaos_bezerros = criar_t_hash_orgaos(quant_orgao);
	t_hash_orgaos_arcoverde = criar_t_hash_orgaos(quant_orgao);

	// Preenchendo a tabela de cidades com as cidades

	t_hash_cidade->tabela_de_tabela[0] = t_hash_orgaos_caruaru;
	t_hash_cidade->tabela_de_tabela[1] = t_hash_orgaos_recife;
	t_hash_cidade->tabela_de_tabela[2] = t_hash_orgaos_jupi;
	t_hash_cidade->tabela_de_tabela[3] = t_hash_orgaos_bezerros;
	t_hash_cidade->tabela_de_tabela[4] = t_hash_orgaos_arcoverde;





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

	/* LEGENDA! (I) = inserir "enfileirar", (D) = Desenfileirar e (P) imprimir. */

		while(fscanf(ffila, "%c", &op) != EOF)
		{

			if (op == 'I')
			{

				fscanf(ffila, " %s ", nome);
				fscanf(ffila, "%s ", orgao);
				fscanf(ffila, "%s ", cidade);
				fscanf(ffila, "%s ", cpf);
				fscanf(ffila, "%s ", data);
				fscanf(ffila, "%d ", &lat);
				fscanf(ffila, "%d ", &longi);

				struct No_fila * nnovo;
				nnovo = cria_no_lista(lat, longi, nome, orgao, cidade, cpf, data);
				cadastrar_na_tabela(t_hash_cidade, nnovo);

			}

			if (op == 'D')
			{

				fscanf(ffila, " %s ", nome);
				fscanf(ffila, "%s ", orgao);
				fscanf(ffila, "%s ", cidade);
				fscanf(ffila, "%s ", cpf);
				fscanf(ffila, "%s ", data);
				fscanf(ffila, "%d ", &lat);
				fscanf(ffila, "%d ", &longi);
				
				struct No_fila * ndoador;
				struct No_fila * nreceptor;

				ndoador = cria_no_lista(lat, longi, nome, orgao, cidade, cpf, data);
				nreceptor = busca(t_hash_cidade, ndoador);

				if (nreceptor == NULL)
				{
					fprintf(fila_res, "Não existem receptores disponíveis em %s!\n", ndoador->cidade);
				}

				if (nreceptor != NULL)
				{

					fprintf(fila_res, "O senhor(senhora) %s recebera um(a) %s do(a) doador(a) %s! \n", nreceptor->nome, nreceptor->orgao, ndoador->nome);
				
				}

			}

		}


	fclose(ffila);
	fclose(fila_res);

	return 0;

}

// Função cria nó de lista

struct No_fila * cria_no_lista(int nlat, int nlongi, char nnome[15], char norgao[15], char ncidade[15], char ncpf[15], char ndata[15])
{
		int i;
		struct No_fila * novo;
		novo = malloc(sizeof(struct No_fila));

		for(i = 0; i < strlen(nnome) ; ++i)
		{
			novo->nome[i] = nnome[i];
		}

		novo->nome[i] = '\0';

		for(i = 0; i < strlen(norgao) ; ++i)
		{
			novo->orgao[i] = norgao[i];
		}

		novo->orgao[i] = '\0';

		for(i = 0; i < strlen(ncidade) ; ++i)
		{
			novo->cidade[i] = ncidade[i];
		}

		novo->cidade[i] = '\0';

		for(i = 0; i < strlen(ncpf) ; ++i)
		{
			novo->cpf[i] = ncpf[i];
		}

		novo->cpf[i] = '\0';

		for(i = 0; i < strlen(ndata) ; ++i)
		{
			novo->data[i] = ndata[i];
		}

		novo->data[i] = '\0';

		novo->lat = nlat;
		novo->longi = nlongi;
		novo->prox = NULL;

		return novo;

}

// Função que dado um novo doador busca por um recepitor

struct No_fila * busca(struct hash_cidade * t_hash, struct No_fila * ndoador)
{
	struct No_fila * receptor;

	int chave_cidade;
	chave_cidade = chave_hash_cidade(ndoador->cidade);

	receptor = buscar_na_lista(t_hash->tabela_de_tabela[chave_cidade], ndoador);

	return receptor;

}

struct No_fila * buscar_na_lista(struct hash_orgao * t_hash, struct No_fila * ndoador)
{
	struct No_fila * receptor;

	int chave_orgao;
	chave_orgao = chave_hash_orgao(ndoador->orgao);

	if (t_hash->lista_orgaos[chave_orgao] == NULL)
	{
		receptor = NULL;
		return receptor;
	}

	if (t_hash->lista_orgaos[chave_orgao] != NULL)
	{

		struct No_fila * aux;
		aux = t_hash->lista_orgaos[chave_orgao];

		t_hash->lista_orgaos[chave_orgao] = aux->prox;

		receptor = aux;

		return receptor;

	}

}




// Função que insere na lista 

void inserir_na_lista(struct No_fila * fila, struct No_fila * novo)
{

	if(fila->prox == NULL)
	{
		novo->prox = fila->prox;
		fila->prox = novo;

	}else{

		struct No_fila * ultimo = fila;

		while(ultimo->prox != NULL)
		{
			ultimo = ultimo->prox;
		}

		novo->prox = NULL;
		ultimo->prox = novo;

	}

}

// Função que calcula a chave da tabela hash apartir da cidade

int chave_hash_cidade(char cidade[15])
{

	if (strcmp(cidade, "caruaru") == 0)
	{
		return 0;
	}

	if (strcmp(cidade, "recife") == 0)
	{
		return 1;
	}

	if (strcmp(cidade, "jupi") == 0)
	{
		return 2;
	}

	if (strcmp(cidade, "bezerros") == 0)
	{
		return 3;
	}

	if (strcmp(cidade, "arcoverde") == 0)
	{
		return 4;
	}

	return -1; //caso não seja nenhuma dessas cidades...
}

// Função que gera chave para orgão 

int chave_hash_orgao(char orgao[15])
{
	if (strcmp(orgao, "rins") == 0)
	{
		return 0;
	}

	if (strcmp(orgao, "figado") == 0)
	{
		return 1;
	}

	if (strcmp(orgao, "cornea") == 0)
	{
		return 2;
	}

	if (strcmp(orgao, "coracao") == 0)
	{
		return 3;
	}

	if (strcmp(orgao, "pancreas") == 0)
	{
		return 4;
	}

	if (strcmp(orgao, "medula") == 0)
	{
		return 5;
	}

	return -1; //caso não seja nenhum desses orgaos

}


// Função que cria a tabela hash


struct hash_cidade * criar_t_hash_cidades(int quant_cidade)
{
	struct hash_cidade * nova_t_hash_cidade;
	nova_t_hash_cidade = (struct hash_cidade*) malloc(sizeof(struct hash_cidade));

	int i;

	nova_t_hash_cidade->tam_tabela = quant_cidade;
	nova_t_hash_cidade->tabela_de_tabela = (struct hash_orgao**) malloc(quant_cidade * sizeof(struct hash_orgao*));
	

	nova_t_hash_cidade->qtd = 0;

	for (i = 0; i < quant_cidade; ++i)
	{
		nova_t_hash_cidade->tabela_de_tabela[i] = NULL;
	}

	return nova_t_hash_cidade;

}

// Função que cria a tabela hash


struct hash_orgao * criar_t_hash_orgaos(int quant_orgao)
{
	struct hash_orgao * nova_t_hash_orgaos;
	nova_t_hash_orgaos = (struct hash_orgao*) malloc(sizeof(struct hash_orgao));

	int i;

	nova_t_hash_orgaos->tam_tabela = quant_orgao;
	nova_t_hash_orgaos->lista_orgaos = (struct No_fila**) malloc(quant_orgao * sizeof(struct No_fila*));
	

	nova_t_hash_orgaos->qtd = 0;


	for (i = 0; i < quant_orgao; ++i)
	{
		nova_t_hash_orgaos->lista_orgaos[i] = NULL;
	}

	return nova_t_hash_orgaos;

}




// Função que cadastra os receptores na tabela, ou seja, copia a fila para a tabela

void cadastrar_na_tabela(struct hash_cidade * t_hash_cidade, struct No_fila * nnovo)
{
	int chave_cidade;
	chave_cidade = chave_hash_cidade(nnovo->cidade);

	cadastrar_na_lista_de_orgaos(t_hash_cidade->tabela_de_tabela[chave_cidade], nnovo);

}

void cadastrar_na_lista_de_orgaos(struct hash_orgao * t_hash, struct No_fila * nnovo)
{
	int chave_orgao;
	chave_orgao = chave_hash_orgao(nnovo->orgao);

	if (t_hash->lista_orgaos[chave_orgao] != NULL)
	{
		inserir_na_lista(t_hash->lista_orgaos[chave_orgao], nnovo);
	}

	if (t_hash->lista_orgaos[chave_orgao] == NULL)
	{
		t_hash->lista_orgaos[chave_orgao] = nnovo;
	}

}