/*
NODE:NEIGHBOR=WEIGHT,NEIGHBOR2=WEIGHT2
A:B1=2,B2=5,B3=8
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

bool startswith(const char *pre, const char *str) {
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

/* neighbor node */
typedef struct NearNode NearNode;
typedef struct NearNode {
    char* name;
    int weight;
} _nearnode;

typedef struct Node Node;
typedef struct Node {
    char* name;
    int length;
    NearNode* neighbors;
} _node;

int get_lines(char* file) {
    int lines = 0;
    int ch = 0;
    FILE* fp = fopen(file, "r");
    while(!feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n')
            lines++;
    }
    return lines;
}

Node* get_nodes(char* file) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int lines = get_lines(file);
    Node* nodes = malloc(lines * 50);
    Node NullNode;

    for (int i; i<lines; i++) {
        nodes[i] = NullNode;
    }

    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "No such file or directory: '%s'\n", file);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        if (startswith("#", line))
            continue;
        // todo
    }

    fclose(fp);
    if (line)
        free(line);

    return nodes;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <node_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    get_nodes(argv[1]);
    return 0;
}
