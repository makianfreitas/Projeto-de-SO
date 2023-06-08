/*
    TAREFA MAIS CURTA PREEMPTIVA
    Integrantes:
        Gabriela Monteiro
        Hugo Gabriel
        Ian Rodrigo
        Igor Caian
        Makian Freitas
        Pablo
        Reginaldo
        Vítor Aniz
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct strcProcesso{
	int tamJobs;
	int idProcesso; 
	int faltaProcessar;
	int tempoChegadaNaFila;
}processo;

void criaProcessos(processo *vetProc, int *vetTempoChegada);
void imprimeProcessosCriados(processo *vetProc);
void function(processo *vetProc, int *fila);

int i, j, k;
int totProcesso;

int main(){
	system("cls");
	printf("Digite o numero de processos: ");
	scanf("%d",&totProcesso);

	processo vetProc[totProcesso];
	int fila[totProcesso];
	int vetTempoChegada[totProcesso];
	
	criaProcessos(vetProc, vetTempoChegada);
	imprimeProcessosCriados(vetProc);
	function(vetProc, fila);
	printf("\n\n");
	system("pause");
	return 0;
}

void criaProcessos(processo *vetProc, int *vetTempoChegada) {
	int cont;
	srand(time(NULL));
    for (cont = 0; cont < totProcesso; cont++) {
		vetProc[cont].tamJobs = 4 + rand() % 16; //tamanho do job do processo é gerado aleatoriamente
		vetProc[cont].tempoChegadaNaFila = rand() % 15; //tempo de chegada é gerado aleatoriamente
		vetProc[cont].idProcesso = 65 + cont;
		vetProc[cont].faltaProcessar = vetProc[cont].tamJobs;
    }
}


void imprimeProcessosCriados(processo *vetProc) {
	int cont;
	printf("\tID Processo | Tamanho do Job | Tempo de Chegada\n");
	for(cont = 0; cont < totProcesso; cont++){
		printf("\t   %c \t    |    %d \t     |    %d \n", vetProc[cont].idProcesso, vetProc[cont].tamJobs, vetProc[cont].tempoChegadaNaFila);
	}
	system("pause");
}

void function(processo *vetProc, int *fila){
	int execultando=-1;
	int tamFila=-1; //tamFila armazena as posições dos processos
	system("cls");
	printf("\t|  Tempo do Processador\t |  Processo em execulcao  |\n");
	for(i=0; totProcesso > 0; i++){
		for(j=0; j < totProcesso; j++){
			if(vetProc[j].tempoChegadaNaFila == i){ //Verifica se chegou processo no tempo atual
				tamFila++; //"Aumenta" o tamanho da fila
				fila[tamFila] = j; //Adiciona a posição do processo na fila
			}
		}
		
		if(tamFila > -1){
			execultando = fila[0];
			for(j=1; j <= tamFila; j++){ //Verifica qual é o processo com a menor tarefa
				if(vetProc[fila[j]].faltaProcessar < vetProc[execultando].faltaProcessar){
					execultando = fila[j]; //execultando recebe a posição do processo com a menor tarefa
				}
			}
			printf("\t----------------------------------------------------\n");
			printf("\t|\t\t  %d\t |\t%c\t\t   |\n", i, vetProc[execultando].idProcesso);
			vetProc[execultando].faltaProcessar--;

			if(vetProc[execultando].faltaProcessar == 0){
				for(j=0; j <= tamFila; j++){ //"Tira" o processo da fila
					if(fila[j] == execultando){ //Verifica se essa posição é o processo que será "apagado" da fila
						for(k=j; k <= tamFila-1; k++){
							fila[k] = fila[k+1];
						}
						break;
					}
				}
				for(j=execultando; j < totProcesso-1; j++){ //"Tira" o processo do vetor
					vetProc[j] = vetProc[j+1];
				}
				vetProc[j].idProcesso = 0;
				vetProc[j].faltaProcessar = 0;
				
				for(j=0; j <= tamFila-1; j++){
					if(fila[j] > execultando){
						fila[j]--;
					}
				}
				
				tamFila--;
				totProcesso--;
			}
		} else {
			printf("\t----------------------------------------------------\n");
			printf("\t|\t\t  %d\t |\t\t\t   |\n", i);
		}

		if(i == 1000){
			system("pause");
		}
	}
}

/* 
    O QUE SE PODE TER COMO RELATÓRIO:
   *ESTUDAR OS CONCEITOS PARA OBTER AS SEGUINTES MÉTRICAS:
  	- Tempo de utilização de CPU;
	- Índice de produtividade da CPU;
	- Tempo médio de espera;
	- Tempo médio de retorno;
	- Etc.
*/