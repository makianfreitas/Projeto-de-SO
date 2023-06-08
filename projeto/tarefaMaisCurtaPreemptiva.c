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
	int tamJobs, idProcesso, totJaProcessado, faltaProcessar;
	int statusProc, TemE_S, instantes_E_S[50], prioridade, tempoChegadaNaFila, instanteChegadaNaFila; //1 ou mais instantes de E/S 
	//através do instanteChegadaNaFila pode-se calcular o tempo de ociosidade e de aproveitamento da CPU, interfere na montagem da fila de prioridade, etc
}processo;

/*typedef struct{
	int indice, 
}*/

void criaProcessos(processo *vetProc, int *vetTempoChegada);
void imprimeProcessosCriados(processo *vetProc);
void ESCALONADOR(processo *vetProc);
void CPU(processo *vetProc, int qualProcess);
void FILA_DE_PROCESSOS(processo *vetProc, int qualProcess);
void function(processo *vetProc, int *fila);

int i, j, k, totProcesso, umQuantumDeCPU, tamTotalMemoria; //tamTotalMemoria: pode determinar se um novo processo pode ou não ser criado/ir para a fila
//umQuantumDeCPU pode punir a eficiência com as trocas e restauração de contexto.
int main() {
	int c;
	system("cls");
	printf("Digite o numero de processos: ");
	scanf("%d",&totProcesso);
	
	/*
	printf("Determine o tamanho do Quantum: ");
	scanf("%d",&umQuantumDeCPU); //O quantum pode ser por processo e não fixo na CPU, pode ser particionado por usuário, etc
									//pode-se associar um peso ao quantum relacionado a troca de contexto
	*/

	processo vetProc[totProcesso];
	int fila[totProcesso];
	int vetTempoChegada[totProcesso];
	for(i=0; i < totProcesso; i++){
		fila[i] = -1;
	}
	
	criaProcessos(vetProc, vetTempoChegada);
	imprimeProcessosCriados(vetProc);
	function(vetProc, fila);
	//nesse ponto, pode-se pensar num estado inicial para a fila antes de chamar o escalonador       		
	//ESCALONADOR(vetProc); //chamar o escalonador 
	printf("\n\n");
	system("pause");
	return 0;
}

void criaProcessos(processo *vetProc, int *vetTempoChegada) {
	int cont, indiceHash;
	srand(time(NULL));
	//SITUAÇÃO 1
	/*vetProc[0].tamJobs = 8;
	vetProc[0].tempoChegadaNaFila = 1;
	vetProc[1].tamJobs = 8;
	vetProc[1].tempoChegadaNaFila = 4;
	vetProc[2].tamJobs = 10;
	vetProc[2].tempoChegadaNaFila = 2;*/

	//SITUAÇÃO 2
	/*vetProc[0].tamJobs = 9;
	vetProc[0].tempoChegadaNaFila = 2;
	vetProc[1].tamJobs = 5;
	vetProc[1].tempoChegadaNaFila = 1;
	vetProc[2].tamJobs = 9;
	vetProc[2].tempoChegadaNaFila = 0;*/

	//SITUAÇÃO 3
	/*vetProc[0].tamJobs = 5;
	vetProc[0].tempoChegadaNaFila = 16;
	vetProc[1].tamJobs = 7;
	vetProc[1].tempoChegadaNaFila = 0;
	vetProc[2].tamJobs = 5;
	vetProc[2].tempoChegadaNaFila = 19;
	vetProc[3].tamJobs = 5;
	vetProc[3].tempoChegadaNaFila = 3;
	vetProc[4].tamJobs = 4;
	vetProc[4].tempoChegadaNaFila = 5;
	vetProc[5].tamJobs = 4;
	vetProc[5].tempoChegadaNaFila = 12;
	vetProc[6].tamJobs = 6;
	vetProc[6].tempoChegadaNaFila = 16;
	vetProc[7].tamJobs = 8;
	vetProc[7].tempoChegadaNaFila = 15;
	vetProc[8].tamJobs = 9;
	vetProc[8].tempoChegadaNaFila = 2;
	vetProc[9].tamJobs = 7;
	vetProc[9].tempoChegadaNaFila = 14;*/
    for (cont = 0; cont < totProcesso; cont++) {
		vetProc[cont].tamJobs = 4 + rand() % 16; //tamanho do job do processo é gerado aleatoriamente
		vetProc[cont].tempoChegadaNaFila = rand() % 15; //tempo de chegada é gerado aleatoriamente
		vetProc[cont].idProcesso = 65 + cont;
		vetProc[cont].faltaProcessar = vetProc[cont].tamJobs;
		vetProc[cont].totJaProcessado = 0;
		
		/*
		//Implementação da pesquisa hash
		indiceHash = vetProc[cont].tempoChegadaNaFila % totProcess;
		if(vetTempoChegada[indiceHash] == -1){
			vetTempoChegada[indiceHash] = cont;
		} else {
			i = (indiceHash + 1) % totProcess;
			do{
				if(vetTempoChegada[i] == -1){
					vetTempoChegada[indiceHash] = cont;
				}
				i = (indiceHash + 1) % totProcess;
			} while(i != indiceHash);
		}*/

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


//ESCALONADOR
   //chamar a CPU
       //ao sair da CPU reorganiza ESSE processo na fila   
//pode-se implementar estratégias para pegar de diferentes filas, eventos que cause a saída de bloqueado para para prontos, entre outras...
//pode-se implementar mecanismo que coloque novos processos na fila (um novo processo), etc   
void ESCALONADOR(processo *vetProcProntos){
	int processEleito;
	while (totProcesso > 0){
		processEleito = 0; //pode-se implementar algum método de seleção do processo de acordo com a característica
		CPU(vetProcProntos, processEleito); //envia o próximo processo para a CPU
		printf("|");	
	}
	
}

//CPU
  //executar o processo ate acabar o quantum ou abortar se houver uma interrupção (estratégia)
void CPU(processo *vetProcEmExecucao, int qualProcess){
	int totDoQuantum;
	for(totDoQuantum = 0; totDoQuantum < umQuantumDeCPU && vetProcEmExecucao[qualProcess].totJaProcessado < vetProcEmExecucao[qualProcess].tamJobs; totDoQuantum++) {
		printf("%c", vetProcEmExecucao[qualProcess].idProcesso);
		vetProcEmExecucao[qualProcess].totJaProcessado++;
		//pode-se pensar em estratégias de interrupção (I/O) nesse ponto
		//nesse caso, com mecanismo para gerenciar a fila de bloqueados e eventos (aleatório, por exemplo)
		//que faça o processo em algum momento voltar para a fila de prontos
	}
	
	//para onde vai o processo após sair da CPU? se terminou, sai da fila, senão vai para o final, para fila de bloqueados, etc
	FILA_DE_PROCESSOS(vetProcEmExecucao, qualProcess);	
}


//REARRANJA FILA DE PROCESSOS
   //organizar a(s) fila(s) de acordo com estratégia/algoritmo
//ESTRATÉGIAS: mais de uma fila, fila por características, etc
void FILA_DE_PROCESSOS(processo *vetProcProntos, int qualProcess){
	int cont;
	processo saiuDaCPU;
	saiuDaCPU = vetProcProntos[qualProcess];
	
	//acabou todo o processo, retira da fila de pendentes
	if(vetProcProntos[qualProcess].totJaProcessado == vetProcProntos[qualProcess].tamJobs){
		for(cont = qualProcess; cont < totProcesso-1; cont++){
			vetProcProntos[cont] = vetProcProntos[cont+1];
		}
		totProcesso--; //faz a fila diminuir até zerar (chegar em 1)
	}else{//vai para o final da fila (quando mais de uma fila, deve-se implementar para qual fila de acordo com a circustancia)
		
		for(cont = qualProcess; cont < totProcesso-1; cont++){
			vetProcProntos[cont] = vetProcProntos[cont+1];
		}
		vetProcProntos[cont] = saiuDaCPU;
	}
}

void function(processo *vetProc, int *fila){
	bool temProcesso;
	int execultando=-1, tamFila=-1; //tamFila armazena as posições dos processos
	system("cls");
	system("cls");
	printf("\t|  Tempo do Processador\t |  Processo em execulcao  |\n");
	/*FOR 1*/for(i=0; totProcesso > 0; i++){
		//printf("\nEntrou no FOR 1\n");
		/*FOR 2*/for(j=0; j < totProcesso; j++){
			//printf("\nEntrou no FOR 2\n");
			/*IF 1*/if(vetProc[j].tempoChegadaNaFila == i){ //Verifica se chegou processo no tempo atual
				//printf("\nEntrou no IF 1\n");
				tamFila++; //"Aumenta" o tamanho da fila
				fila[tamFila] = j; //Adiciona a posição do processo na fila
			}
		}
		
		/*IF 2*/if(tamFila > -1){
			//printf("\nEntrou no IF 2\n");
			execultando = fila[0];
			//printf("\nExecultando1: %d\n", execultando);
			/*FOR 3*/for(j=1; j <= tamFila; j++){ //Verifica qual é o processo com a menor tarefa
				/*printf("\nEntrou no FOR 3\n");
				printf("\nfila[j]: %d", fila[j]);
				printf("\nvetProc[fila[j]].faltaProcessar: %d\n", vetProc[fila[j]].faltaProcessar);
				printf("\nexecultando: %d", execultando);
				printf("\nvetProc[execultando].faltaProcessar: %d\n", vetProc[execultando].faltaProcessar);*/
				/*IF 3*/if(vetProc[fila[j]].faltaProcessar < vetProc[execultando].faltaProcessar){
					//printf("\nEntrou no IF 3\n");
					execultando = fila[j]; //execultando recebe a posição do processo com a menor tarefa
				}
			}
			//printf("\nExecultando2: %d\n", execultando);
			//printf("vetProc[execultando].faltaProcessar: %d", vetProc[execultando].faltaProcessar);
			printf("\t----------------------------------------------------\n");
			printf("\t|\t\t  %d\t |\t%c\t\t   |\n", i, vetProc[execultando].idProcesso);
			vetProc[execultando].faltaProcessar--;

			/*IF 4*/if(vetProc[execultando].faltaProcessar == 0){
				//printf("\nEntrou no IF 4\n");
				/*FOR 5*/for(j=0; j <= tamFila; j++){ //"Tira" o processo da fila
					//printf("\nEntrou no FOR 5\n");
					/*IF 5*/if(fila[j] == execultando){ //Verifica se essa posição é o processo que será "apagado" da fila
						//printf("\nEntrou no IF 5\n");
						/*FOR 6*/for(k=j; k <= tamFila-1; k++){
							//printf("\nEntrou no FOR 6\n");
							fila[k] = fila[k+1];
						}
						fila[k] = -1;
						break;
					}
				}
				/*FOR 4*/for(j=execultando; j < totProcesso-1; j++){ //"Tira" o processo do vetor
					//printf("\nEntrou no FOR 4\n");
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
		} /*ELSE DO IF 2*/else {
			//printf("\nEntrou no ELSE DO IF 2\n");
			printf("\t----------------------------------------------------\n");
			printf("\t|\t\t  %d\t |\t\t\t   |\n", i);
		}

		if(i == 1000){
			system("pause");
		}
		
		/*if(vetProc[i].tempoChegadaNaFila == i){
			if()
			fila[cont] = vetProc[i].idProcesso;
			cont++;
			printf("   %d |    %c\n", i, vetProc[i].idProcesso);
		} else {
			printf("   %d |\n", i);
		}*/
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