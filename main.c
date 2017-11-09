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

char** split(const char* str, const char* s) {
    //char* str = malloc(sizeof(str));
    //char* s = malloc(sizeof(s));
    //memcpy(&str, &str_cp, strlen(str_cp)+1);
    //memcpy(&s, &s_cp, strlen(s_cp)+1);
    char* no_const = malloc(sizeof(str)+10);
    memcpy(no_const, str, strlen(str)+1);
    char* token;
    char** tokens = malloc(sizeof(str));
    int counter = 0;
    /* get the first token */
    token = strtok(no_const, s);

    /* walk through other tokens */
    while( token != NULL ) {
        tokens[counter] = token;
        counter++;
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
    Node* node_tmp = malloc(sizeof(Node) * 10);
    NodeList nodes = {node_tmp, 0};
    nodes.count = 0;
    int counter = 0;

    for (int i = 0; i<lines; i++) {
        nodes.nodes[i] = NullNode;
        nodes.count++;
    }

    if (verbose)
        puts("INPUT");

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '#')
            continue;
        NearNode* neighbors = malloc(sizeof(NearNode) * 20);
        int neighbors_counter = 0;
        //printf("line is %s", line);
        char** neighbors_in = split(split(line, ":")[1], ",");
        //printf("line is now %s\n", line);
        while (neighbors_in[neighbors_counter] != NULL) {
            neighbors[neighbors_counter].name = split(neighbors_in[neighbors_counter], "=")[0];
            neighbors[neighbors_counter].weight = atoi(split(neighbors_in[neighbors_counter], "=")[1]);
            neighbors_counter++;
        }
        nodes.nodes[counter].name = split(line, ":")[0];
        printf("node name is %s", nodes.nodes[counter].name);
        nodes.nodes[counter].length = neighbors_counter;
        nodes.nodes[counter].neighbors = neighbors;
        counter++;
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
    for (int i = 0; i < nodes.count; i++) {
        printf("NODE %s\n", nodes.nodes[i].name);
    }
    return 0;
}
