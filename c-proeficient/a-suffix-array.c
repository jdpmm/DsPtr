// :]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct SUF2A {
    char* value;
    int idx;
} san;

char* substr (char* str_, int i, int j) {
    char* newstr = (char*) calloc(j + 1, sizeof(char));
    newstr[j] = '\0';
    strncpy(newstr, str_ + i, j);

    return newstr;
}

san create_ (char* value, int idx) {
    san newnode;
    newnode.value = value;
    newnode.idx = idx;

    return newnode;
}

void sort (san* arr, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if ( strcmp( arr[i].value, arr[j].value ) < 0 ) {
                san aux = arr[j];
                arr[j] = arr[i];
                arr[i] = aux;
            }
        }
    }
}

void make (char* msg) {
    int len = strlen(msg);
    san sarray[len];

    for (int i = 0; i < len; ++i) {
        sarray[i] = create_( substr(msg, i, len), i+1 );
    }
    sort(sarray, len);

    for (int i = 0; i < len; ++i) {
        printf("%d : %s\n", sarray[i].idx, sarray[i].value);
    }
}

int main () {
    char* msg1 = "GCATCGC";
    char* msg2 = "banana$";
    make(msg1);

    return 0;
}

