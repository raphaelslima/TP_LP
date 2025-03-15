#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void processarMatriz(int tamanho){
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

   /* Substituir os elementos pela média dos vizinhos, se for a primeira posição pega o próprio valor e o vizinho a dirita, 
   se for a primeira posição pega o próprio valor e o vizinho a esquerda 
   e se for um elemento que não está nas extremidades pega o vizinho da esquerda e o da direita.
   */
   for (int i = 0; i < tamanho; i++) {
       if (i == 0)
           *(nova_matriz + i) = (*(matriz + i) + *(matriz + i + 1)) / 2;
       else if (i == tamanho - 1)
           *(nova_matriz + i) = (*(matriz + i) + *(matriz + i - 1)) / 2;
       else
           *(nova_matriz + i) = (*(matriz + i - 1) + *(matriz + i + 1)) / 2;
   }

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

   // Libera a memória alocada
   delete[] matriz; 
   delete[] nova_matriz;
}

int main() {
    processarMatriz(10); 
    processarMatriz(50); 
    processarMatriz(100);  
    return 0;
}