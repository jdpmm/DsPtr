# Introduction to data structures

## Stack

```c
typedef struct STACK_NODE {
    struct STACK_NODE *next;
    char value;
} stack_node;
```

The basic struct for a stack

```c
stack_node* create_node (char n_value) {
    stack_node* newNode;
    newNode = (stack_node *) calloc(1, sizeof( stack_node ));

    newNode->value = n_value;
    newNode->next = NULL;
    return newNode;
}
```

create a new node for can make the stack, we need a value for the node, and the pointer to the next node must be NULL at this moment because there's no another node yet.

```C
void push (char value, stack_node *root) {
    stack_node *auxLastNode = root;
    while (auxLastNode->next != NULL) {
        auxLastNode = auxLastNode->next;
    }
    auxLastNode->next = create_node(value);
}
```

We need to know what is the last node can link the new node with the last node at the stack

```c
void print_ (stack_node *root) {
    stack_node *aux = root;
    for (aux; aux != NULL; aux = aux->next) {
        printf("%c", aux->value);
    }
    printf("\n");
}
```

Basically, just we've created an aux, this aux will run through each node and will print his value. But when the aux will be NULL the process must stop because there are no more nodes.

```c
stack_node* pop (stack_node *root) {
    if ( root->next != NULL ) {
        stack_node* nextNode = root->next;
        free (root);
        return nextNode;
    }
    free (root);
    return NULL;
}
```

To can remove a node we need to know if there are nodes... If there are, will create a new node and his value will be the next node of the node to erase, then delete the node to erase with free function

---

## Doubly Linked List

```c
typedef struct Double_linked_list_node {
    struct Double_linked_list_node* next;
    struct Double_linked_list_node* ante;
    char value;
} dl2n;
```

Basic struct

```c
dl2n* create_node (char value){ 
    dl2n* newNode;
    newNode = (dl2n *) calloc(1, sizeof(dl2n));
    newNode->value = value;
    newNode->next = NULL;
    newNode->ante = NULL;

    return newNode;
}
```

create a node with all pointers to NULL

```c
dl2n* last_node (dl2n *headhead) {
    dl2n* lastNode = headhead;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    return lastNode;
}
```

This function is so useful because we need to know what is the last node at the linked list.

```c
void push_n (char value, dl2n *head) {
    dl2n* lastNode = last_node(head);
    lastNode->next = create_node(value);
    lastNode->next->ante = lastNode;
}
```

We gotta search the last node at the Linked List, when we got it we must create a new node, this node will be pointed by the last node at the Linked List.

Something like:

```
[lastnode]-> [newnode]
```

Then, the new node will point to the last node, and it will look something like

```
[lastnode]-> <-[newnode]
```

```c
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
```

We need to find the node to erase, when happening we must sort the linked list:
A: node to erase
B: next node of node to erase
C: before node of node to erase

C must point to B and B must point to C and A must be deleted

---

## Doubly cirucular linked list

Here there is a little issue, yeah, it's a Doubly circular linked list but the last node always will be the last unless to be deleted.

```c
typedef struct DCLL {
    struct DCLL* next;
    struct DCLL* ante;

    struct DCLL* toStart;
    struct DCLL* toEnd;
    int value;
} dc2l;
dc2l* head;
dc2l* last;
```

The basic struct and the head of the ...linked list and the last node of the ...linked list

```c
dc2l* create_node (int value) {
    dc2l *new = (dc2l *) calloc(1, sizeof(dc2l));
    new->next = NULL;
    new->ante = NULL;
    new->toStart = NULL;
    new->toEnd = NULL;
    new->value = value;

    return new;
}
```

Create a new node with all pointer to NULL, again? yeah

```c
void union_hl () {
    head->toEnd = last;
    last->toStart = head;

    head->next = last;
    head->ante = last;

    last->ante = head;
    last->next = head;
}
```

This function link the last and first node between them, it will look something like

```
<-[head]-> <-[last]->
```

```c
dc2l* last_node () {
    dc2l* aux_l = head;
    while (aux_l->next != NULL && aux_l->toStart == NULL) {
        aux_l = aux_l->next;
    }
    return aux_l->ante;
}
```

Returns the last node at the ...linked list

```c
void push_node (int value) {
    dc2l* lastn = last_node();
    lastn->next = create_node(value);
    lastn->next->ante = lastn;

    last->ante = lastn->next;
    lastn->next->next = last;
}
```

Search the last node, when happening will link the new node to the last node towards the right and left (next and ante pointers)

```c
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
```

To delete a node, first, we need to know if exist, if the node to erase exists we to know if the node is the first node or the last at the ...linked list

---

If it's the head we must sort the all ...linked list again because this head will don't exist more, so:
A: head
B: node before to head (last node)
C: next node to head (any node or the last node)

B must point to C as "ante", "next" and "toEnd"
C must point to B as "next", "ante" and "toStart"
A must be deleted

---

A: last node
B: node before to last (any node)
C: next node to head (head)

B must point to C as "next" and "toStart"
C must point to B as "toEnd" and "ante"

---

A: any node
B: node before to A
C: next node to A

B must point to C
C must point to B
