#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

Node* createNode(char ch, int freq) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void generateCodes(Node *root, char code[], int top) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        code[top] = '\0';
        printf("%c: %s\n", root->ch, code);
        return;
    }

    code[top] = '0';
    generateCodes(root->left, code, top + 1);

    code[top] = '1';
    generateCodes(root->right, code, top + 1);
}

int main() {
    int n;
    scanf("%d", &n);

    Node *nodes[1000];

    for (int i = 0; i < n; i++) {
        char ch;
        int freq;

        scanf(" %c %d", &ch, &freq);
        nodes[i] = createNode(ch, freq);
    }

    int size = n;

    while (size > 1) {
        int min1 = -1, min2 = -1;

        for (int i = 0; i < size; i++) {
            if (min1 == -1 || nodes[i]->freq < nodes[min1]->freq)
                min1 = i;
        }

        Node *left = nodes[min1];
        nodes[min1] = nodes[size - 1];
        size--;

        for (int i = 0; i < size; i++) {
            if (min2 == -1 || nodes[i]->freq < nodes[min2]->freq)
                min2 = i;
        }

        Node *right = nodes[min2];
        nodes[min2] = nodes[size - 1];
        size--;

        Node *parent = createNode('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        nodes[size++] = parent;
    }

    char code[1000];

    if (n == 1) {
        printf("%c: 0\n", nodes[0]->ch);
    } else {
        generateCodes(nodes[0], code, 0);
    }

    return 0;
}