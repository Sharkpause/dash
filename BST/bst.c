#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define WHITE "\033[0;37m"
#define CYAN "\033[0;36m"

typedef struct Node {
	int value;
	struct Node* left;
	struct Node* right;
} Node;

Node* createNode(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->left = NULL;
	node->right = NULL;

	return node;
}

Node* insert(int value, Node* root) {
	if(root == NULL) {
		return createNode(value);
	} else if(value < root->value) {
		root->left = insert(value, root->left);
	} else if(value > root->value) {
		root->right = insert(value, root->right);
	}

	return root;
}

void inorder(Node* root) {
	if(root == NULL) return;
	if(root->left != NULL) inorder(root->left);
	printf("%d ", root->value);
	if(root->right != NULL) inorder(root->right);
}

void preorder(Node* root) {
	if(root == NULL) return;
	printf("%d ", root->value);
	if(root->left != NULL) preorder(root->left);
	if(root->right != NULL) preorder(root->right);
}

void postorder(Node* root) {
	if(root == NULL) return;
	if(root->left != NULL) postorder(root->left);
	if(root->right != NULL) postorder(root->right);
	printf("%d ", root->value);
}

Node* min(Node* root) {
	Node* temp = root;
	if(temp == NULL) return temp;
	
	while(temp->left != NULL) {
		temp = temp->left;
	}

	return temp;
}

Node* delete(int value, Node* root) {
	if(root == NULL) return root;
	if(value < root->value) {
		root->left = delete(value, root->left);
	} else if(value > root->value) {
		root->right = delete(value, root->right);
	} else {
		if(root->left == NULL) {
			Node* temp = root->right;
			free(root);

			return temp;
		} else if(root->right == NULL) {
			Node* temp = root->left;
			free(root);
			
			return temp;
		}
		Node* minval = min(root->right);
		root->value = minval->value;
		root->right = delete(minval->value, root->right);
	}

	return root;
}

void freeTree(Node* root) {
	if(root == NULL) return;
	if(root->left != NULL) freeTree(root->left);
	if(root->right != NULL) freeTree(root->right);
	free(root);
}

void cpyerr(char* message, int type) {
	if(type == 0) {
		strcpy(message, RED);
		strcat(message, "[ERROR] Input was not an integer!\n\n");
	}

	int c;
	while(c = getchar() != '\n' && c != EOF);
}

int main() {
	system("tput smcup");

	int input;
	int nodeValue;
	char message[45];
	Node* root = NULL;

	while(1) {
		system("clear");

		printf("%s", message);
		message[0] = '\0';

		printf("%sTree:%s\n", GREEN, MAGENTA);
		printf("In-order traversal: "); inorder(root); printf("\n");
		printf("Pre-order traversal: "); preorder(root); printf("\n");
		printf("Post-order traversal: "); postorder(root); printf("\n\n");

		printf("%sOperation list:\n%s1 = Quits the program\n2 = INSERT - Inserts a new node into the tree\n3 = DELETE - Deletes a node from the tree\n%sEnter an operation: %s", BLUE, WHITE, BLUE, WHITE);

		if(scanf("%d", &input) != 1) {
			cpyerr(message, 0);
			continue;
		}

		switch(input) {
			default:
				snprintf(message, 100, "%s[ERROR] '%d' is not a valid operation!\n\n", RED, input);
				int c;
				while(c = getchar() != '\n' && c != EOF);

				break;
			case 1:
				system("tput rmcup");
				if(root != NULL) freeTree(root);

				return 0;
			case 2:
				printf("\n%s[INSERT]%s Enter the value for the new node: ", CYAN, WHITE);

				if(scanf("%d", &nodeValue) != 1) {
					cpyerr(message, 0);
				} else {
					if(root == NULL) root = insert(nodeValue, root);
					else insert(nodeValue, root);
				}

				break;
			case 3:
				printf("\n%s[DELETE]%s Enter the value of the node to delete: ", CYAN, WHITE);

				if(scanf("%d", &nodeValue) != 1) cpyerr(message, 0);
				else root = delete(nodeValue, root);
		}
	}

	return 0;
}
