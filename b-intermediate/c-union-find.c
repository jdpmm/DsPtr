// :]
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct UFN {
    int value;
    struct UFN* parent;
    int nchilds;

    char codechild;
} ufn;

ufn* create_node (int value) {
    ufn* node = (ufn*) calloc(1, sizeof(ufn));
    node->value = value;
    node->parent = node;
    node->nchilds = 0;
    node->codechild = value + 33;

    return node;
}

bool parent_of_itself (ufn* node) {
    return node->parent->value == node->value;
}

void union_nodes (ufn* node1, ufn* node2) {
    ufn* auxnode1 = node1;
    ufn* auxnode2 = node2;
    int newnodes_to_node1 = 1;

    if ( !parent_of_itself(node1) ) {
        while (!parent_of_itself(auxnode1)) {
            auxnode1 = auxnode1->parent;
        }
    }
    if ( !parent_of_itself(node2) ) {
        while (!parent_of_itself(auxnode2)) {
            newnodes_to_node1++;
            auxnode2 = auxnode2->parent;
        }
    }
    
    if ( auxnode2->parent->value != auxnode1->value  ) {
        auxnode2->parent = auxnode1;
        auxnode1->nchilds += newnodes_to_node1;
    }

}

int main () {
    ufn* node1 = create_node(1);
    ufn* node2 = create_node(2);
    ufn* node3 = create_node(3);
    ufn* node4 = create_node(4);
    ufn* node5 = create_node(5);
    ufn* node6 = create_node(6);
    ufn* node7 = create_node(7);
    ufn* node8 = create_node(8);

    union_nodes(node1, node2); // [1] <- [2]
    union_nodes(node3, node4); // [3] <- [4]
    union_nodes(node5, node6); // [5] <- [6]
    union_nodes(node7, node8); // [7] <- [8]

    //  [1]
    //  ^  ^
    // [2] [3]
    //      ^
    //     [4]
    union_nodes(node2, node4);
    union_nodes(node1, node3);

    printf("%d\n", node1->parent->value);
    printf("%d\n", node1->nchilds);


    return 0;
}
