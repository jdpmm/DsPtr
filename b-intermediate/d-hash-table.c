// :]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_ARR 100

typedef struct HST {
    char* value;
    char* key;
    struct HST* next;
} hstn;
hstn* hashtable[SIZE_ARR];

int get_token (char *key) {
    int x = 0;
    for (int i = 0; i < strlen(key); ++i) {
        x += key[i];
    }
    return x % SIZE_ARR;
}

hstn* createnode (char* key, char *value) {
    hstn* node = (hstn*) calloc(1, sizeof(hstn));
    node->value = value;
    node->next = NULL;
    node->key = key;

    return node;
}

void push (char* key, char *value) {
    int token = get_token(key);
    if ( hashtable[token] ) {
        hstn* auxhere = hashtable[token];
        while (auxhere->next != NULL) {
            auxhere = auxhere->next;
        }
        auxhere->next = createnode(key, value);
    }
    else {
        hashtable[token] = createnode(key, value);
    }
}

char* get_value (char* key) {
    int token = get_token(key);
    if ( hashtable[token] ) {
        hstn* node = hashtable[token];
        while (node->key != key) {
            node = node->next;
        }
        return node->value;
    }
    return "+no+value+";
}

int main () {
    push("hola", "como estas");
    push("laoh", "como no estas");

    printf("%s\n", get_value("laoh"));
    return 0;
}
