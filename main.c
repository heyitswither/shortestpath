/*
NODE:NEIGHBOR=WEIGHT,NEIGHBOR2=WEIGHT2
A:B1=2,B2=5,B3=8
*/

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#ifndef LINE_MAX
#define LINE_MAX 2048
#endif

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

/* basically just an array of nodes with a count */
typedef struct NodeList NodeList;
typedef struct NodeList {
    Node* nodes;
    int count;
} _nodelist;

/* gets line count of `file` */
int get_lines(char* file) {
    FILE* fp = fopen(file, "r");;
    if (fp == NULL) {
        fprintf(stderr, "No such file or directory: '%s'\n", file);
        exit(EXIT_FAILURE);
    }

    int lines = 0;
    char line[LINE_MAX];
    while (fgets(line, sizeof(line), fp)) {
        if(line[0] == '#')
            continue;
        lines++;
    }
    return lines;
}

char** split(char* str, char* s) {
    char* token;
    char** tokens = malloc(sizeof(char) * 20);
    int counter = 0;
    /* get the first token */
    token = strtok(str, s);

    /* walk through other tokens */
    while( token != NULL ) {
        tokens[counter] = token;
        counter++;
        printf( " %s\n", token );
        token = strtok(NULL, s);
    }

   return tokens;
}

/* makes a node with arbitrary data */
Node make_nullnode() {
    NearNode* neighbors = malloc(sizeof(NearNode));
    neighbors[0] = (struct NearNode) {"Near No Data", 1};
    Node node = {"No Data", 1, neighbors};
    return node;
}

/* returns a NodeList defined in `file` */
NodeList get_nodes(char* file, bool verbose) {
    FILE* fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "No such file or directory: '%s'\n", file);
        exit(EXIT_FAILURE);
    }

    int lines = get_lines(file);
    char line[LINE_MAX];
    Node NullNode = make_nullnode();
    NearNode* neighbors = malloc(sizeof(NearNode) * 10);
    neighbors[0] = (struct NearNode) {"B", 2};
    Node* node_tmp = malloc(sizeof(Node) * 10);
    node_tmp[0] = NullNode;
    NodeList nodes = {node_tmp, 0};
    nodes.nodes[0] = (struct Node) {"A", 1, neighbors};
    nodes.count = 1;

    for (int i = 0; i<lines; i++) {
        nodes.nodes[i] = NullNode;
        nodes.count++;
    }

    if (verbose)
        puts("INPUT");

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '#')
            continue;
        if (verbose) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return nodes;
}

int main(int argc, char** argv) {
    int file_index = 1;
    bool isVerbose = false;
    if (((argc != 2) && (argc != 3)) || ((argc == 2) && argv[1][0] == '-')) {
        fprintf(stderr, "Usage: %s [-V] <file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argv[1][0] == '-') {
        file_index = 2;
        if (argv[1][1] == 'V') {
            isVerbose = true;
        } else {
            if ((argv[1][1] != 'h') || (argv[1][1] != '?'))
                fprintf(stderr, "Unknown option: '%c'\n", argv[1][1]);
            fprintf(stderr, "Usage: %s [-V] <file>\n", argv[0]);
            return EXIT_FAILURE;
        }
    }
    NodeList nodes = get_nodes(argv[file_index], isVerbose);
    puts("\nDEBUG");
    printf("node length %d\n", nodes.count);
    for (int i = 0; i <= nodes.count; i++) {
        printf("NODE %s\n", nodes.nodes[i].name);
    }
    return 0;
}
