#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void inOrderTraversal(Disc* root) {
    if (root == NULL)
        return;
    
    inOrderTraversal(root->left);
    printf("| %-26s | %-14s | %-5d | %-5s | %-13d |\n", root->title, root->genre, root->releaseYear, root->rate, root->stock);
    printf("+----------------------------+----------------+-------+-------+---------------+\n");
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
	int length = (year);
    if (length < 1900 || length > 2023) {
        return 0;
    }
    return 1;
}

int validateRate(char Rate[]) {
	if (strcmp(Rate, "13+") == 0) {
        return 1;
    }
    else if (strcmp(Rate, "15+") == 0) {
        return 1;
    }
    else if (strcmp(Rate, "17+") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int validateGenre(char genre[]) {
	if (strcmp(genre, "Romance") == 0) {
        return 6;
    }
	if (strcmp(genre, "Fantasy") == 0) {
        return 5;
    }
    if (strcmp(genre, "Action") == 0) {
        return 4;
    }
	else if (strcmp(genre, "Sci-fi") == 0) {
        return 3;
    }
    else if (strcmp(genre, "Adventure") == 0) {
        return 2;
    }
    else if (strcmp(genre, "Comedy") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int validateStock(int stock) {
    return stock >= 1;
}

void importDatabase(Disc** root) {
    char title[51];
    char author[10];
    int releaseYear;
    char rate[5];
    char genre[20];
    int stock;
    
    
	strcpy(title, "Black Mermaid");
	strcpy(author, "Walt Marney");
	releaseYear = 2023;
	strcpy(rate, "15+");
	strcpy(genre, "Adventure");
	stock = 64;
    
    
    Disc* newDisc = createDisc(title, author, releaseYear, rate, genre, stock);
    
    if (*root == NULL) {
        *root = newDisc;
        printf("Insert Success!\n");
        return;
    }
    
    Disc* current = *root;
    Disc* parent = NULL;
    
    while (1) {
        parent = current;
        
        if (strcmp(title, current->title) < 0) {
            current = current->left;
            if (current == NULL) {
                parent->left = newDisc;
                return;
            }
        } else if (strcmp(title, current->title) > 0) {
            current = current->right;
            if (current == NULL) {
                parent->right = newDisc;
        
                return;
            }
        } else {
            printf("Disc with the same title already exists!\n");
            return;
        }
    }
}

void insertDisc(Disc** root) {
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
    
    printf("Input author[Mr. | Mrs.]: ");
    scanf(" %[^\n]", author);
    while (!validateAuthor(author)) {
    	printf("Input author[Mr. | Mrs.]: ");
        scanf(" %[^\n]", author);
    }
    
    printf("Input release Year[1900-2023]: ");
    scanf("%d", &releaseYear);
    getchar();
    while (!validateYear(releaseYear)) {
        printf("Input release Year[1900-2023]: ");
        scanf("%d", &releaseYear);
        getchar();
    }
    
    printf("Input Rate[13+ | 15+ | 17+]: ");
    scanf(" %[^\n]", rate);
    while (!validateRate(rate)) {
        printf("Input Rate[13+ | 15+ | 17+]: ");
        scanf(" %[^\n]", rate);
    }
    
    printf("Input Genre[Action | Sci-fi | Adventure | Comedy | Fantasy | Romance]: ");
    scanf(" %[^\n]", genre);
    while (!validateGenre(genre)) {
        printf("Input Genre[Action | Sci-fi | Adventure | Comedy | Fantasy | Romance]: ");
        scanf(" %[^\n]", genre);
    }
    
    printf("Input Stock[>= 1]: ");
    scanf("%d", &stock);
    getchar();
    while (!validateStock(stock)) {
        printf("Input Stock[>= 1]: ");
        scanf("%d", &stock);
        getchar();
    }
    
    
    Disc* newDisc = createDisc(title, author, releaseYear, rate, genre, stock);
    
    if (*root == NULL) {
        *root = newDisc;
        printf("Insert Success!\n");
        return;
    }
    
    Disc* current = *root;
    Disc* parent = NULL;
    
    while (1) {
        parent = current;
        
        if (strcmp(title, current->title) < 0) {
            current = current->left;
            if (current == NULL) {
                parent->left = newDisc;
                printf("Insert Success!\n");
                return;
            }
        } else if (strcmp(title, current->title) > 0) {
            current = current->right;
            if (current == NULL) {
                parent->right = newDisc;
                printf("Insert Success!\n");
                return;
            }
        } else {
            printf("Disc with the same title already exists!\n");
            return;
        }
    }
    printf("\n\nPress Enter to Continue...");
    getchar();
}

void viewDisc(Disc* root) {
    if (root == NULL) {
        printf("Warehouse is empty!\n");
        return;
    }
    
    printf("+----------------------------+----------------+-------+-------+---------------+\n");
    printf("| Movie Title                | Movie Genre    | Years | R+    | Movie Stock   |\n");
    printf("+----------------------------+----------------+-------+-------+---------------+\n");
    inOrderTraversal(root);
    printf("Press Enter to Continue...");
    getchar();
    getchar();
}

Disc* getSuccessor(Disc* node) {
    Disc* current = node->right;
    Disc* parent = node;
    Disc* successor = node;
    
    while (current != NULL) {
        parent = successor;
        successor = current;
        current = current->left;
    }
    
    if (successor != node->right) {
        parent->left = successor->right;
        successor->right = node->right;
    }
    
    return successor;
}

void deleteDisc(Disc** root) {
    if (*root == NULL) {
        printf("Warehouse is empty!\n");
        return;
    }
    
    char title[51];
    printf("Input Movie title: ");
    scanf(" %[^\n]", title);
    
    Disc* parent = NULL;
    Disc* current = *root;
    int isLeftChild = 0;
    
    while (current != NULL) {
        int comparison = strcmp(title, current->title);
        
        if (comparison == 0) {
            break;
        }
        
        parent = current;
        
        if (comparison < 0) {
            current = current->left;
            isLeftChild = 1;
        } else {
            current = current->right;
            isLeftChild = 0;
        }
    }
    
    if (current == NULL) {
        printf("Disc not found!\n");
        return;
    }
    
    if (current->left == NULL && current->right == NULL) {
        if (current == *root) {
            *root = NULL;
        } else if (isLeftChild) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else if (current->left == NULL) {
        if (current == *root) {
            *root = current->right;
        } else if (isLeftChild) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    } else if (current->right == NULL) {
        if (current == *root) {
            *root = current->left;
        } else if (isLeftChild) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    } else {

        Disc* successor = getSuccessor(current);
        
        if (current == *root) {
            *root = successor;
        } else if (isLeftChild) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        
        successor->left = current->left;
    }
    
    free(current);
    printf("Disc deleted successfully!\n");
    printf("Press Enter to Continue...");
    getchar();
    getchar();
}



void adminMenu(Disc** root) {
    int choice;
    do {
        printf("\n----- Admin Menu -----\n");
        printf("1. Insert Disc\n");
        printf("2. View Disc\n");
        printf("3. Delete Disc\n");
        printf("4. Import from Database\n");
        printf("5. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                insertDisc(root);
                break;
            case 2:
                viewDisc(*root);
                break;
            case 3:
                deleteDisc(root);
                break;
            case 4:
            	importDatabase(root);
                break;
            case 5:
            	return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (1);
}

void userMenu(Disc* root) {
    int choice;
    do {
        printf("\n----- User Menu -----\n");
        printf("1. View Disc\n");
        printf("2. Search Disc\n");
        printf("3. Buy Disc\n");
        printf("4. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
            
                viewDisc(root);
                break;
            case 2:
                // Perform search logic here
                break;
            case 3:
                // Perform buy logic here
                break;
            case 4:
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
                adminMenu(&root);
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
