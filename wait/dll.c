#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    int index;
    struct Node* prev;
    struct Node* next;
};
int length = 0;

struct Node* dll_make (int value, struct Node* prev, struct Node* next)
{
    struct Node* new_node = malloc(sizeof(struct Node*));
    new_node->value = value;
    new_node->index = length;
    new_node->prev = prev;
    new_node->next = next;

    length++;
    return new_node;
}

void dll_update_indexes (struct Node* root, int add)
{
    /**
     * When a node is inserted or deleted
     * at the start or at the middle the next
     * indexes nodes must be updated.
     * **/
    while ( root ) {
        root->index += add;
        root = root->next;
    }
}

void dll_pop (struct Node** root, int index)
{
    if ( index >= length || index <= -1 ) {
        printf("Unrechable index: %d\n", index);
        return;
    }
    if ( !index && length == 1 ) {
        printf("Only there is one node, could not be deleted.\n");
        return;
    }

    struct Node* insert_n = (*root);
    while ( insert_n ) {
        if ( insert_n->index == index ) { break; }
        insert_n = insert_n->next;
    }

    if ( !index ) {
        (*root) = (*root)->next;
        (*root)->prev = NULL;
        dll_update_indexes(insert_n, -1);
    }
    else if ( index == (length - 1) ) {
        insert_n->prev->next = NULL;
        insert_n->prev = NULL;
    }
    else {
        dll_update_indexes(insert_n->next, -1);
        insert_n->next->prev = insert_n->prev;
        insert_n->prev->next = insert_n->next;
        insert_n->next = NULL;
        insert_n->prev = NULL;
    }
    free (insert_n);
    length--;
}

void dll_push (struct Node** root, int value, int index)
{
    if ( index >= length || index <= -2  ) {
        printf("Unrechable index: %d\n", index);
        return;
    }

    struct Node* insert_n = (*root);
    while ( insert_n ) {
        if ( insert_n->index == index ) { break; }
        insert_n = insert_n->next;
    }

    if ( index == -1 ) {
        (*root)->prev = dll_make(value, NULL, *root);
        (*root) = (*root)->prev;
        (*root)->index = 0;
        dll_update_indexes((*root)->next, 1);
    }
    else if ( index == (length - 1) ) {
        insert_n->next = dll_make(value, insert_n, NULL);
    }
    else {
        dll_update_indexes(insert_n->next, 1);
        insert_n->next = dll_make(value, insert_n, insert_n->next);
        insert_n->next->next->prev = insert_n->next;
        insert_n->next->index = insert_n->index + 1;
    }
}

void dll_print (struct Node* root)
{
    while ( root ) {
        printf("[%d %d], ", root->value, root->index);
        root = root->next;
    }
    printf("null\n");
}

void dll_edit (struct Node* root, int new_value, int index)
{
    if ( index >= length || index <= -1 ) {
        printf("Unrechable index: %d\n", index);
        return;
    }

    while ( root ) {
        if ( root->index == index ) { break; }
        root = root->next;
    }
    root->value = new_value;
}

int main ()
{
    struct Node* main_node = dll_make(2, NULL, NULL);
    dll_push(&main_node, 4, -1);
    dll_push(&main_node, 8, 1);
    dll_push(&main_node, 9, 1);
    dll_print(main_node);

    dll_pop(&main_node, 0);
    dll_push(&main_node, 16, -1);
    dll_push(&main_node, 16, length - 1);
    dll_edit(main_node, -16, length - 1);
    dll_print(main_node);

    dll_pop(&main_node, length - 1);
    dll_pop(&main_node, 0);
    dll_pop(&main_node, length - 1);
    dll_pop(&main_node, 0);

    dll_print(main_node);
    return 0;
}
