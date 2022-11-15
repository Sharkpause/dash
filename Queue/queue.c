#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define GREEN "\033[0;32m"
#define WHITE "\033[0;37m"
#define CYAN "\033[0;36m"

typedef struct Node {
	int value;
	struct Node* next;
} Node;

typedef struct Queue {
	Node* head;
	Node* tail;
} Queue;

void cpyerr(char* message, int type) {
	strcpy(message, RED);
	if(type == 0) strcat(message, "[ERROR] Input was not an integer!\n\n");
	else if(type == 1) strcat(message, "[ERROR] List index is invalid!\n\n");

	int c;
	while(c = getchar() != '\n' && c != EOF);
}

Queue* createQueue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

Node* createNode(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	return node;
}

int front(Queue* queue) {
	if(queue->tail != NULL) return queue->tail->value;
}

void enqueue(int value, Queue* queue) {
	if(queue->head == NULL) {
		queue->head = createNode(value);
		queue->tail = queue->head;
	} else {
		queue->tail->next = createNode(value);
		queue->tail = queue->tail->next;
	}
}

void dequeue(Queue* queue) {
	if(queue->head == NULL) return;
	if(queue->head->next == NULL) queue->tail = NULL;

	Node* deleted = queue->head;
	queue->head = queue->head->next;
	free(deleted);
}

void printQueue(Queue* queue) {
	Node* current = queue->head;

	while(current != NULL) {
		printf("%d->", current->value);
		current = current->next;
	}
	printf("NULL");
}

void freeQueue(Queue* queue) {
	Node* current = queue->head;
	Node* next;
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	free(queue);
}

int main() {
	system("tput smcup");
	system("clear");

	Queue* queue = createQueue();

	int input;
	int nodeValue;
	char message[41] = "";

	while(1) {
		system("clear");

		printf("%s", message);
		message[0] = '\0';

		printf("%sQueue: %s\n", GREEN, MAGENTA);
		printQueue(queue);
		printf("\n%sFront: %s%d\n", GREEN, MAGENTA, front(queue));

		printf("\n\n%sOperation list:%s\n1 = Quits the program\n2 = Enqueue - Enqueues a new node into the queue\n3 = Dequeue - Dequeues a node from the queue\n%sEnter an operation: %s", BLUE, WHITE, BLUE, WHITE);

		if(scanf("%d", &input) != 1) {
			cpyerr(message, 0);
			continue;
		}
		printf("\n");

		switch(input) {
			default:
				snprintf(message, 100, "%s[ERROR] %d is not a valid operation!\n\n", RED, input);
			case 1: // QUIT
				system("tput rmcup");
				
				freeQueue(queue);

				return 0;
			case 2: // Enqueue
				printf("%s[ENQUEUE] Enter a value for the new node: ", CYAN, WHITE);

				if(scanf("%d", &nodeValue) != 1) cpyerr(message, 0);
				else enqueue(nodeValue, queue);

				break;
			case 3: //Dequeue
				dequeue(queue);

				break;
		}
	}

	freeQueue(queue);
	
	return 0;
}
