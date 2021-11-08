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
            printf("PUSHING: [newnode]{%d} < [parent]{%d}\n", value, auxroot->value);
            push(value, &auxroot->lc);
        }
        else {
            printf("PUSHING: [newnode]{%d} > [parent]{%d}\n", value, auxroot->value);
            push(value, &auxroot->rc);
        }
    }
}

bstn* find (int value, bstn* root) {
    if (root == NULL) return NULL;
    else if (root->value == value) {
        return root;
    }
    else {
        if (value > root->value) find(value, root->rc);
        else if (value < root->value) find(value, root->lc);
    }
}

int childs (bstn *root) {
    bool left = root->lc == NULL ? false : true;
    bool right = root->rc == NULL ? false : true;

    if (left && right) return 2;
    if (!left && !right) return 0;
    return 1;
}

bstn* last_inorden (bstn** node) {
    bstn* auxio = (*node)->rc;
    while (auxio->lc != NULL) {
        auxio = auxio->lc;
    }
    return auxio;
}

void delete (int value, bstn *root) {
    bstn* to_rm = find(value, root);
    if (to_rm != NULL) {
        int childscount = childs(to_rm);

        if (childscount == 0) {
            if (value < to_rm->parent->value) {
                to_rm->parent->lc = NULL;
            }
            else {
                to_rm->parent->rc = NULL;
            }
            free (to_rm);
        }
        else if (childscount == 1) {
            if (value < to_rm->parent->value) {
                if (to_rm->lc != NULL) to_rm->parent->lc = to_rm->lc;
                else to_rm->parent->lc = to_rm->rc;
            }
            else {
                if (to_rm->lc != NULL) to_rm->parent->rc = to_rm->lc;
                else to_rm->parent->rc = to_rm->rc;
            }
            free(to_rm);
        }

        else if (childscount == 2) {
            bstn* last__ = last_inorden(&to_rm);
            to_rm->value = last__->value;
            last__->parent->lc = NULL;
            free (last__);
        }
    }
    else {
        printf("Node with %d as value doesn't exists\n", value);
    }
}

void pre_order (bstn* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        pre_order(root->lc);
        pre_order(root->rc);
    }
}

void in_order (bstn* root) {
    if (root != NULL) {
        in_order(root->lc);
        printf("%d ", root->value);
        in_order(root->rc);
    }
}

void post_order (bstn* root) {
    if (root != NULL) {
        post_order(root->lc);
        post_order(root->rc);
        printf("%d ", root->value);
    }
}

void print (bstn* root) {
    if (root != NULL) {
        if (root->parent == NULL) {
            printf("ROOT: %d\n", root->value);
        }

        printf("     %d\n", root->value);
        printf("   /    \\");

        if (root->lc != NULL) {
            printf("\n[%d]", root->lc->value);
        }
        else {
            printf("\nNULL");
        }

        if (root->rc != NULL) {
            printf("\t[%d]\n\n", root->rc->value);
        }
        else {
            printf("\tNULL\n\n");
        }

        print(root->lc);
        print(root->rc);
    }
}

int main () {
    bstn *root = create_node(7);
    push(20, &root);
    push(5, &root);
    push(15, &root);
    push(10, &root);
    push(4, &root);
    push(33, &root);
    push(2, &root);
    push(25, &root);
    push(6, &root);

    pre_order(root);
    printf("\n");
    in_order(root);
    printf("\n");
    post_order(root);
    printf("\n");

    print(root);
    printf("\n");

    delete(2, root);
    delete(15, root);
    delete(20, root);

    printf("--------------\n");
    print(root);
    printf("\n");

    return 0;
}
