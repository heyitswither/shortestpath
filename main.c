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

/* converts a string to an integer */
int strtoi(char* str_cp) {
    if (str_cp == NULL) {
        return 0;
    }
    char* str = malloc(sizeof(str_cp)+1);
    memcpy(str, str_cp, strlen(str_cp)+1);
    strtok(str, "\n");
    int ret = 0;
    sscanf(str, "%d", &ret);
    return ret;
}

char** split(const char* str, const char* s) {
    char** tokens = malloc(sizeof(str)+1);
    if (strcmp(str, s) == 0) {
        return tokens;
    }
    char* no_const = malloc(sizeof(str)+1);
    memcpy(no_const, str, strlen(str)+1);
    char* token = malloc(sizeof(str));
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
NodeList get_nodes(char* file) {
    FILE* fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "No such file or directory: '%s'\n", file);
        exit(EXIT_FAILURE);
    }

    int lines = get_lines(file);
    char line[LINE_MAX];
    Node NullNode = make_nullnode();
    Node* node_tmp = malloc(sizeof(Node) * 20);
    NodeList nodes = {node_tmp, 0};
    int counter = 0;

    for (int i = 0; i<lines; i++) {
        nodes.nodes[i] = NullNode;
        nodes.count++;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '#')
            continue;
        NearNode* neighbors = malloc(sizeof(NearNode) * 20);
        int neighbors_counter = 0;
        char** neighbors_in = split(split(line, ":")[1], ",");
        while (neighbors_in[neighbors_counter] != NULL) {
            char* name_tmp = split(neighbors_in[neighbors_counter], "=")[0];
            if (strcmp(name_tmp, "\n") == 0)
                break;
            neighbors[neighbors_counter].name = name_tmp;
            neighbors[neighbors_counter].weight = strtoi(split(neighbors_in[neighbors_counter], "=")[1]);
            neighbors_counter++;
        }
        nodes.nodes[counter].name = split(line, ":")[0];
        nodes.nodes[counter].length = neighbors_counter;
        nodes.nodes[counter].neighbors = neighbors;

        counter++;
    }

    fclose(fp);

    return nodes;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stdout, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    NodeList nodes = get_nodes(argv[1]);
    puts("\nDEBUG");
    printf("node length %d\n", nodes.count);
    for (int i = 0; i < nodes.count; i++) {
        if (i == 0)
            printf("First ");
        if (i == nodes.count - 1)
            printf("Last ");
        printf("NODE %s\n", nodes.nodes[i].name);
        int counter = 0;
        NearNode* tmp_near = &nodes.nodes[i].neighbors[counter];
        while (counter < nodes.nodes[i].length) {
            printf("\tNEAR %s: %d\n", tmp_near->name, tmp_near->weight);
            counter++;
            tmp_near = &nodes.nodes[i].neighbors[counter];
        }
    }
    return 0;
}
