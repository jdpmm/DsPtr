// :]
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BST {
    struct BST* rc;
    struct BST* lc;
    struct BST* parent;

    int value;
} bstn;
bstn* last_parent;

bstn* create_node (int value) {
    bstn* newnode;
    newnode = (bstn*) calloc(1, sizeof(bstn));
    newnode->value = value;
    newnode->lc = NULL;
    newnode->rc = NULL;
    newnode->parent = NULL;

    nodes_created++;
    return newnode;
}

void push (int value, bstn** root) {
    bstn* auxroot = *root;
    if (auxroot == NULL) {
        *root = create_node(value);
        (*root)->parent = last_parent;
    }
    else {
        last_parent = *root;
        if (value < auxroot->value) {
            push(value, &auxroot->lc);
        }
        else {
            push(value, &auxroot->rc);
        }
    }
}

bstn* get_node (int value, bstn* root) {
    if (root == NULL) return NULL;
    if (root->value == value) {
        return root;
    }
    else {
        if (value > root->value) return get_node(value, root->rc);
        else if (value < root->value) return get_node(value, root->lc);
    }
}

bstn* lca (int v, int vv, bstn* root) {
    bstn* a1 = get_node(v, root);
    bstn* a2 = get_node(vv, root);
    if (a1 != NULL && a2 != NULL) {
        bstn* r = NULL;

        while (a1->parent != NULL) {
            while (a1->parent->value < a2->value) {
                if (a2->parent != NULL) {
                    a2 = a2->parent;

                    if (a2->lc->value == a1->parent->value) {
                        r = a2;
                        break;
                    }
                }
                else {
                    break;
                }
            }
            if (a1->parent->value == a2->value) {
                r = a1->parent;
                break;
            }
            a1 = a1->parent;
        }

        return r;
    }
    else {
        printf("The two nodes must exist\n");
        return NULL;
    }
}

int main () {
    bstn* root = create_node(30);
    push(20, &root);
    push(40, &root);
    push(10, &root);
    push(25, &root);
    push(35, &root);
    push(50, &root);

    push(22, &root);
    push(45, &root);
    push(15, &root);

    printf("[left]{10} [root]{%d} [right]{25}\n", lca(10, 25, root)->value);
    printf("[left]{10} [root]{%d} [right]{45}\n", lca(10, 45, root)->value);
    printf("[left]{25} [root]{%d} [right]{35}\n", lca(25, 35, root)->value);
    printf("[left]{15} [root]{%d} [right]{22}\n", lca(15, 22, root)->value);

    return 0;
}
