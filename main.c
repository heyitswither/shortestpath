/*
NODE:NEIGHBOR=WEIGHT,NEIGHBOR2=WEIGHT2
A:B1=2,B2=5,B3=8
*/

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

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

/* makes a node with arbitrary data */
Node make_nullnode() {
    NearNode* neighbors = malloc(sizeof(NearNode));
    neighbors[0] = (struct NearNode) {"NearNULL", 1};
    Node node = {"NULL", 1, neighbors};
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

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '#')
            continue;
        printf("%s", line);
    }

    fclose(fp);
    return nodes;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <node_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    NodeList nodes = get_nodes(argv[1]);
    nodes.nodes[0].name = "A";
    nodes.nodes[1].name = "B";
    nodes.count = 2;
    printf("node length %d\n", nodes.count);
    for (int i = 0; i <= nodes.count; i++) {
        printf("NODE %s\n", nodes.nodes[i].name);
    }
    return 0;
}
