#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RED "\033[0;31m"
#define WHITE "\033[0;37m"
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"

typedef struct Node {
	int value;
	struct Node* next;
} Node;

typedef struct List {
	Node* head;
	Node* tail;
	int size;
} List;

int push(int value, List* list) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->value = value;

	if(list->head == NULL) {
		list->head = newNode;
		list->tail = list->head;
	} else {
		list->tail->next = newNode;
		list->tail = list->tail->next;
	}

	++list->size;
	return 0;
}

int unshift(int value, List* list) {
	if(list->head == NULL) return push(value, list);

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->value = value;

        Node* temp = list->head;
        list->head = newNode;
        newNode->next = temp;

	++list->size;
	return 0;
}

int insert(int value, List* list, int index) {
	if(index == 0) {
		return unshift(value, list);
	} else if(index == -1 || index == list->size) {
		return push(value, list);
	} else if(index > list->size) {
		return -1;
	}

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->value = value;
	Node* temp = list->head;

	for(int i = 0; i < index-1; ++i) temp = temp->next;

	Node* next = temp->next;
	temp->next = newNode;
	newNode->next = next;

	++list->size;
	return 0;
}

int pop(List* list) {
	Node* temp = list->head;

	if(temp == NULL) return 1;
	if(temp->next == NULL) {
		int value = temp->value;
		free(temp);
		list->head = NULL;
		--list->size;
		return 0;
	}

	Node* previous;
	while(temp->next != NULL) {
		previous = temp;
		temp = temp->next;
	}

	previous->next = NULL;
	free(temp);
	list->tail = previous;

	--list->size;
	return 0;
}

int shift(List* list) {
	if(list->head == NULL) return 1;
	if(list->head->next == NULL) return pop(list);

	int value = list->head->value;
	Node* next = list->head->next;
	free(list->head);
	list->head = next;

	--list->size;
	return 0;
}

int delete(int index, List* list) {
	if(index == 0) return shift(list);
	if(index >= list->size) return -1;
	if(index == list->size-1 || index == -1) return pop(list);

	Node* temp = list->head;
	
	if(temp == NULL) return 1;
	if(temp->next == NULL) return pop(list);

	int value;

	for(int i = 0; i < index-1; ++i) temp = temp->next;
	
	Node* next = temp->next->next;
	value = temp->next->value;
	free(temp->next);
	temp->next = next;

	--list->size;
	return 0;
}

void freeList(List* list) {
	Node* next;
	while(list->head != NULL) {
		next = list->head->next;
		free(list->head);
		list->head = next;
	}
	free(list);
}

void printList(List* list) {
	Node* temp = list->head;
	while(temp != NULL) {
		printf("%d->", temp->value);
		temp = temp->next;
	}
	printf("NULL");
}

void cpyerr(char* message, int type) {
	strcpy(message, RED);
	if(type == 0) {
		strcat(message, "[ERROR] Input was not an integer!\n\n");
	} else if(type == 1) {
		strcat(message, "[ERROR] List index is invalid!\n\n");
	}

	int c;
	while(c = getchar() != '\n' && c != EOF);
}

int main() {
	system("tput smcup");
	system("clear");

	List* list = (List*)malloc(sizeof(List));

	int input;
	int nodeValue;
	int index;
	char message[41] = "";

	while(1) {
		system("clear");

		printf("%s", message);
		message[0] = '\0';

		printf("%sList:%s\n", GREEN, MAGENTA);
		printList(list);

		printf("\n\n%sOperation list:%s\n1 = Quits the program\n2 = PUSH - Adds a new node at the end of the list\n3 = UNSHIFT - Adds a new node at the start of the list\n4 = INSERT - Adds a new node at a certain index in the list\n5 = POP - Deletes a node at the end of the list\n6 = SHIFT - Deletes a node at the start of the list\n7 = DELETE - Deletes a node at a certain index\n8 = SIZE - Displays the size of the list\n%sEnter an operation: %s", BLUE, WHITE, BLUE, WHITE);

		if(scanf("%d", &input) != 1) {
			cpyerr(message, 0);
			continue;
		}
		printf("\n");

		switch(input) {
			default:
				snprintf(message, 100, "%s[ERROR] %d is not a valid operation!\n\n", RED, input);

				break;
			case 1: // QUIT
				system("tput rmcup");

				freeList(list);

				return 0;
			case 2: // PUSH
				printf("%s[PUSH]%s Enter a value for the new node: ", CYAN, WHITE);

				if(scanf("%d", &nodeValue) != 1) cpyerr(message, 0);
				else push(nodeValue, list);

				break;
			case 3: // UNSHIFT
				printf("%s[UNSHIFT]%s Enter a value for the new node: ", CYAN,  WHITE);

				if(scanf("%d", &nodeValue) != 1) cpyerr(message, 0);
				else unshift(nodeValue, list);

				break;
			case 4: // INSERT
				printf("%s[INSERT]%s Enter a value for the new node: ", CYAN, WHITE);

				if(scanf("%d", &nodeValue) != 1) {
					cpyerr(message, 0);
				} else {
					printf("%s[INSERT]%s Enter an index to insert the new node in: ", CYAN, WHITE);
					if(scanf("%d", &index) != 1) cpyerr(message, 0);
					else insert(nodeValue, list, index);	
				}

				break;
			case 5: // POP
				if(pop(list) == -1) cpyerr(message, 1);

				break;
			case 6: // SHIFT
				if(shift(list) <= -1) cpyerr(message, 1);

				break;
			case 7: // DELETE
				printf("%s[DELETE]%s Enter an index to delete at: ", CYAN, WHITE);

				if(scanf("%d", &index) != 1) cpyerr(message, 0);
				else if(delete(index, list) <= -1) cpyerr(message, 1);

				break;
			case 8: // SIZE
				snprintf(message, 100, "%sSize of list: %s%d\n\n", GREEN, MAGENTA, list->size);
		}
	}

	freeList(list);

	system("tput rmcup");
	
	return 0;
}
