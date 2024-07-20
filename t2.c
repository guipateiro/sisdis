#include <stdio.h>
#include <stdlib.h>

#define POW_2(num) (1<<(num))
#define MAXSIZE 1024

typedef struct {
    int content;
    node_t* next[MAXSIZE];
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

int modified_cis() {
    return 0; // TODO IMPLEMENT
}

int* mst(node_t *node, int dimensions, int failed_processes[]) {

    if (!node)
        return NULL;

    printf('%d ', node->content);

    int i = modified_cis();
    int xor = node->content ^ POW_2(dimensions-1);
    
    for (int j = 1; j <= dimensions; ++j) {

    }
    
}

int main() {
    unsigned int startingNode = 0;
    unsigned int dimensions = 3;
    static const int failed_processes[] = {4,6};

    mst(create_node(NULL, 0), dimensions, failed_processes);
    
    return 0;
}

// + - + - + - + -
// + + - - + + - -
// + + + + - - - -