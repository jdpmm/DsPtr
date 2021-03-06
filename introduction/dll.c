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

    /**
     * insert_n is just a reference to whole node,
     * insert_n could not modific the whole node, just
     * its values.
     * **/
    struct Node* insert_n = (*root);
    while ( insert_n ) {
        if ( insert_n->index == index ) { break; }
        insert_n = insert_n->next;
    }

    if ( !index ) {
        /**
         * When the first node will be deleted
         * the whole node (root) must be modified,
         * that's why this part does not use insert_n.
         * **/
        (*root) = (*root)->next;
        (*root)->prev = NULL;
        dll_update_indexes(insert_n, -1);
    }
    else if ( index == (length - 1) ) {
        /**
         * The node to be deleted is the
         * last one.
         * **/
        insert_n->prev->next = NULL;
        insert_n->prev = NULL;
    }
    else {
        /**
         * The node to be deleted is at
         * the middle on the list.
         * **/
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
    /**
     * -1 included because if it wants push some
     * node at the start of the list the index
     * must be -1.
     * **/
    if ( index >= length || index <= -2  ) {
        printf("Unrechable index: %d\n", index);
        return;
    }

    struct Node* insert_n = (*root);
    while ( insert_n ) {
        if ( insert_n->index == index ) { break; }
        insert_n = insert_n->next;
    }

    /**
     * It's the same, when the whole root should be modified
     * root is used, insert_n otherwise.
     * **/
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

void dll_deleteduplicates (struct Node** root, int torm)
{
    struct Node* rmdts = (*root);
    while ( rmdts ) {
        if ( rmdts->value == torm ) {
            dll_pop(root, rmdts->index);
        }
        rmdts = rmdts->next;
    }
}

int main ()
{
    /**
     * This list uses also an index
     * to make other operations.
     * The index also starts from 0 :D.
     * **/
    struct Node* main_node = dll_make(2, NULL, NULL);
    dll_push(&main_node, 4, -1);
    dll_push(&main_node, 8, 1);
    dll_push(&main_node, 9, 1);
    dll_print(main_node);

    dll_pop(&main_node, 0);
    dll_push(&main_node, 16, -1);
    dll_push(&main_node, 16, length - 1);
    dll_edit(main_node, -16, length - 1);
    dll_push(&main_node, 16, 1);
    dll_print(main_node);

    dll_deleteduplicates(&main_node, 16);
    dll_pop(&main_node, 0);
    dll_print(main_node);
    return 0;
}
