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


typedef struct NodeList NodeList;
typedef struct NodeList {
    Node* nodes;
    int count;
} _nodelist;

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

NearNode make_nearnode(char* name, int weight) {
    NearNode node = {};
    node.name = name;
    node.weight = weight;
    return node;
}

Node make_node(char* name, int length, NearNode* neighbors) {
    Node node = {};
    node.name = name;
    node.length = length;
    node.neighbors = neighbors;
    return node;
}

Node make_nullnode() {
    NearNode* neighbors = malloc(sizeof(NearNode));
    neighbors[0] = make_nearnode("NearNULL", 1);
    Node node = make_node("NULL", 1, neighbors);
    return node;
}

NodeList get_nodes(char* file) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int lines = get_lines(file);
    Node NullNode = make_nullnode();
    NearNode* neighbors = malloc(sizeof(NearNode) * 10);
    neighbors[0] = make_nearnode("B", 2);
    NodeList nodes = {}; //malloc(sizeof(Node) * 10);;
    nodes.nodes[0] = make_node("A", 1, neighbors);
    nodes.count = 1;

    for (int i = 0; i<lines; i++) {
        nodes.nodes[i] = NullNode;
        nodes.count++;
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
    NodeList nodes = get_nodes(argv[1]);
    nodes.nodes[0].name = "A";
    nodes.nodes[1].name = "B";
    nodes.count = 2;
    printf("node length %d\n", nodes.count);
    for (int i = -1; i <= nodes.count; i++) {
        printf("NODE %s", nodes.nodes[i].name);
    }
    return 0;
}
