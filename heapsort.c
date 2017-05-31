/***************************************************************************************************************

UPE - CARUARU - LP1
IZAIAS GONÇALVES


	Implementação do HeapSort (min Heap)

\\ Entrada

	|1 = R       \\ Número de Repetições;
	|2 = T       \\ Quantidade de menores números;
	|4 = n       \\ Número de elementos a serem ordenados;
	|4 3 2 1     \\ O array propriamente dito;	 

\\ Saída

	|1 = R       \\ Número de Repetições;
	|2 = T       \\ Quantidade de menores números;
	|1 2         \\ O 2 (T) menores números;




***************************************************************************************************************/

// Bibliotecas 

#include <stdio.h>
#include <stdlib.h>

//Protótipos

void criaHeap(int *numeros, int i, int final);
void heapSort(int *numeros, int tamanho);

// Função principal (main)

int main(int argc, char const *argv[])
{

	// Abre os aquivos atravez do diretorio que foi passado por linha de comando 

	FILE * fheaps = fopen(argv[1], "r");
	FILE * fheaps_res = fopen(argv[2], "w");

	// Verifica se esta tudo OK com os arquivos
		
		if (fheaps == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

		if (fheaps_res == NULL)
		{
			printf("Erro ao abrir o arquivo!\n");
			return 1;
		}

	int repeticoes, i, j, k, num_meneres, num_elementos;
	int *numeros;

	// Pegando o número de repetições
	
	fscanf(fheaps, "%d \n",&repeticoes);

	fprintf(fheaps_res, "%d\n", repeticoes);

	printf("R = %d\n", repeticoes);

	// Laço que vai percorrer todo o arquivo

	for (i = 0; i < repeticoes; ++i)
	{
		fscanf(fheaps, "%d \n",&num_meneres);
		printf("T = %d\n", num_meneres);
		fscanf(fheaps, "%d \n",&num_elementos);
		printf("N = %d\n", num_elementos);

		numeros = (int*) malloc(num_elementos * sizeof(int));

		for (j = 0; j < num_elementos; ++j)
		{
			fscanf(fheaps, "%d ", &numeros[j]);
			printf("%d ", numeros[j]);
		}

		printf("\n");

		// chamar a função heapsort();
		// passando o array "ponteiro" (numeros), o tamanho (num_elementos) 
		// e o número de menores números (num_meneres)

		heapSort(numeros, num_elementos);

		// escrevendo no arquivo resposta

		int ultimo = (num_elementos - 1);
	
		fprintf(fheaps_res, "%d\n", num_meneres);

		for (j = 0; j < num_meneres; ++j)
		{
			fprintf(fheaps_res, "%d ", numeros[ultimo--]);
		}

		fprintf(fheaps_res, "\n");

	}

	fclose(fheaps);
	fclose(fheaps_res);

	return 0;
	
}

// Função HeapSort

void heapSort(int *numeros, int tamanho)
{
	int i, aux;
	
	// cria heap a partir dos dados

	for(i = (tamanho - 1)/2; i >= 0; --i)
	{
		criaHeap(numeros, i, tamanho - 1);
	}

	// Reconstruir heap

	for (i = (tamanho - 1); i >= 1; --i)
	{
		/*Pegar o maior elemento da heap
		e colocar na sua posição 
		correspondente no array
		*/
		
		aux = numeros[0];
		numeros[0] = numeros[i];
		numeros[i] = aux;

		// Construir heap

		criaHeap(numeros, 0, i - 1);
	}
}

// Função criar Heap

void criaHeap(int *numeros, int i, int final)
{
	int aux = numeros[i];
	int j = i * 2 + 1;

	while(j <= final)
	{
		if (j < final)
		{
			// Pai tem 2filhos?
			// Quem é o menor?

			if (numeros[j] > numeros[j + 1])
			{
				j = j +1;
			}
		}

		// Filho menor que o pai?
		// Filho se torna pai!
		// Repetir o processo

		if (aux > numeros[j])
		{
			numeros[i] = numeros[j];
			i = j;
			j = 2 * i + 1;
		}else{
			j = final + 1;
		}
	}

	//Antigo pai ocupa o lugar do
	// último filho analisado

	numeros [i] = aux;
}