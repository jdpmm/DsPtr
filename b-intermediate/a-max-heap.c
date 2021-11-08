#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX_SIZE 500

typedef struct MAX_HEAP {
    int value;
    struct MAX_HEAP *l; // left
    struct MAX_HEAP *r; // right
    struct MAX_HEAP *p; // parent

    int idxarr;
} maxhn;
maxhn *arrnodes[MAX_SIZE];
int size = 0;

maxhn* create_node (int value, maxhn* parent) {
    maxhn* newnode = (maxhn*) calloc(1, sizeof(maxhn));

    newnode->value = value;
    newnode->l = NULL;
    newnode->r = NULL;
    newnode->p = parent;
    newnode->idxarr = size;

    arrnodes[size] = newnode;
    size++;
    return newnode;
}

void append (int value) {
    int idx_to_newnode = floor( (size + 1) / 2 ) - 1;
    maxhn* auxnode = arrnodes[idx_to_newnode];

    if (auxnode->l == NULL) {
        auxnode->l = create_node(value, auxnode);
    }
    else {
        auxnode->r = create_node(value, auxnode);
    }

    if (value > auxnode->value) {
        maxhn* aux = arrnodes[size - 1];
        while (aux->p != NULL) {
            if (aux->value > aux->p->value) {
                int auxvalue = aux->value;
                aux->value = aux->p->value;
                aux->p->value = auxvalue;

                aux = aux->p;
            }
            else {
                break;
            }
        }
    }
}

bool complete_at_this_moment () {
    return (size % 2) != 0;
}

void pop () {
    maxhn* lastnode = arrnodes[size - 1];
    arrnodes[0]->value = lastnode->value;

    if (lastnode->p->r != NULL) {
        lastnode->p->r = NULL;
    }
    else {
        lastnode->p->l = NULL;
    }
    arrnodes[size - 1] = NULL;
    free (lastnode);
    size--;

    maxhn* rootaux = arrnodes[0];
    while (true) {
        int lvalue, rvalue;
        if (rootaux->l != NULL) {
            lvalue = rootaux->l->value;
        }
        if (rootaux->r != NULL) {
            rvalue = rootaux->r->value;
        }

        if (lvalue > rootaux->value) {
            rootaux = rootaux->l;
            rootaux->value = rootaux->p->value;
            rootaux->p->value = lvalue;
        }
        else if (rvalue > rootaux->value) {
            rootaux = rootaux->r;
            rootaux->value = rootaux->p->value;
            rootaux->p->value = rvalue;
        }

        else {
            break;
        }
    }
}

void print (maxhn *node) {
    if (node != NULL) {
        if (node->p == NULL) {
            printf("ROOT: %d\n", node->value);
        }

        printf("     %d\n", node->value);
        printf("   /    \\\n");

        if (node->l != NULL) printf("%d", node->l->value);
        else printf("NULL");

        if (node->r != NULL) printf("      %d\n", node->r->value);
        else printf("      NULL\n");

        print(node->r);
        print(node->l);
    }
}

int main () {
    maxhn* root = create_node(50, NULL);
    append(30);
    append(20);

    append(15);
    append(10);

    append(8);
    append(16);

    append(60);
    append(40);

    pop();
    print(root);

    printf("%d\n", arrnodes[1]->value);
    printf("complete: %d\n", complete_at_this_moment());
    return 0;
}
