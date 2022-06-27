#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    int index;
    struct Node* left;
    struct Node* right;
};
int n_nodes = 0;

struct Node* dll_make (int value, int index, struct Node* left, struct Node* right)
{
    struct Node* new_n = malloc(sizeof(struct Node));
    new_n->value = value;
    new_n->index = index;
    new_n->left = left; 
    new_n->right = right; 

    n_nodes++;
    return new_n;
}

void dll_update_indexes (struct Node* from, int set)
{
    /**
     * When some element is pushed or deleted at the middle
     * or at the begin (only pop operation) the indexes
     * must be updated to make future oprations.
     * **/
    struct Node* updaten = from;
    while ( updaten ) {
        updaten->index += set;
        updaten = updaten->right;
    }
}

void dll_print (struct Node* main)
{
    /**
     * Prints the value and the index:
     * (value index)
     * **/
    struct Node* auxp = main;
    while ( auxp ) {
        printf("(%d %d), ", auxp->value, auxp->index);
        auxp = auxp->right;
    }
    printf("null.\n");
}

void dll_push (struct Node* main, int value, int index)
{
    if ( index > n_nodes || index <= -1 ) {
        printf("Unreachable index: %d\n", index);
        return;
    }

    struct Node* insertn = main;
    while ( insertn ) {
        if ( insertn->index == index ) { break; }
        insertn = insertn->right;
    }

    if ( !insertn->right ) {
        /**
         * When there is not another node to the right
         * in the current node means the current
         * node is the last one on the list.
         * **/
        insertn->right = dll_make(value, index + 1, insertn, NULL);
    }
    else {
        struct Node* rightn = insertn->right;
        /**
         * All nodes must be updated (index value)
         * from the next node until the last one, its index value
         * must be incremented by 1.
         * **/
        dll_update_indexes(rightn, 1);

        /**
         * At the begin: [1 0] = [2 1] = [3 2]
         *                 \ maybe here is pointing insertn, and maybe the value
         *                 5 will be inserted.
         * Then: [1 0] = [5 1] = [2 2] = [3 3]
         * **/
        insertn->right = dll_make(value, index + 1, insertn, NULL);
        insertn->right->right = rightn;
        rightn->left = insertn->right;
    }
}

void dll_pop (struct Node** main, int index)
{
    if ( index > n_nodes || index <= -1 ) {
        printf("Unreachable index: %d\n", index);
        return;
    }
    /**
     * When only there is one node, that node could not be deleted
     * because there will be not a reference to the list then.
     * **/
    if ( !index && n_nodes == 1 ) {
        printf("Only there is one node, could not be deleted\n");
        return;
    }

    /**
     * The pop function needs the original main node, not a reference.
     * **/
    struct Node* popn = (*main);
    while ( popn ) {
        if ( popn->index == index ) { break; }
        popn = popn->right;
    }

    if ( !popn->right ) {
        /**
         * Remove the last one:
         * At the begin: [3 0] = [4 1] = [1 3]
         * Then: [3 0] = [4 1]
         * **/
        popn->left->right = NULL;
        popn->left = NULL;
    }
    else if ( !index ) {
        /**
         * Remove the first one:
         * At the begin: [1 0] = [2 1] = [3 2]
         * Then: [2 0] = [3 1]
         * **/
        dll_update_indexes(popn->right, -1);
        (*main) = popn->right;
        (*main)->left = NULL;
        popn->right = NULL;
    }
    else {
        /**
         * Remove one node at the midddle:
         * At the begin: [1 0] = [2 1] = [3 2]
         * Then: [1 0] = [3 1]
         * **/
        dll_update_indexes(popn->right, -1);
        popn->right->left = popn->left;
        popn->left->right = popn->right;
        popn->right = NULL;
        popn->left = NULL;
    }

    free(popn);
    n_nodes--;
}

void dll_edit (struct Node* main, int newval, int index)
{
    if ( index > n_nodes || index <= -1 ) {
        printf("Unreachable index: %d\n", index);
        return;
    }
    struct Node* editn = main;
    while ( editn ) {
        if ( editn->index == index ) { break; }
        editn = editn->right;
    }
    editn->value = newval;
}

int main ()
{
    struct Node* main = dll_make(1, 0, NULL, NULL);
    dll_push(main, 2, 0);
    dll_push(main, 3, 1);
    dll_push(main, 4, 2);
    dll_push(main, 5, 3);
    dll_print(main);

    dll_edit(main, 16, 0);
    dll_print(main);

    dll_pop(&main, 0);
    dll_push(main, -15, 0);
    dll_print(main);

    dll_pop(&main, n_nodes - 1);
    dll_pop(&main, 2);
    dll_print(main);
    return 0;
}

