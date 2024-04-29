#ifndef __TEMPO__
#define __TEMPO__
/* Autor: Elias P. Duarte Jr.
   Data da Ãšltima ModificaÃ§Ã£o: 11/abril/2024
   DescriÃ§Ã£o: Nosso primeiro programa de simulaÃ§Ã£o da disciplina Sistemas DistribuÃ­dos.
     Vamos simular N processos, cada um conta o â€œtempoâ€ independentemente
    Um exemplo simples e significativo para captar o â€œespÃ­ritoâ€ da simulaÃ§Ã£o */

#include <stdio.h>
#include <stdlib.h>
#include "smpl.h"

// Vamos definir os EVENTOS 
#define test 1
#define fault 2
#define recovery 3
#define apply 4

// Vamos definir o descritor do processo

typedef struct{
   int estado; // -1 , 0 ,1 
   int tempo; // tempo em que esse estado foi pego, pra evitar conflito de update
   int latencia; // tempo que levou para receber a quantas rodadas demorou para chegar a info
} Tipoestado;


typedef struct{ 
   int id;            // identificador de facility do SMPL
   Tipoestado *state;
   Tipoestado *change_buffer;
   int ***tabela_testadores;  //tabela com os possiveis nodos testados
   int clusters; //numero de clusters nessa implemetacao
   int morri;
   // outras variÃ¡veis locais dos processos sÃ£o declaradas aqui!
} TipoProcesso;

#endif