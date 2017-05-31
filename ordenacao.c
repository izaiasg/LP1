/*********************************************************************

Primeira atividade

1) OK!

- Pesquisar e entender como funciona o Quick Sort. OK!

- Qual o pior caso? 

	R - No pior caso, é Quicksort ser de ordem Ο(n²).

- Qual o melhor caso?

	R - No pior caso, é Quicksort ser de ordem Ο(n log(n)).


2) OK! 

- Implemetar o Merge Sort que receberá um arquivo TXT e retornará outro.



			----------- ATEÇÃO ----------- 

			** Passe os diretórios dos dois arquivos,
			o primeiro contendo os números a serem 
			ordenados e o segundo o arquivo resposta ** 



Exemplo: 

\\ Entrada

|3 = R       \\ Número de Repetições, ou seja, quantidade de arrays a serem ordenados;
|4 = n       \\ Número de elementos a serem ordenados;
|4 3 2 1     \\ O array propriamente dito;
|5 = n       \\ Número de elementos a serem ordenados;
|10 15 7 0 1 \\ O array propriamente dito;
|2 = n       \\ Número de elementos a serem ordenados;
|3 1         \\ O array propriamente dito;


\\ Saida

|3 = R       \\ Número de Repetições, ou seja, quantidade de arrays a serem ordenados;
|4 = n       \\ Número de elementos a serem ordenados;
|1 2 3 4     \\ O array propriamente dito;
|5 = n       \\ Número de elementos a serem ordenados;
|0 1 7 10 15 \\ O array Ordenado;
|2 = n       \\ Número de elementos a serem ordenados;
|1 3         \\ O array Ordenado;


Segue o código...

*********************************************************************/

// Bibliotecas

#include <stdio.h>
#include <stdlib.h>

// Protótipos

void merge_sort(int numeros[], int primeiro, int ultimo);
void compara(int numeros[], int primeiro, int ultimo, int central);


// Função principal (main)

int main(int argc, char const *argv[])
{

// Abre o aquivo atravez do diretorio que foi passado por linha de comando

	FILE * ordenar = fopen(argv[1], "r");

	// Verifica se esta tudo OK com o arquivo
		
		if (ordenar == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

	int repeticoes, i, j, k, *num_elementos, **numeros;
	

	fscanf(ordenar, "%d",&repeticoes);


// Vetor contendo o numero de repetições

	num_elementos = (int*) malloc(repeticoes * sizeof(int));

	numeros = (int**) malloc(repeticoes * sizeof(int));




// for() que lê o numero de elementos e preenche o vetor numeros


	for (i = 0; i < repeticoes; ++i)
	{
		
		fscanf(ordenar, "%d",&num_elementos[i]);


		numeros[i] = (int*) malloc(num_elementos[i] * sizeof(int));
		


		for (j = 0; j < num_elementos[i]; ++j)
		{
			fscanf(ordenar, "%d ", &numeros[i][j]);
		}

	}


	fclose(ordenar);


// chamando o Merge Sort

	for (i = 0; i < repeticoes; ++i)
	{
		
		merge_sort(numeros[i], 0, num_elementos[i] - 1);

	}


// Abrir o arquivo resposta e colocar as respectivas respostas


	FILE * resposta = fopen(argv[2], "w");

		// Verifica se esta tudo OK com o arquivo
		
		if (resposta == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

// escrevendo no arquivo resposta

	fprintf(resposta, "%d\n", repeticoes);

	for (i = 0; i < repeticoes; ++i)
	{

		fprintf(resposta, "%d\n", num_elementos[i]);

		for (j = 0; j < num_elementos[i]; ++j)
		{
			
			fprintf(resposta, "%d ", numeros[i][j]);

		}

		fprintf(resposta, "\n");

	}

	fclose(resposta);

	return 0;
}

// Função Merge Sort

void merge_sort(int numeros[], int primeiro, int ultimo)
{

	int central;

	if(primeiro < ultimo)
	{
		central = (primeiro + ultimo) / 2;
		merge_sort(numeros, primeiro, central);
		merge_sort(numeros, central + 1, ultimo);
		compara(numeros, primeiro, ultimo, central);
	}

}


// Função compara

void compara(int numeros[], int primeiro, int ultimo, int central)
{

	int poslivre, inicio_vetor1, inicio_vetor2, i;
	int auxiliar[10];
	inicio_vetor1 = primeiro;
	inicio_vetor2 = central + 1;
	poslivre = primeiro;

	while(inicio_vetor1 <= central && inicio_vetor2 <= ultimo)
	{
		if (numeros[inicio_vetor1] <= numeros[inicio_vetor2])
		{
			auxiliar[poslivre] = numeros[inicio_vetor1];
			++inicio_vetor1;
		}
		else
		{
			auxiliar[poslivre] = numeros[inicio_vetor2];
			++inicio_vetor2;
		}
		++poslivre;
	}

/* Caso ainda exista numeros no primeiro vetor que não foram passados para o auxiliar */

	for (i = inicio_vetor1; i <= central; ++i)
	{
		auxiliar[poslivre] = numeros[i];
		++poslivre;
	}
/* Caso ainda exista numeros no segundo vetor que não foram passados para o auxiliar */

	for(i = inicio_vetor2; i <= ultimo; ++i)
	{
		auxiliar[poslivre] = numeros[i];
		++poslivre;
	}

// Retornando os valores para o vetor principal

	for(i = primeiro; i <= ultimo; ++i)
	{
		numeros[i] = auxiliar[i];
	}

}