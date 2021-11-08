// :]
#include <stdio.h>
#include <stdlib.h>

typedef struct STACK_NODE {
    struct STACK_NODE *next;
    char value;
} stack_node;

stack_node* create_node (char n_value) {
    stack_node* newNode;
    newNode = (stack_node *) calloc(1, sizeof( stack_node ));

    newNode->value = n_value;
    newNode->next = NULL;
    return newNode;
}

void push (char value, stack_node *root) {
    stack_node *auxLastNode = root;
    while (auxLastNode->next != NULL) {
        auxLastNode = auxLastNode->next;
    }
    auxLastNode->next = create_node(value);
}

void print_ (stack_node *root) {
    stack_node *aux = root;
    for (aux; aux != NULL; aux = aux->next) {
        printf("%c", aux->value);
    }
    printf("\n");
}

stack_node* pop (stack_node *root) {
    if ( root->next != NULL ) {
        stack_node* nextNode = root->next;
        free (root);
        return nextNode;
    }
    free (root);
    return NULL;
}

int main () {
    stack_node* root = create_node('!');
    push('r', root);
    push('m', root);
    push('j', root);
    push('d', root);
    push('p', root);
    push('m', root);
    push('m', root);

    root = pop(root);
    root = pop(root);
    root = pop(root);

    print_(root);
    return 0;
}
