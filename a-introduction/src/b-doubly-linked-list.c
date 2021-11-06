// :]
#include <stdio.h>
#include <stdlib.h>

typedef struct Double_linked_list_node {
    struct Double_linked_list_node* next;
    struct Double_linked_list_node* ante;
    char value;
} dl2n;

dl2n* create_node (char value){ 
    dl2n* newNode;
    newNode = (dl2n *) calloc(1, sizeof(dl2n));
    newNode->value = value;
    newNode->next = NULL;
    newNode->ante = NULL;

    return newNode;
}

dl2n* last_node (dl2n *headhead) {
    dl2n* lastNode = headhead;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    return lastNode;
}

void push_n (char value, dl2n *head) {
    dl2n* lastNode = last_node(head);
    lastNode->next = create_node(value);
    lastNode->next->ante = lastNode;
}

void print_inOrden (dl2n *head) {
    dl2n* auxp = head;
    for (auxp; auxp != NULL; auxp = auxp->next) {
        printf("%c", auxp->value);
    }
    printf("\n");
    free(auxp);
}

void remove_n (char data, dl2n *head) {
    dl2n* searchNode = head;
    while (searchNode->next != NULL) {
        if ( searchNode->value == data ) {
            break;
        }
        searchNode = searchNode->next;
    }

    searchNode->ante->next = searchNode->next;
    searchNode->next->ante = searchNode->ante;
    free (searchNode);
}

void print_inDisorden (dl2n *head) {
    dl2n *lastN = last_node(head);
    for (lastN; lastN != NULL; lastN = lastN->ante) {
        printf("%c", lastN->value);
    }
    printf("\n");
    free (lastN);
}

int main () {
    dl2n* head = create_node('j');
    push_n('d', head);
    push_n('p', head);
    push_n('x', head);
    push_n('m', head);
    push_n('m', head);

    print_inOrden(head);
    remove_n('x', head);
    print_inOrden(head);
    print_inDisorden(head);

    return 0;
}


