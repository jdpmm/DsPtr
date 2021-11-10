#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCHARS 187
#define FROM 65
#define WHEREASCII(x) x - FROM

typedef struct TrieN {
    char value;
    struct TrieN* childs[NCHARS];
} tn;
char* strfindh;

tn* createnode (char valueue) {
    tn* newnode = (tn*) calloc(1, sizeof(tn));
    newnode->value = valueue;
    for (int i = 0; i < NCHARS; ++i) {
        newnode->childs[i] = NULL;
    }
    return newnode;
}

void append (char* msg, tn* root, int from) {
    if ( from == strlen(msg) ) {
        return;
    }

    int whereascii = WHEREASCII(msg[from]);
    if ( !root->childs[whereascii] ) {
        root->childs[whereascii] = createnode(msg[from]);
        append(msg, root->childs[whereascii], from+1);
    }
    else {
        append(msg, root->childs[whereascii], from+1);
    }
}

void find (char* word, tn* root, int from) {
    if (from >= strlen(word)) {
        if (strfindh != word) {
            printf("%s exists\n", word);
        }
        return;
    }

    int wa = WHEREASCII(word[from]);
    if (root->childs[wa]) {
        strfindh[from] = word[from];
        find(word, root->childs[wa], from + 1);
    }
    else {
        printf("%s doesn't exists\n", word);
    }
}

int main () {
    strfindh = (char*) calloc(NCHARS, sizeof(char));
    tn* root = createnode('*');
    append("hola", root, 0);
    append("horas", root, 0);
    append("oso", root, 0);
    append("horno", root, 0);
    append("jonh", root, 0);
    append("juan", root, 0);

    find("horitas", root, 0);
    find("juan", root, 0);
    find("jonh", root, 0);
    return 0;
}

