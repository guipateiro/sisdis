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
    return node;
}

void print_tree(node_t *root) {
    printf("%d ", root->content);
    for (int i = 0; i < root->num_leaves; i++)
        print_tree(root->next[i]);
}

int locate_in_array(int element, int array[], int array_size) {
    for (int i = 0; i < array_size; i++) {
        if (element == array[i])
            return 1;
    }
    return 0;
}

int locate_in_list(int element, list *l) {
    while (l) {
        if(element == l->data)
            return 1;
        l = l->next;
    }
    return 0;
}

int first_correct_process(int i, int s, list* fail_list) {
	int xor = i ^ POW_2(s-1);
	int j;

    node_set *possible_values = cis(i, s);
    //printf("%d\n", possible_values->size);
    int *sorted = malloc(sizeof(int) * possible_values->size);
    int size = possible_values->size;
    for (int j = 0; j < size; j++) {
        sorted[j] = possible_values->nodes[j]; // transfer to an array for sorting
    }
    //these must be sorted in order to establish priority among processes
    specialSort(sorted, size);
    //printArray(sorted, size);
    for (int j = 0; j < size; j++) {
        if (!locate_in_list(sorted[j], fail_list)) {
            //printf("%d\n", sorted[j]);
            return sorted[j];
        }
    }
    return -1;
}

void tree_step(node_t *node, int s, list *fail_list) {
    if (!node)
        return;
    printf("%d ", node->content);

    if (s == 1) {
        return;
    }
    for (int j = 1; j <= s-1; j++) {
        int k = first_correct_process(node->content, j, fail_list);
        if (k < 0) continue;
        node_t* new_node = create_node(node, k);
        tree_step(new_node, j, fail_list);
    }
}

void generate_tree(int starting_process, int dimensions, int failed_processes[], int failed_process_size) {
    list *fail_list = create_list(failed_processes, failed_process_size);
    printf("%d ", starting_process);
    for (int j = 1; j <= dimensions; j++) {
        int k = first_correct_process(starting_process, j, fail_list);
        if (k < 0) continue;
        node_t* tree = create_node(NULL, k);
        tree_step(tree, j, fail_list);
    }
    
}

int main() {
    unsigned int startingNode = 0;
    unsigned int dimensions = 3;
    static const int failed_processes[] = {1};
    int failed_process_size = sizeof(failed_processes)/sizeof(failed_processes[0]);

    generate_tree(startingNode, dimensions, failed_processes, failed_process_size);
    
    return 0;
}

// + - + - + - + -
// + + - - + + - -
// + + + + - - - -