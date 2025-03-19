#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;


void calculosMatriz(int tamanho, int qtdThradsAtual){
    /*
    Inicializa a função para gerar números aleatórios, a time(0) retorna um número em segundos desde 1 de jan de 1970 
    e a srand() gera uma sequência de números aleatórios , como o parâmetro sempre mudará devido ao time(0), a sequência 
    sempre será diferente em cada execução.
    */
    srand(time(0)); 



    // Aloca matriz de tamanho 10 (nxn) usando ponteiros
    int *matriz = (int *)malloc(tamanho * tamanho * sizeof(int));



    // Preenche as matrizes com números aleatórios entre 0 e 255
    /*for (int i = 0; i < tamanho; i++) {
        *(matriz + i) = rand() % 256;
    }*/
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            *(matriz + i * tamanho + j) = rand() % 256;  //tamanho = n (número de colunas)
        }
    }



    // Exibe os valores armazenados na matriz
    cout << "Matriz original de tamanho " << tamanho << ":" << endl;

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            cout << *(matriz + i * tamanho + j) << " ";  //tamanho = n (número de colunas)
        }
        cout << endl;
    }
    cout << endl;

    // Criar uma nova matriz para armazenar os novos valores após a operação.
    int *nova_matriz = (int *)malloc(tamanho * tamanho * sizeof(int));

    // Inicia a contagem de tempo
    double inicio = omp_get_wtime(); 

    // inicia a programacao em paralelo
    #pragma omp parallel for num_threads(qtdThradsAtual)
    {    
    

        // Retorna o número da thread atual
        int thread_id = omp_get_thread_num();

        /* divide a matriz de acordo com o número de threads, cada threads irá processar (tamanho da matriz/ n  de thears) linhas ou colunas já que a matriz é sempre quadrada tanto faz.
        */
        int linhas_por_thread = tamanho / qtdThradsAtual;

        // Calcula onde a thread atual começa na matriz
        int inicio = thread_id * linhas_por_thread;

        // Calcula onde a thread atual termina na matriz
        int fim = inicio + linhas_por_thread;

        // Percorre matriz
            for (int i = inicio; i < fim; i++) {
                for (int j = inicio; j < fim; j++) {
                    // soma os vizinhos
                    int soma = 0;
                    // conta os vizinhos
                    int count = 0;
                    
                    // Percorre os viznhos do elemento, -1 começa "átras dele".
                    /*
                        (-1,-1) (-1,0) (-1,1)
                        (0,-1)  (i,j)   (0,1)
                        (1,-1)  (1,0)   (1,1)
                    */
                    for (int vi = -1; vi <= 1; vi++) {
                        for (int vj = -1; vj <= 1; vj++) {

                            // calcula os indices dos vizinhos (i e j são coordenadas do elemento central da matriz)
                            // vi e vj percorre os vizinhos
                            // ni linha do vizinho e nj a coluna do vizinho
                            int ni = i + vi;
                            int nj = j + vj;
                            /*
                                - ni >= 0 && ni < fim && nj >= 0 && nj < fim usado em elementos nas bordas evita contar os viznhos que não existem nos elementos das bordas
                                - !(vi == 0 && vj == 0): Não conta o prório elemento
                            */
                            if (ni >= 0 && ni < fim && nj >= 0 && nj < fim && !(vi == 0 && vj == 0)) {
                                soma += *(matriz + ni * fim + nj);
                                count++;
                            }
                        }
                    }
                    *(nova_matriz + i * tamanho + j) = (soma / count);
                }
            }

    }

    // Finaliza a contagem de tempo
    double fim = omp_get_wtime(); 

    // Exibe os valores após a substituição
    cout << "Matriz apos substituicao:" << endl;

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            cout << *(nova_matriz + i * tamanho + j) << " ";  //tamanho = n (número de colunas)
        }
        cout << endl;
    }
    cout << endl;

    // Tempo de execução da thread e da matriz
    cout << "Tempo de execucao com: " << qtdThradsAtual << " threads." << endl;
    cout << "Tempo de execução para tamanho " << tamanho << "x" << tamanho << ": " << (fim - inicio) << " segundos." << endl;

    // Libera a memória alocada
    delete[] matriz; 
    delete[] nova_matriz;

}


int main() {

    // 1 threads
    calculosMatriz(10, 1); 
    calculosMatriz(50, 1); 
    calculosMatriz(100, 1);


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



