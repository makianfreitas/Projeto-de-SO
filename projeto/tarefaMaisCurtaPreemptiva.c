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

typedef struct strcProcesso{
	int tamJobs; //Tamanho do processo
	int idProcesso; //Armazena um código int que será impresso como char (%c) para mostrar uma letra (A, B, C...)
	int faltaProcessar; //Quantidade que falta processar
	int tempoChegadaNaFila; //Tempo de chegada do processo
}processo;

void criaProcessos(processo *vetProc);
void imprimeProcessosCriados(processo *vetProc);
void function(processo *vetProc, int *fila);

int totProcesso; //Quantidade total de processos e tamanho lógico do vetor principal vetProcessos[]
/*
	totProcesso é a posição limite do vetor principal (vetProcessos[]), 
	ou seja, o vetor será lido até a posição tamFila. Se tiver alguma coisa 
	amazenada depois desta posição (no vetor vetProcessos[]), será 
	ignorado pois se trata de processo(s) finalizado(s)
*/

int main(){
	system("cls");
	printf("Digite o numero de processos: ");
	scanf("%d",&totProcesso);

	processo vetProcessos[totProcesso]; //Vetor (PRINCIPAL) do tipo processo que armazena as características de cada processo
	int fila[totProcesso]; //Armazena, por ordem de chegada, a posição de cada processo no vetor principal (vetProcessos[])
	
	criaProcessos(vetProcessos);
	imprimeProcessosCriados(vetProcessos);
	system("pause");
	function(vetProcessos, fila);
	printf("\t----------------------------------------------------\n\n");
	system("pause");
	return 0;
}

void criaProcessos(processo *vetProcessos) {
	int cont;
	srand(time(NULL));
    for (cont = 0; cont < totProcesso; cont++) {
		vetProcessos[cont].tamJobs = 4 + rand() % 16; //Tamanho do processo é gerado aleatoriamente (de 4 a 20)
		vetProcessos[cont].tempoChegadaNaFila = rand() % 15; //Tempo de chegada é gerado aleatoriamente (de 0 a 15)
		vetProcessos[cont].idProcesso = 65 + cont; //idProcesso recebe o código de cada letra baseado na tabela ASCII (exemplo: 65 = A e 90 = Z)
		vetProcessos[cont].faltaProcessar = vetProcessos[cont].tamJobs; //faltaProcessar recebe inicialmente o tamanho do processo (tamJobs)
    }
}


void imprimeProcessosCriados(processo *vetProcessos) {
	int cont;
	system("cls");
	system("cls");
	printf("\t----------------------------------------------------\n");
	printf("\t| ID Processo | Tamanho do Job | Tempo de Chegada  |\n");
	for(cont = 0; cont < totProcesso; cont++){
		printf("\t----------------------------------------------------\n");
		printf("\t|    %c \t      |    %d \t       |    %d \t\t   |\n", vetProcessos[cont].idProcesso, vetProcessos[cont].tamJobs, vetProcessos[cont].tempoChegadaNaFila);
	}
	printf("\t----------------------------------------------------\n\n");
}

void function(processo *vetProcessos, int *fila){
	int i, j; //Variáveis para os laços
	int tempo; //Tempo atual
	int execultando=-1; //Armazena a posição, no vetor principal (vetProcessos[]), do processo que está em execulção
	int tamFila=-1; //Tamanho lógico do vetor fila[]
	/*
		tamFila é a posição limite do vetor fila[], ou seja, 
		o vetor será lido até a posição tamFila. Se tiver alguma coisa 
		amazenada depois desta posição (no vetor fila[]), será 
		ignorado pois se trata de processo(s) finalizado(s)
	*/

	imprimeProcessosCriados(vetProcessos);
	
	
	//LEMBRAR DE ADICIONAR A TERCEIRA COLUNA (ignorem)
	
	
	printf("\n\t----------------------------------------------------\n");
	printf("\t|  Tempo do Processador\t |  Processo em Execulcao  |\n");
	for(tempo=0; totProcesso > 0; tempo++){ //Laço que representa o tempo

		for(i=0; i < totProcesso; i++){ //Laço que verifica se chegou processo no tempo atual
			if(vetProcessos[i].tempoChegadaNaFila == tempo){
				tamFila++; //"Aumenta" o tamanho da fila
				fila[tamFila] = i; //fila[] recebe a posição, no vetor principal (vetProcessos[]), do processo que chegou
			}
		}
		
		if(tamFila > -1){ //Verifica se existe processo para ser execultado
			execultando = fila[0];
			for(i=1; i <= tamFila; i++){ //Laço que verifica qual é o processo com o menor tamanho
				if(vetProcessos[fila[i]].faltaProcessar < vetProcessos[execultando].faltaProcessar){
					execultando = fila[i]; //execultando recebe a posição, no vetor principal (vetProcessos[]), do processo com o menor tamanho
				}
			}

			printf("\t----------------------------------------------------\n");
			printf("\t|\t\t  %d\t |\t%c\t\t   |\n", tempo, vetProcessos[execultando].idProcesso); //Execulta
			vetProcessos[execultando].faltaProcessar--;

			if(vetProcessos[execultando].faltaProcessar == 0){ //Verifica se o processo que acabou de ser execultado terminou
				for(i=0; i <= tamFila; i++){ //Laço que procura este processo no vetor fila[]
					if(fila[i] == execultando){ //Verifica se esta posição é o processo que será "apagado" do vetor fila[]
						for(j=i; j <= tamFila-1; j++){ //Laço que "apaga" o processo do vetor fila[]
							fila[j] = fila[j+1];
						}
						break; //Se o processo for encontrado, o laço que procura o processo será interrompido
					}
				}

				for(i=execultando; i < totProcesso-1; i++){ //Laço que "apaga" o processo do vetor principal (vetProcessos[])
					vetProcessos[i] = vetProcessos[i+1];
				}
				totProcesso--;

				for(i=0; i <= tamFila-1; i++){ 
					/*
						Quando o processo foi "apagado" do vetor principal (vetProcessos[]),
						todos os processos depois dele deslocaram 1 posição pra trás. Então esse
						laço serve para subtrair 1 (no vetor fila[]) de todos os números que 
						forem maiores do que a posição, no vetor principal (vetProcessos[]), 
						do processo que foi "apagado"
					*/
					if(fila[i] > execultando){
						fila[i]--;
					}
				}
				tamFila--;
			}
		} else { //Não tem processo no momento
			printf("\t----------------------------------------------------\n");
			printf("\t|\t\t  %d\t |\t\t\t   |\n", tempo);
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