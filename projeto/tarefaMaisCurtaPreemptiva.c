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

void criaProcessos(processo *vetProc); //Cria os processos (armazena os valores no vetor principal (vetProcessos[]))
void imprimeProcessosCriados(processo *vetProc); //Imprime o ID, o tamanho e o tempo de chegada de cada processo
void timeCPU(processo *vetProc, int *fila); //Passa o tempo
void filaProcessos(processo *vetProcessos, int *fila); //Organiza a fila
void escalonador(processo *vetProcessos, int *fila); //Verifica qual é o processo com o menor tamanho
void cpu(int execultando, processo *vetProcessos, int *fila); //Execulta o processo

int tempo; //Tempo atual
int i; //Variável para os laços
int totProcesso; //Quantidade total de processos e tamanho lógico do vetor principal vetProcessos[]
/*
	totProcesso é a posição limite do vetor principal (vetProcessos[]), 
	ou seja, o vetor será lido até a posição tamFila. Se tiver alguma coisa 
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
	printf("\t---------------------------------------------------\n\n");
	system("pause");
	return 0;
}

void criaProcessos(processo *vetProcessos) { //Cria os processos (armazena os valores no vetor principal (vetProcessos[]))
	srand(time(NULL));
	for (i = 0; i < totProcesso; i++) {
		vetProcessos[i].tamJobs = 4 + rand() % 16; //Tamanho do processo é gerado aleatoriamente (de 4 a 20)
		vetProcessos[i].tempoChegadaNaFila = rand() % 15; //Tempo de chegada é gerado aleatoriamente (de 0 a 15)
		vetProcessos[i].idProcesso = 65 + i; //idProcesso recebe o código de cada letra baseado na tabela ASCII (exemplo: 65 = A e 90 = Z)
		vetProcessos[i].faltaProcessar = vetProcessos[i].tamJobs; //faltaProcessar recebe inicialmente o tamanho do processo (tamJobs)
	}
}


void imprimeProcessosCriados(processo *vetProcessos) { //Imprime o ID, o tamanho e o tempo de chegada de cada processo
	int i;
	system("cls");
	system("cls");
	printf("\t---------------------------------------------------\n");
	printf("\t| ID Processo | Tamanho do Job | Tempo de Chegada |\n");
	for(i = 0; i < totProcesso; i++){
		printf("\t---------------------------------------------------\n");
		printf("\t|    %c \t      |    %d \t       |    %d \t\t  |\n", vetProcessos[i].idProcesso, vetProcessos[i].tamJobs, vetProcessos[i].tempoChegadaNaFila);
	}
	printf("\t---------------------------------------------------\n\n");
}

void timeCPU(processo *vetProcessos, int *fila) { //Passa o tempo
	imprimeProcessosCriados(vetProcessos);
	printf("\n\t---------------------------------------------------\n");
	printf("\t| Tempo\t| Processo em Execulcao\t| Falta Processar |\n");
	for(tempo=0; totProcesso > 0; tempo++){ //Laço que representa o tempo
		filaProcessos(vetProcessos, fila); //Organiza a fila
		if(tamFila > -1){ //Verifica se existe processo para ser execultado
			escalonador(vetProcessos, fila); //Verifica qual é o processo com o menor tamanho
		} else { //Não tem processo no momento
			printf("\t---------------------------------------------------\n");
			printf("\t|  %d\t|           -\t\t|        -\t  |\n", tempo); //Imprime a linha da tabela sem processo
		}
	}
}

void filaProcessos(processo *vetProcessos, int *fila) { //Organiza a fila
	for(i=0; i < totProcesso; i++){ //Laço que verifica se chegou processo no tempo atual
		if(vetProcessos[i].tempoChegadaNaFila == tempo){
			tamFila++; //"Aumenta" o tamanho da fila
			fila[tamFila] = i; //fila[] recebe a posição, no vetor principal (vetProcessos[]), do processo que chegou
		}
	}
}

void escalonador(processo *vetProcessos, int *fila) { //Verifica qual é o processo com o menor tamanho
	int menorProcesso; //Armazena a posição, no vetor principal (vetProcessos[]), do processo com o menor tamanho, ou seja, o processo que será execultado
	menorProcesso = fila[0];
	for(i=1; i <= tamFila; i++){ //Laço que verifica qual é o processo com o menor tamanho
		if(vetProcessos[fila[i]].faltaProcessar < vetProcessos[menorProcesso].faltaProcessar){
			menorProcesso = fila[i]; //menorProcesso recebe a posição, no vetor principal (vetProcessos[]), do processo com o menor tamanho
		}
	}
	cpu(menorProcesso, vetProcessos, fila);
}

void cpu(int execultando, processo *vetProcessos, int *fila) { //Execulta o processo
	int j; //Variável para o laço
	printf("\t---------------------------------------------------\n");
	printf("\t|  %d\t|           %c\t\t|        %d\t  |\n", tempo, vetProcessos[execultando].idProcesso, vetProcessos[execultando].faltaProcessar - 1); //Imprime o tempo, o ID e a quantidade que resta do processo em execulção
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
				todos os processos depois dele deslocaram 1 posição para trás. Então esse
				laço serve para subtrair 1 (no vetor fila[]) de todos os números que 
				forem maiores do que a posição, no vetor principal (vetProcessos[]), 
				do processo que foi "apagado"
			*/
			if(fila[i] > execultando){ //Verifica se a posição armazenada é maior que a posição do processo que foi "apagado"
				fila[i]--;
			}
		}
		tamFila--;
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