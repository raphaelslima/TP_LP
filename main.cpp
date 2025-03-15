#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

void calculosMatriz(int tamanho, int qtdThradsAtual){
    /*
    Inicializa a função para gerar números aleatórios, a time(0) retorna um núemro em segundos desde 1 de jan de 1970 
    e a srand() gera uma sequência de números aleatórios , como o parâmetro sempre mudará graças ao time(0) a sequência sempre 
    será diferente em cada execução.
    */
   srand(time(0)); 

   // Aloca matriz de tamanho 10 usando ponteiros
   int* matriz = new int[tamanho]; 

   // Preenche as matrizes com números aleatórios entre 0 e 255
   for (int i = 0; i < tamanho; i++) {
       *(matriz + i) = rand() % 256;
   }

   // Exibe os valores armazenados na matriz
   cout << "Matriz original de tamanho " << tamanho << ":" << endl;
   for (int i = 0; i < tamanho; i++) {
       cout << *(matriz + i) << " ";
   }
   cout << endl;

   // Criar uma nova matriz para armazenar os novos valores após a operação.
   int* nova_matriz = new int[tamanho];

   // Inicia a contagem de tempo
   double inicio = omp_get_wtime(); 

    // inicia a programacao em paralelo
    omp_set_num_threads(qtdThradsAtual);

    #pragma omp parallel
{
    // retorna o número da thread
    int nThread = omp_get_thread_num(); 
    // retona a quantidade totais de threads
    int totalNumThreads = omp_get_num_threads();
    // Inicio da matriz
    int inicio = (tamanho / totalNumThreads) * nThread;
    // Fim da matriz
    int fim = (nThread == totalNumThreads - 1) ? tamanho : (tamanho / totalNumThreads) * (nThread + 1);

    /* Substituir os elementos pela média dos vizinhos, se for a primeira posição pega o próprio valor e o vizinho a dirita, 
   se for a primeira posição pega o próprio valor e o vizinho a esquerda 
   e se for um elemento que não está nas extremidades pega o vizinho da esquerda e o da direita.
   */
  #pragma omp for
    for (int i = inicio; i < fim; i++) {
        if (i == 0)
            *(nova_matriz + i) = (*(matriz + i) + *(matriz + i + 1)) / 2;
        else if (i == tamanho - 1)
            *(nova_matriz + i) = (*(matriz + i) + *(matriz + i - 1)) / 2;
        else
            *(nova_matriz + i) = (*(matriz + i - 1) + *(matriz + i + 1)) / 2;
    }
}

    // Finaliza a contagem de tempo
   double fim = omp_get_wtime(); 

   // Copia os valores da nova matriz para a matriz original
   for (int i = 0; i < tamanho; i++) {
       *(matriz + i) = *(nova_matriz + i);
   }

   // Exibe os valores após a substituição
   cout << "Matriz apos substituicao:" << endl;
   for (int i = 0; i < tamanho; i++) {
       cout << *(matriz + i) << " ";
   }
   cout << endl;

   // Tempo de execução da thread e da matriz
   cout << "Tempo de execucao com: " << qtdThradsAtual << " threads." << endl;
   cout << "Tempo de execução para tamanho " << tamanho << ": " << (fim - inicio) << " segundos." << endl;

   // Libera a memória alocada
   delete[] matriz; 
   delete[] nova_matriz;
}

int main() {

    // 2 threads
    calculosMatriz(10, 2); 
    calculosMatriz(50, 2); 
    calculosMatriz(100, 2);

    // 4 threads
    calculosMatriz(10, 4); 
    calculosMatriz(50, 4); 
    calculosMatriz(100, 4);

    // 8 threads
    calculosMatriz(10, 8); 
    calculosMatriz(50, 8); 
    calculosMatriz(100, 8);

    return 0;
}