#include <stdio.h>
#include <stdlib.h>
#include "cisj.h"
#include "utils.h"

#define MAXSIZE 1024

typedef struct node_t {
    int content;
    struct node_t* next[MAXSIZE];
    int num_leaves;
} node_t;

node_t *create_node(node_t *root, int content) {
    node_t *node = malloc(sizeof(node_t));
    if (root) {
        root->num_leaves++;
        root->next[root->num_leaves - 1] = node;
    }
    node->content = content;
    node->num_leaves = 0;
}

int locate_in_array(int element, int array[], int array_size) {
    for (int i = 0; i < array_size; i++) {
        if (element == array[i])
            return 1;
    }
    return 0;
}

int first_correct_process(int i, int s, int invalid_array[], int invalid_array_size) {
	int xor = i ^ POW_2(s-1);
	int j;

    node_set *possible_values = cis(i, s);
    //printf("%d\n", possible_values->size);
    int *sorted = malloc(sizeof(int) * possible_values->size);
    for (int j = 0; j < possible_values->size; j++) {
        sorted[j] = possible_values->nodes[j]; // transfer to an array for sorting
    }
    //these must be sorted in order to establish priority among processes
    specialSort(sorted, possible_values->size);
    for (int j = 0; j < possible_values->size; j++) {
        if (!locate_in_array(sorted[j], invalid_array, invalid_array_size))
            return sorted[j];
    }
    return -1;


    //for (i=0; i < possible_values->size; i++)
		//printf("%i ", possible_values->nodes[i]);


    //int *possible_values = malloc((s-1) * sizeof(int));


}

int* mst(node_t *node, int dimensions, int failed_processes[]) {

    if (!node)
        return NULL;

    //printf("%d ", node->content);

    int i = first_correct_process(node->content, dimensions, failed_processes, 1);
    printf("%d\n", i);
    int xor = node->content ^ POW_2(dimensions-1);
    
    for (int j = 1; j <= dimensions; ++j) {

    }
    
}

int main() {
    unsigned int startingNode = 5;
    unsigned int dimensions = 3;
    static const int failed_processes[] = {1,6};

    mst(create_node(NULL, startingNode), dimensions, failed_processes);
    
    return 0;
}

// + - + - + - + -
// + + - - + + - -
// + + + + - - - -