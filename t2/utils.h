
typedef struct list {
    int data;
    struct list* next;
} list;



void specialSort(int arr[], int n);
list* create_list_node(int data);
list* create_list(int data[], int size);
void append(list** headRef, int data);
void printList(list* head);
void printArray(int arr[], int n);
void freeList(list* head);
