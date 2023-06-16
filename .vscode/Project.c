#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct Disc {
    char title[51];
    char author[10];
    int releaseYear;
    char rate[5];
    char genre[20];
    int stock;
    struct Disc* left;
    struct Disc* right;
};

typedef struct Disc Disc;

struct TrieNode {
    struct TrieNode* children[26];
    int isEndOfWord;
    Disc* disc;
};

typedef struct TrieNode TrieNode;

Disc* createDisc(char title[], char author[], int releaseYear, char rate[], char genre[], int stock) {
    Disc* newDisc = (Disc*)malloc(sizeof(Disc));
    strcpy(newDisc->title, title);
    strcpy(newDisc->author, author);
    newDisc->releaseYear = releaseYear;
    strcpy(newDisc->rate, rate);
    strcpy(newDisc->genre, genre);
    newDisc->stock = stock;
    newDisc->left = NULL;
    newDisc->right = NULL;
    return newDisc;
}

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = 0;
    node->disc = NULL;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}


void insertTitle(TrieNode* root, char title[], Disc* disc) {
    TrieNode* current = root;
    int length = strlen(title);
    for (int i = 0; i < length; i++) {
        int index = title[i] - 'A' && 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
    current->disc = disc;
}

Disc* searchTitle(TrieNode* root, char title[]) {
    TrieNode* current = root;
    int length = strlen(title);
    for (int i = 0; i < length; i++) {
        int index = title[i] - 'A' && 'a';
        if (current->children[index] == NULL) {
            return NULL;
        }
        current = current->children[index];
    }
    if (current != NULL && current->isEndOfWord) {
        return current->disc;
    }
    return NULL;
}

int countDiscs(Disc* root) {
    if (root == NULL)
        return 0;
    
    int count = 1; // Count the current disc
    
    // Recursively count discs in the left and right subtrees
    count += countDiscs(root->left);
    count += countDiscs(root->right);
    
    return count;
}

// Function to compare two strings alphabetically
int compareStrings(const void* a, const void* b) {
    const Disc* disc1 = *(const Disc**)a;
    const Disc* disc2 = *(const Disc**)b;

    return strcmp(disc1->title, disc2->title);
}

// Function to create an array of Disc pointers
void createDiscArray(Disc* root, Disc** discArray, int* index) {
    if (root == NULL)
        return;

    createDiscArray(root->left, discArray, index);
    discArray[*index] = root;
    (*index)++;
    createDiscArray(root->right, discArray, index);
}

// Function to display discs based on alphabetical order of titles
void displayInventory(Disc* root) {
    if (root == NULL) {
        printf("Inventory is empty!\n");
        return;
    }

    int discCount = countDiscs(root);
    Disc** discArray = (Disc**)malloc(discCount * sizeof(Disc*));

    int index = 0;
    createDiscArray(root, discArray, &index);

    qsort(discArray, discCount, sizeof(Disc*), compareStrings);

    printf("+----------------------------+----------------+-------+-------+---------------+\n");
    printf("| Movie Title                | Movie Genre    | Years | R+    | Movie Stock   |\n");
    printf("+----------------------------+----------------+-------+-------+---------------+\n");

    for (int i = 0; i < discCount; i++) {
        Disc* disc = discArray[i];
        printf("| %-26s | %-14s | %-5d | %-5s | %-13d |\n", disc->title, disc->genre, disc->releaseYear, disc->rate, disc->stock);
    }

    printf("+----------------------------+----------------+-------+-------+---------------+\n");

    free(discArray);
}

// Function to swap two Disc pointers
void swapDiscs(Disc** disc1, Disc** disc2) {
    Disc* temp = *disc1;
    *disc1 = *disc2;
    *disc2 = temp;
}

void heapify(Disc** discArray, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && discArray[left]->stock < discArray[smallest]->stock)
        smallest = left;

    if (right < n && discArray[right]->stock < discArray[smallest]->stock)
        smallest = right;

    if (smallest != i) {
        Disc* temp = discArray[i];
        discArray[i] = discArray[smallest];
        discArray[smallest] = temp;

        heapify(discArray, n, smallest);
    }
}

void buildHeap(Disc** discArray, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(discArray, n, i);
}

void displayInventoryWithHeap(Disc* root) {
    if (root == NULL) {
        printf("Inventory is empty!\n");
        return;
    }

    int discCount = countDiscs(root);
    Disc** discArray = (Disc**)malloc(discCount * sizeof(Disc*));

    int index = 0;
    createDiscArray(root, discArray, &index);

    buildHeap(discArray, discCount);

    printf("+----------------------------+----------------+-------+-------+---------------+\n");
    printf("| Movie Title                | Movie Genre    | Years | R+    | Movie Stock   |\n");
    printf("+----------------------------+----------------+-------+-------+---------------+\n");

    for (int i = 0; i < discCount; i++) {
        Disc* disc = discArray[i];
        printf("| %-26s | %-14s | %-5d | %-5s | %-13d |\n", disc->title, disc->genre, disc->releaseYear, disc->rate, disc->stock);
    }

    printf("+----------------------------+----------------+-------+-------+---------------+\n");

    free(discArray);
}


int validateAuthor(char author[]) {
    int length = strlen(author);
    if (length < 5 || length > 25) {
        return 0;
    }
    if (strncmp(author, "Mr. ", 4) != 0 && strncmp(author, "Mrs. ", 5) != 0) {
        return 0;
    }
    return 1;
}

int validateYear(int year) {
    if (year < 1900 || year > 2023) {
        return 0;
    }
    return 1;
}

int validateRate(char Rate[]) {
    if (strcmp(Rate, "G") != 0 && strcmp(Rate, "PG") != 0 && strcmp(Rate, "PG-13") != 0 && strcmp(Rate, "R") != 0) {
        return 0;
    }
    return 1;
}

int validateGenre(char genre[]) {
    if (strcmp(genre, "Action") != 0 && strcmp(genre, "Adventure") != 0 && strcmp(genre, "Comedy") != 0 && strcmp(genre, "Drama") != 0 && strcmp(genre, "Horror") != 0) {
        return 0;
    }
    return 1;
}

int validateStock(int stock) {
    return stock >= 1;
}

void addDisc(Disc** root, TrieNode* trieRoot) {
    char title[51];
    char author[10];
    int releaseYear;
    char rate[5];
    char genre[20];
    int stock;

    fgets(title, 51, stdin);
	title[strcspn(title, "\n")] = 0;	
	while (strlen(title) < 5 || strlen(title) > 50) {
		printf("Input game title[5-25][unique]: ");
		fgets(title,50, stdin);
	    title[strcspn(title, "\n")] = 0;	
	}

    printf("Enter the author of the disc (Mr./Mrs. <name>): ");
    scanf(" %[^\n]s", author);

   	while (!validateAuthor(author)) {
        printf("Invalid author format. Author must be in the format 'Mr./Mrs. <name>' and have a length between 5 and 25 characters.\n");
        printf("\nEnter the author of the disc (Mr./Mrs. <name>): ");
    	scanf(" %[^\n]s", author);
    }

    printf("Enter the release year of the disc (between 1900 and 2023): ");
    scanf("%d", &releaseYear);

    while (!validateYear(releaseYear)) {
        printf("Invalid release year. Year must be between 1900 and 2023.\n");
        printf("\nEnter the release year of the disc: ");
    	scanf("%d", &releaseYear);
    }

    printf("Enter the rate of the disc (G, PG, PG-13, R): ");
    scanf(" %[^\n]s", rate);

    while (!validateRate(rate)) {
        printf("Invalid rate. Rate must be 'G', 'PG', 'PG-13', or 'R'.\n");
        printf("\nEnter the rate of the disc (G, PG, PG-13, R): ");
    	scanf(" %[^\n]s", rate);
    }

    printf("Enter the genre of the disc (Action, Adventure, Comedy, Drama, Horror): ");
    scanf(" %[^\n]s", genre);

    while (!validateGenre(genre)) {
        printf("Invalid genre. Genre must be 'Action', 'Adventure', 'Comedy', 'Drama', or 'Horror'.\n");
        printf("Enter the genre of the disc (Action, Adventure, Comedy, Drama, Horror): ");
    	scanf(" %[^\n]s", genre);
    }

    printf("Enter the stock of the disc[>= 1]: ");
    scanf("%d", &stock);
    while (!validateStock(stock)) {
    	printf("Enter the stock of the disc[>= 1]: ");
    	scanf("%d", &stock);
    }

    Disc* newDisc = createDisc(title, author, releaseYear, rate, genre, stock);
    insertTitle(trieRoot, title, newDisc);

    if (*root == NULL) {
        *root = newDisc;
    } else {
        Disc* current = *root;
        Disc* parent = NULL;
        while (current != NULL) {
            parent = current;
            if (strcmp(title, current->title) < 0) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (strcmp(title, parent->title) < 0) {
            parent->left = newDisc;
        } else {
            parent->right = newDisc;
        }
    }
    printf("Disc added successfully.\n");
}

void searchDisc(TrieNode* trieRoot) {
    char title[51];

    printf("Enter the title of the disc: ");
    scanf(" %[^\n]s", title);

    Disc* disc = searchTitle(trieRoot, title);
    if (disc != NULL) {
        printf("\nDisc found:\n");
        printf("+----------------------------+----------------+-------+-------+---------------+\n");
        printf("|           Title            |     Genre      | Year  | Rate  |     Stock     |\n");
        printf("+----------------------------+----------------+-------+-------+---------------+\n");
        printf("| %-26s | %-14s | %-5d | %-5s | %-13d |\n", disc->title, disc->genre, disc->releaseYear, disc->rate, disc->stock);
        printf("+----------------------------+----------------+-------+-------+---------------+\n");
    } else {
        printf("Disc not found.\n");
    }
}

//void updateStock(AVLTree* tree) {
//    if (tree->root == NULL) {
//        printf("Warehouse is empty !\n");
//        printf("\nPress Enter to Continue...");
//        getchar();
//        getchar();
//        return;
//    }
//
//    char title[26], type[10];
//    int quantity;
//
//    printf("Input game title: ");
//    scanf(" %[^\n]", title);
//
//    Data* game = searchGame(tree, title);
//    if (game == NULL) {
//        return;
//    }
//    printf("Current stock: %d\n", game->GStock);
//
//    printf("Input update type[add|remove][case insensitive]: ");
//    scanf(" %[^\n]", type);
//    while (strcasecmp(type, "add") != 0 && strcasecmp(type, "remove") != 0) {
//        printf("Invalid update type. Input update type [add|remove] (case insensitive): ");
//        scanf(" %[^\n]", type);
//    }
//
//    if (strcasecmp(type, "add") == 0) {
//        printf("Input game stock to add [>= 1]: ");
//        scanf("%d", &quantity);
//        while (!validateStock(quantity)) {
//            printf("Input game stock to add [>= 1]: ");
//            scanf("%d", &quantity);
//        }
//        game->GStock += quantity;
//    } else {
//        printf("Input game stock to remove [1-%d]: ", game->GStock);
//        scanf("%d", &quantity);
//        while (quantity < 1 || quantity > game->GStock) {
//            printf("Input game stock to remove [1-%d]: ", game->GStock);
//            scanf("%d", &quantity);
//        }
//        game->GStock -= quantity;
//        if (game->GStock == 0) {
//        }
//    }
//
//    printf("Data updated successfully!\n");
//    if (game->GStock == 0) {
//        printf("%s is removed from the warehouse!\n", game->GTitle);
//    }
//    printf("\nPress Enter to Continue...");
//    getchar();
//    getchar();
//}

int deleteDisc(Disc** root, TrieNode* trieRoot) {
	if (*root == NULL) {
        printf("Invetory is empty !\n");
        printf("\nPress Enter to Continue...");
        getchar();
        return 1;
    }
    char title[51];

    printf("Enter the title of the disc to delete: ");
    scanf(" %[^\n]s", title);

    Disc* disc = searchTitle(trieRoot, title);
    if (disc != NULL) {
        // Delete from the binary search tree
        Disc* current = *root;
        Disc* parent = NULL;
        while (current != NULL) {
            if (strcmp(title, current->title) == 0) {
                if (parent == NULL) {
                    *root = NULL;
                } else if (parent->left == current) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
                free(current);
                current = NULL;
                break;
            } else if (strcmp(title, current->title) < 0) {
                parent = current;
                current = current->left;
            } else {
                parent = current;
                current = current->right;
            }
        }

        // Delete from the trie
        TrieNode* currentTrie = trieRoot;
        int length = strlen(title);
        for (int i = 0; i < length; i++) {
            int index = title[i] - 'A' && 'a';
            currentTrie = currentTrie->children[index];
        }
        currentTrie->isEndOfWord = 0;
        currentTrie->disc = NULL;

        printf("Disc '%s' deleted successfully.\n", title);
        return 1;
    } else {
        printf("Disc '%s' not found.\n", title);
        return 0;
    }
}



void adminMenu(Disc* root) {
    TrieNode* trieRoot = createNode();

	char input[10];
    int choice;
    do {
        printf("\n--- Disc Management System ---\n");
        printf("1. Add a Disc\n");
        printf("2. Display Discs (in alphabet)\n");
        printf("3. Display Discs (in stock)\n");
        printf("4. Search\n");
        printf("5. Delete Discs\n");
        printf("6. Back..\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addDisc(&root, trieRoot);
	            getchar();
                break;
            case 2:
                displayInventory(root);
                break;
            case 3:
                displayInventoryWithHeap(root);
                break;
            case 4:
                searchDisc(trieRoot);
                break;
            case 5:
                deleteDisc(&root, trieRoot);
	            getchar();
                break;
            case 6:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice\n");
        }
	}while (1);
}

void userMenu(Disc* root) {
	TrieNode* trieRoot = createNode();
    int choice;
    do {
        printf("\n----- User Menu -----\n");
        printf("1. View Discs (in alphabet)\n");
        printf("2. View Discs (in stock)\n");
        printf("3. Search Disc\n");
        printf("4. Buy Disc\n");
        printf("5. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                displayInventory(root);
                break;
            case 2:
                displayInventoryWithHeap(root);
                break;
            case 3:
                searchDisc(trieRoot);
                break;
            case 4:
                // Perform buy logic here
                break;
            case 5:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (1);
}

int main() {
    Disc* root = NULL;
    int choice;
    
    do {
        printf("----- Main Menu -----\n");
        printf("1. Login as Admin\n");
        printf("2. Login as User\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                // Perform admin login logic here
                adminMenu(root);
                break;
            case 2:
                userMenu(root);
                break;
            case 3:
                printf("Terminating the program...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (1);
    
    return 0;
}
