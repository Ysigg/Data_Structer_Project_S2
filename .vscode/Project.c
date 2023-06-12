#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

struct node {
    struct node* children[ALPHABET_SIZE];
    int count;
};

struct node* create_node() {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->count = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        new_node->children[i] = NULL;
    }

    return new_node;
}

// insert tries
void insert(struct node* root, const char* word) {
    struct node* current_node = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        
        if (current_node->children[index] == NULL) {
            current_node->children[index] = create_node();
        }

        current_node = current_node->children[index];
    }

    current_node->count++;
}
