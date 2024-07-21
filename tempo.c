/* Autor: Elias P. Duarte Jr.
   Data da Ãšltima ModificaÃ§Ã£o: 11/abril/2024
   DescriÃ§Ã£o: Nosso primeiro programa de simulaÃ§Ã£o da disciplina Sistemas DistribuÃ­dos.
     Vamos simular N processos, cada um conta o â€œtempoâ€ independentemente
    Um exemplo simples e significativo para captar o â€œespÃ­ritoâ€ da simulaÃ§Ã£o */

#include <stdio.h>
#include <stdlib.h>
#include "tempo.h"
#include "cisj.h"
#include "tree.h"

int log_n(int n){
    if (n == 0)
        return 0;
    
    int pos = 0;
    
    // Fazendo um deslocamento para a direita até encontrar o bit 1 mais significativo
    while (n != 0) {
        n = n >> 1;
        pos++;
    }
    
    return pos;
}

int*** geraclusters(int N){
    int clusters = log_n(N);
    // Alocar dinamicamente um array de ponteiros para as linhas da matriz
    int*** matriz = (int***)malloc(clusters * sizeof(int**));
    // Verificar se a alocação foi bem sucedida
    if (matriz == NULL) {
        printf("Erro ao alocar memória.");
        return NULL;
    }
    // Alocar dinamicamente cada linha da matriz e cada elemento da linha
    for (int i = 0; i < clusters-1; i++) {
        // Tamanho do vetor para esta linha
        matriz[i] = (int**)malloc(N * sizeof(int*));
        // Verificar se a alocação foi bem sucedida
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memória.");
            return NULL;
        }
        // Alocar dinamicamente cada elemento da linha (vetor de tamanho N)
        for (int j = 0; j < N; j++) {
            int tamanho_linha = pow(2, i);
            matriz[i][j] = (int*)malloc(tamanho_linha * sizeof(int));

            // Verificar se a alocação foi bem sucedida
            if (matriz[i][j] == NULL) {
                printf("Erro ao alocar memória.");
                return NULL;
            }
			//printf("cis (%d %d)\n", j , i+1);
            node_set* nodes;
            nodes = cis(j,i+1);
			/*for (int l=0; l < nodes->size; l++)
				printf("%i ", nodes->nodes[l]);
			puts("");*/
            // Inicializar valores do vetor
            for (int k = 0; k < nodes->size; k++) {
                matriz[i][j][k] = nodes->nodes[k];
            }
			set_free(nodes);
        }
    }
	/*for (size_t i = 0; i < clusters; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			printf("{");
			for (size_t k = 0; k < pow(2, i); k++)
			{
				printf("%d ", matriz[i][j][k]);
			}
			printf("}");
		}
		printf("\n");
	}
	*/
	return matriz;
}


TipoProcesso* geraprocessos(int N){
    TipoProcesso *processo = (TipoProcesso *) malloc(sizeof(TipoProcesso)*N);
    static char fa_name[5];
    for (int i=0; i<N; i++) {
        //gera o id
        memset(fa_name, '\0', 5);
        //sprintf(fa_name, "%d", i);
        processo[i].id = facility(fa_name,1);
        memset(fa_name, '\0', 5);
        // gera numero de clusters
        processo[i].clusters = log_n(N);
        // gera o processo que sera testado por esse processo

        processo[i].tabela_testadores = geraclusters(N);
       
        //gera o vetor de estados 
        processo[i].state = (Tipoestado *)malloc(N * sizeof(Tipoestado));
		processo[i].change_buffer = (Tipoestado *)malloc(N * sizeof(Tipoestado));
        for (int j = 0; j < N; j++){
            processo[i].state[j].estado = -1;
            processo[i].state[j].tempo = 0;
            processo[i].state[j].latencia = 0;
        }
		processo[i].state[i].estado = 0;
        processo[i].state[i].tempo = 0;
        processo[i].state[i].latencia = 0;

		processo[i].morri = 0; // 0 ok 1 falha
    }

    return processo;
}

int decobre_testador(TipoProcesso processo, int i, int j){
	for(int k = 0; k < pow(2, i); k++){
		if(processo.state[processo.tabela_testadores[i][j][k]].estado != 1){
			return processo.tabela_testadores[i][j][k];
		}
	}
}

void renew(TipoProcesso processo, int N){
	free(processo.change_buffer);
	processo.change_buffer = (Tipoestado *)malloc(N * sizeof(Tipoestado));
	for(int i = 0; i < N; i++){
		processo.change_buffer[i].estado = -2;
		processo.change_buffer[i].tempo = -1;
        processo.change_buffer[i].latencia = 0;
	}
}

void atualizarstate(TipoProcesso processo, int j, int estado,int tempo){
	processo.change_buffer[j].estado = estado; 
	processo.change_buffer[j].tempo = tempo;
    processo.change_buffer[j].latencia = 0;
}

void aply(TipoProcesso processo, int N){
	for(int i = 0; i < N; i++){
		if (processo.change_buffer[i].tempo >= processo.state[i].tempo && processo.change_buffer[i].tempo >= 0 ){
			processo.state[i].estado = processo.change_buffer[i].estado;
			processo.state[i].tempo = processo.change_buffer[i].tempo;
            processo.state[i].latencia = processo.change_buffer[i].latencia;
		}
	}
}

void imprimeestados(TipoProcesso processo, int token, int N){
	//printf("=================================================\n");
    for(int i = 0; i < N; i++){
		//printf("processo %d considera processo %d como ",token ,i);
		if(processo.state[i].estado == 0){
			//printf("correto\n");
		} else if(processo.state[i].estado == -1){
			//printf("desconhecido\n");
		} else {
			//printf("falho\n");
		}
	}
    //printf("=================================================\n");
}

int recebernovidades(TipoProcesso processo_atual, TipoProcesso processo_testado,int token,int N){
	for(int i = 0; i < N; i++){
        if(i != token){
            if(processo_atual.state[i].estado != processo_testado.state[i].estado && processo_testado.state[i].tempo - processo_atual.state[i].tempo > 0 ){
                processo_atual.change_buffer[i].estado = processo_testado.state[i].estado;
                if (processo_testado.state[i].tempo - processo_atual.change_buffer[i].tempo > 0){
                    processo_atual.change_buffer[i].latencia = processo_testado.state[i].latencia + 1;
                    //printf("Recebendo atualizações sobre: %d (latencia %d rodadas, %d T) \n",i, processo_atual.change_buffer[i].latencia, (int)time() - processo_testado.state[i].tempo);
                    processo_atual.change_buffer[i].tempo = processo_testado.state[i].tempo;
                }
	        }
        }
    }
}

void imprimeestate(TipoProcesso processo_atual, int N){
    for(int i = 0; i < N; i++){
        //printf("{%d %d} ", processo_atual.state[i].estado, processo_atual.state[i].tempo);
    }
    //printf("\n");
}

int main (int argc, char *argv[]) {
   TipoProcesso *processo;
   
   static int N,   // nÃºmero de processos
            token,  // indica o processo que estÃ¡ executando
            event, r, i,
            MaxTempoSimulac = 250;

   static char fa_name[5];

   if (argc != 2) {
       puts("Uso correto: tempo <nÃºmero de processos>");
       exit(1);
    }

   N = atoi(argv[1]);

   smpl(0, "Um Exemplo de Simulacao");
   reset();
   stream(1);

   // inicializar processos
   processo = geraprocessos(N);

   int ***sla = geraclusters(N);
   int clusters = log_n(N);
   /*for (size_t i = 0; i < clusters-1; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			printf("{");
			for (size_t k = 0; k < pow(2, i); k++)
			{
				printf("%d ", sla[i][j][k]);
			}
			printf("}");
		}
		printf("\n");
	}*/
    // vamos fazer o escalonamento inicial de eventos

    // nossos processos vÃ£o executar testes em intervalos de testes
    // o intervalo de testes vai ser de 30 unidades de tempo
    // a simulaÃ§Ã£o comeÃ§a no tempo 0 (zero) e vamos escalonar o primeiro teste de todos os    
    //       processos para o tempo 30.0

    for (int i=0; i<N; i++) {
       schedule(test, 30.0, i); 
    }

    //schedule(fault, 1.0, 0);
    //schedule(fault, 1.0, 1);
    //schedule(fault, 1.0, 2);
    //schedule(fault, 1.0, 4);
    //schedule(fault, 1.0, 7);
    schedule(arvore_geradora, 150.0, 0);

    // agora vem o loop principal do simulador



    puts("===============================================================");
    puts("           Sistemas Distribuidos Prof. Elias");
    puts("          LOG do Trabalho Pratico 2, Tarefa 5");
    puts("      imprimir arvore gferadora minima usando v-cubev2");
    printf("   Este programa foi executado para: N=%d processos.\n", N); 
    printf("           V-cube tamanho = %d\n", clusters-1);
    puts("===============================================================");

    while(time() < 200.0) {
        cause(&event, &token);
        switch(event) {
           	case test: 
                if (status(processo[token].id) !=0) break; // se o processo estÃ¡ falho, nÃ£o testa!
				renew(processo[token],N);
                //printf("=================================================\n");
				for (int i = 0; i < clusters-1; i++){
					for (int j = 0; j < N; j++){
						if(decobre_testador(processo[token],i,j) == token){
							//printf("Processo %d: estou testando o processo %d no tempo %4.1f: \n", token, j, time());
							if(processo[j].morri == 0){
								//printf("correto \n");
								atualizarstate(processo[token],j,0,time());
								recebernovidades(processo[token],processo[j],token,N);
							}else {
								//printf("falha \n");
								atualizarstate(processo[token],j,1,time());
							}
						}
					}
				}
                //printf("=================================================\n");
                schedule(apply, 1.0, token);
                break;
            case apply:
                if (status(processo[token].id) !=0) break;
                aply(processo[token],N);
				//imprimeestados(processo[token], token,N);
                //imprimeestate(processo[token],N);
                schedule(test, 29.0, token);
                break;
           case fault:
                r = request(processo[token].id, token, 0);
				processo[token].morri = 1;
                //printf("----------------------------------------------------------------\n");
                //printf("Socooorro!!! Sou o processo %d  e estou falhando no tempo %4.1f\n", token, time());
                //printf("----------------------------------------------------------------\n");
                break;
           case recovery:
                release(processo[token].id, token);
				processo[token].morri = 0;
                //printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                //printf("Viva!!! Sou o processo %d e acabo de recuperar no tempo %4.1f\n", token, time());
                //printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                schedule(test, 1.0, token);
                break;
            case arvore_geradora:
                arvore_geradora_minima(processo[token],token, clusters-1);
            break;
          } // switch
    } // while
} // tempo.c
        