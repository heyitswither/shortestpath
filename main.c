/*
NODE:NEIGHBOR=WEIGHT,NEIGHBOR2=WEIGHT2
A:B1=2,B2=5,B3=8
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool startswith(const char *pre, const char *str) {
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

typedef struct Node Node;
typedef struct Node {
    char* name;
    int weight;
    int length;
    Node* neighbors;
};

Node* get_nodes(char* file) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    Node* nodes;
  
    fp = fopen(file, "r");
    if (fp == NULL)
        fprintf(stderr, "No such file or directory: '%s'\n", file);
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if (
    }

    fclose(fp);
    if (line)
        free(line);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <node_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    get_nodes(argv[1]);
    return 0;
}
