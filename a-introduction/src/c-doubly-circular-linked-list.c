// :]
#include <stdio.h>
#include <stdlib.h>

typedef struct DCLL {
    struct DCLL* next;
    struct DCLL* ante;

    struct DCLL* toStart;
    struct DCLL* toEnd;
    int value;
} dc2l;
dc2l* head;
dc2l* last;

dc2l* create_node (int value) {
    dc2l *new = (dc2l *) calloc(1, sizeof(dc2l));
    new->next = NULL;
    new->ante = NULL;
    new->toStart = NULL;
    new->toEnd = NULL;
    new->value = value;

    return new;
}

void union_hl () {
    head->toEnd = last;
    last->toStart = head;

    head->next = last;
    head->ante = last;

    last->ante = head;
    last->next = head;
}

dc2l* last_node () {
    dc2l* aux_l = head;
    while (aux_l->next != NULL && aux_l->toStart == NULL) {
        aux_l = aux_l->next;
    }
    return aux_l->ante;
}

void push_node (int value) {
    dc2l* lastn = last_node();
    lastn->next = create_node(value);
    lastn->next->ante = lastn;

    last->ante = lastn->next;
    lastn->next->next = last;
}

void print () {
    dc2l *auxprint = head;
    while (auxprint->value != last->value) {
        printf("%d, ", auxprint->value);
        auxprint = auxprint->next;
    }
    printf("%d\n", auxprint->value);
}

void rmnode (int value) {
    dc2l* searchnode = head;
    while (searchnode->value != value) {
        searchnode = searchnode->next;
    }

    // head
    if ( searchnode->toEnd != NULL ) {
        searchnode->next->toEnd = last;
        last->toStart = searchnode->next;
        last->next = searchnode->next;
        searchnode->next->ante = last;
        head = searchnode->next;
        free (searchnode);
    }
    // last
    else if ( searchnode->toStart != NULL  ) {
        searchnode->ante->toStart = head;
        head->toEnd = searchnode->ante;
        searchnode->ante->next = head;
        head->ante = searchnode->ante;
        last = searchnode->ante;
        free (searchnode);
    }
    else {
        searchnode->ante->next = searchnode->next;
        searchnode->next->ante = searchnode->ante;
        free (searchnode);
    }
}

int main () {
    head = create_node(1);
    last = create_node(2);
    union_hl();
    push_node(3);
    push_node(4);

    print();

    rmnode(1);
    rmnode(2);
    push_node(16);
    rmnode(16);
    rmnode(4);
    print();

    return 0;
}
