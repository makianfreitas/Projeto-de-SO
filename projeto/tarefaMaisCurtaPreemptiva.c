/*
    TAREFA MAIS CURTA PREEMPTIVA
    Integrantes:
        Gabriela Monteiro
        Hugo Gabriel
        Ian Rodrigo
        Igor Caian
        Makian Freitas
        Pablo Fernandes
        Reginaldo Cruz
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

void criaProcessos(processo *vetProc); //Cria os processos (armazena os valores no vetor principal (vetProcessos[]))
void imprimeProcessosCriados(processo *vetProc); //Imprime o ID, o tamanho e o tempo de chegada de cada processo
void timeCPU(processo *vetProc, int *fila); //Passa o tempo
void filaProcessos(processo *vetProcessos, int *fila); //Organiza a fila
void escalonador(processo *vetProcessos, int *fila); //Verifica qual é o processo com o menor tamanho
void cpu(int executando, processo *vetProcessos, int *fila); //Executa o processo
void relatorio(); //Informações extras

int i; //Variável para os laços
float tempoTotal; //Tempo total/atual
float tempoUtil=0; //Contador que representa o tempo que a CPU foi utilizada
float tempoInutil=0; //Contador que representa o tempo que a CPU não foi utilizada
int totProcesso; //Quantidade total de processos e tamanho lógico do vetor principal vetProcessos[]
/*
	totProcesso é a posição limite do vetor principal (vetProcessos[]), 
	ou seja, o vetor será lido até a posição totProcesso. Se tiver alguma coisa 
	amazenada depois desta posição (no vetor vetProcessos[]), será 
	ignorado pois se trata de processo(s) finalizado(s)
*/
int tamFila=-1; //Tamanho lógico do vetor fila[]
/*
	tamFila é a posição limite do vetor fila[], ou seja, 
	o vetor será lido até a posição tamFila. Se tiver alguma coisa 
	amazenada depois desta posição (no vetor fila[]), será 
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
	timeCPU(vetProcessos, fila);
	relatorio();
	printf("\n\tFim do programa\n\n");
	system("pause");
	return 0;
}

void criaProcessos(processo *vetProcessos){ //Cria os processos (armazena os valores no vetor principal (vetProcessos[]))
	srand(time(NULL));
	for (i=0; i < totProcesso; i++) {
		vetProcessos[i].tamJobs = 3 + rand() % 12; //Tamanho do processo é gerado aleatoriamente (de 3 a 15)
		vetProcessos[i].tempoChegadaNaFila = rand() % 15; //Tempo de chegada é gerado aleatoriamente (de 0 a 15)
		vetProcessos[i].idProcesso = 65 + i; //idProcesso recebe o código de cada letra baseado na tabela ASCII (exemplo: 65 = A e 90 = Z)
		vetProcessos[i].faltaProcessar = vetProcessos[i].tamJobs; //faltaProcessar recebe inicialmente o tamanho do processo (tamJobs)
	}
}

void imprimeProcessosCriados(processo *vetProcessos){ //Imprime o ID, o tamanho e o tempo de chegada de cada processo
	system("cls");
	system("cls");
	printf("\t---------------------------------------------------\n");
	printf("\t| ID Processo | Tamanho do Job | Tempo de Chegada |\n");
	for(i=0; i < totProcesso; i++){
		printf("\t---------------------------------------------------\n");
		printf("\t|    %c \t      |    %d \t       |    %d \t\t  |\n", vetProcessos[i].idProcesso, vetProcessos[i].tamJobs, vetProcessos[i].tempoChegadaNaFila);
	}
	printf("\t---------------------------------------------------\n\n");
}

void timeCPU(processo *vetProcessos, int *fila){ //Passa o tempo
	imprimeProcessosCriados(vetProcessos);
	printf("\n\t---------------------------------------------------\n");
	printf("\t| Tempo\t| Processo em Execucao\t| Falta Processar |\n");
	for(tempoTotal=0; totProcesso > 0; tempoTotal++){ //Laço que representa o tempo
		filaProcessos(vetProcessos, fila); //Organiza a fila
		if(tamFila > -1){ //Verifica se existe processo para ser executado
			escalonador(vetProcessos, fila); //Verifica qual é o processo com o menor tamanho
			tempoUtil++;
		} else { //Não tem processo no momento
			printf("\t---------------------------------------------------\n");
			printf("\t|  %.0f\t|           -\t\t|        -\t  |\n", tempoTotal); //Imprime a linha da tabela sem processo
			tempoInutil++;
		}
	}
	printf("\t---------------------------------------------------\n\n");
}

void filaProcessos(processo *vetProcessos, int *fila){ //Organiza a fila
	for(i=0; i < totProcesso; i++){ //Laço que verifica se chegou processo no tempo atual
		if(vetProcessos[i].tempoChegadaNaFila == tempoTotal){
			tamFila++; //Aumenta o tamanho lógico da fila
			fila[tamFila] = i; //fila[] recebe a posição, no vetor principal (vetProcessos[]), do processo que chegou
		}
	}
}

void escalonador(processo *vetProcessos, int *fila){ //Verifica qual é o processo com o menor tamanho
	int menorProcesso; //Armazena a posição, no vetor principal (vetProcessos[]), do processo com o menor tamanho, ou seja, o processo que será executado
	menorProcesso = fila[0];
	for(i=1; i <= tamFila; i++){ //Laço que verifica qual é o processo com o menor tamanho
		if(vetProcessos[fila[i]].faltaProcessar < vetProcessos[menorProcesso].faltaProcessar){
			menorProcesso = fila[i]; //menorProcesso recebe a posição, no vetor principal (vetProcessos[]), do processo com o menor tamanho
		}
	}
	cpu(menorProcesso, vetProcessos, fila);
}

void cpu(int executando, processo *vetProcessos, int *fila){ //Executa o processo
	int j; //Variável para o laço
	printf("\t---------------------------------------------------\n");
	printf("\t|  %.0f\t|           %c\t\t|        %d\t  |\n", tempoTotal, vetProcessos[executando].idProcesso, vetProcessos[executando].faltaProcessar - 1); //Imprime o tempo, o ID e a quantidade que resta do processo em execução
	vetProcessos[executando].faltaProcessar--;

	if(vetProcessos[executando].faltaProcessar == 0){ //Verifica se o processo que acabou de ser executado terminou
		for(i=0; i <= tamFila; i++){ //Laço que procura este processo no vetor fila[]
			if(fila[i] == executando){ //Verifica se esta posição é o processo que será "apagado" do vetor fila[]
				for(j=i; j <= tamFila-1; j++){ //Laço que "apaga" o processo do vetor fila[]
					fila[j] = fila[j+1];
				}
				break; //Se o processo for encontrado, o laço que procura o processo será interrompido
			}
		}

		for(i=executando; i < totProcesso-1; i++){ //Laço que "apaga" o processo do vetor principal (vetProcessos[])
			vetProcessos[i] = vetProcessos[i+1];
		}
		totProcesso--; //Diminui o tamanho lógico do vetor principal (vetProcessos[])

		for(i=0; i <= tamFila-1; i++){ 
			/*
				Quando o processo foi "apagado" do vetor principal (vetProcessos[]),
				todos os processos depois dele deslocaram 1 posição para trás. Então esse
				laço serve para subtrair 1 (no vetor fila[]) de todos os números que 
				forem maiores do que a posição, no vetor principal (vetProcessos[]), 
				do processo que foi "apagado"
			*/
			if(fila[i] > executando){ //Verifica se a posição armazenada é maior que a posição do processo que foi "apagado"
				fila[i]--;
			}
		}
		tamFila--; //Diminui o tamanho lógico do vetor fila[]
	}
}

void relatorio(){ //Informações extras
	printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<< RELATORIO >>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
	printf("\tConclusao no tempo total de: %.0f\n", tempoTotal);
	printf("\tTempo de ultilizacao da CPU: %.0f\n", tempoUtil);
	printf("\tTempo de inultilizacao da CPU: %.0f\n", tempoInutil);
	printf("\tPercentual de utilizacao da CPU: %.2f %%\n", (tempoUtil / tempoTotal)*100);
	printf("\tPercentual de inutilizacao da CPU: %.2f %%\n\n", (tempoInutil / tempoTotal)*100);
}