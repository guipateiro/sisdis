#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tempo.h"
#include "cisj.h"

#define MAXSIZE 1024

typedef struct node_t {
    int content;
    struct node_t* next[MAXSIZE];
    int num_leaves;
} node_t;

typedef struct printbuffer{
    int **buffer;
    int *index;
} buffer_t;

extern buffer_t *print_buffer; // Declaração da variável global

void create_buffer(int size);
void add_to_buffer(int valor, int altura);
void printb();
node_t *create_node(node_t *root, int content);
void print_tree(node_t *root);
int locate_in_array(int element, int array[], int array_size);
int locate_in_list(int element, list *l);
int first_correct_process(int i, int s, list* fail_list);
void tree_step(node_t *node, int s, list *fail_list,int altura);
void generate_tree(int starting_process, int dimensions, int failed_processes[], int failed_process_size);
void arvore_geradora_minima(TipoProcesso processo,int token,int dimensao);

#endif

// + - + - + - + -
// + + - - + + - -
// + + + + - - - -