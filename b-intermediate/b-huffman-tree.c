// :]
#include <stdio.h>
#include <stdlib.h>

typedef struct HMT {
    char value;
    unsigned int fi;
    struct HMT* l;
    struct HMT* r;
    struct HMT* p;

    char* code;
} hmTn;

hmTn* make_tree_node (char value, int freq, hmTn* parent) {
    hmTn* newN = (hmTn *) calloc(1, sizeof(hmTn));
    newN->value = value;
    newN->fi = freq;
    newN->l = NULL;
    newN->r = NULL;
    newN->p = parent;


    return newN;
}

void set_nodes (hmTn** nodes_b, int size, char values[], int freq[]) {
    for (int i = 0; i < size; ++i) {
        nodes_b[i] = make_tree_node( values[i], freq[i], NULL );
    }
}

hmTn* make_tree (hmTn **nodes_b, int from, hmTn *helpern, int sizenodesbase) {
    if (helpern == NULL) {
        int addBnodes = nodes_b[from]->fi + nodes_b[from + 1]->fi;
        hmTn* newnode = make_tree_node('*', addBnodes, NULL); // ab at this moment
        newnode->l = nodes_b[from];
        newnode->r = nodes_b[from + 1];

        nodes_b[from]->p = newnode;
        nodes_b[from + 1]->p = newnode;

        return make_tree(nodes_b, from + 2, newnode, sizenodesbase);
    }
    else {
        int addBnodes = helpern->fi + nodes_b[from]->fi;
        hmTn* newhelpern = make_tree_node('*', addBnodes, NULL);
        newhelpern->l = helpern;
        newhelpern->r = nodes_b[from];

        helpern->p = newhelpern;
        nodes_b[from]->p = newhelpern;

        if ( (from + 1) == sizenodesbase ) {
            return newhelpern;
        }
        else {
            return make_tree(nodes_b, from + 1, newhelpern, sizenodesbase);
        }
    }
}

void set_codes (hmTn* root, hmTn** nodesbase, int size) {
    for (int i = 0; i < size; ++i) {
        hmTn* auxp = root;
        char* code = calloc(size, sizeof(char));
        int codeidx = 0;

        while (auxp != NULL) {
            if (auxp->r != NULL) {
                if (auxp->r->value == nodesbase[i]->value) {
                    code[codeidx] = '0';
                    nodesbase[i]->code = code;
                    break;
                }
            }
            if (auxp->value == nodesbase[i]->value) {
                code[codeidx] = '1';
                nodesbase[i]->code = code;
                break;
            }
            else {
                code[codeidx] = '1';
            }

            codeidx++;
            auxp = auxp->l;
        }
    }
}

void print (hmTn** nodesbase, int size) {
    for (int node = 0; node < size; ++node) {
        printf("%c :: %s\n", nodesbase[node]->value, nodesbase[node]->code);
    }
}

int main () {
    char msg1[] = {'a', 'b', 'c', 'd', 'e'};
    int msg1f[] = {3, 2, 6, 8, 10};
    int size_ = sizeof(msg1) / sizeof(msg1[0]);
    hmTn* nodesbase[size_];

    set_nodes(nodesbase, size_, msg1, msg1f);
    hmTn* root = make_tree(nodesbase, 0, NULL, size_);
    set_codes(root, nodesbase, size_);


    print(nodesbase, size_);
    

    return 0;
}
