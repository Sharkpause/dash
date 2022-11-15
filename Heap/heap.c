#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[0;31m"
#define WHITE "\033[0;37m"
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define MAGENTA "\033[0;35m"

typedef struct Heap {
	int size;
	int capacity;
	int* heap;
	short type;
} Heap;

Heap* createHeap(short type) { // 0 = Max Heap | 1 = Min Heap
	Heap* new = (Heap*)malloc(sizeof(Heap));
	new->heap = (int*)calloc(10, sizeof(int));
	new->capacity = 0;
	new->size = 0;
	new->type = type;

	return new;
}

void swap(int* x, int* y) {
	int z = *y;
	*y = *x;
	*x = z;
}

void heapify(Heap* heap, int i) {
	if(heap->size == 1) {
		return;
	}
	int* array = heap->heap;
	if(heap->type == 0) {
		int largest = i;
		
		int leftIndex = 2*i + 1;
		int rightIndex = 2*i + 2;

		if(leftIndex < heap->size && array[leftIndex] > array[i]) {
			largest = leftIndex;
		}
		if(rightIndex < heap->size && array[rightIndex] > array[largest]) {
			largest = rightIndex;
		}
		if(largest != i) {
			swap(&array[i], &array[largest]);
			heapify(heap, largest);
		}
	} else if(heap->type == 1) {
		int smallest = i;
		
		int leftIndex = 2*i + 1;
		int rightIndex = 2*i + 2;

		if(leftIndex < heap->size && array[leftIndex] < array[i]) {
			smallest = leftIndex;
		}
		if(rightIndex < heap->size && array[rightIndex] < array[smallest]) {
			smallest = rightIndex;
		}
		if(smallest != i) {
			swap(&array[i], &array[smallest]);
			heapify(heap, smallest);
		}

	}
}

void insert(int value, Heap* heap) {
	heap->heap[heap->size] = value;
	heapify(heap, heap->size/2 - 1);
	++heap->size;
}

void delete(int value, Heap* heap) {
	int index;
	int* array = heap->heap;

	for(int i = 0; i < heap->size; ++i) {
		if(array[i] == value) {
			index = i;
			break;
		}
	}
	
	swap(&array[index], &array[heap->size-1]);
	--heap->size;

	for(int i = heap->size/2 - 1; i >= 0; --i) heapify(heap, i);
	
}

void printHeap(Heap* heap) {
	for(int i = 0; i < heap->size; ++i) {
		printf("%d ", heap->heap[i]);
	}
}

void maxHeap(Heap* heap) {
	heap->type = 0;
	for(int i = heap->size/2; i >= 0; --i) {
		heapify(heap, i);
	}
}

void minHeap(Heap* heap) {
	heap->type = 1;
	for(int i = heap->size/2; i >= 0; --i) {
		heapify(heap, i);
	}
}


void freeHeap(Heap* heap) {
	free(heap->heap);
	free(heap);
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
	Heap* minHeap = createHeap(1);
	Heap* maxHeap = createHeap(0);

	system("tput smcup");
	system("clear");

	int input, nodeValue;
	char message[41] = "";

	while(1) {
		system("clear");

		printf("%s", message);
		message[0] = '\0';

		printf("%sMin heap: %s", GREEN, MAGENTA); printHeap(minHeap); printf("\n");
		printf("%sMax heap: %s", GREEN, MAGENTA); printHeap(maxHeap); printf("\n\n");

		printf("%sOperation list:%s\n1 = Quits the program\n2 = INSERT - Adds a new node into the heap\n3 = DELETE - Deletes a specified node in the heap\n%sEnter an operation: %s", BLUE, WHITE, BLUE, WHITE);

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
				freeHeap(minHeap);
				freeHeap(maxHeap);

				return 0;
			case 2: // INSERT
				printf("%s[INSERT]%s Enter a value for the new node: ", CYAN, WHITE);

				if(scanf("%d", &nodeValue) != 1) {
					cpyerr(message, 0);
				} else {
					insert(nodeValue, minHeap);
					insert(nodeValue, maxHeap);
				}

				break;
			case 3: // DELETE
				printf("%s[DELETE]%s Enter the value of the node to be deleted: ", CYAN, WHITE);

				if(scanf("%d", &nodeValue) != 1) {
					cpyerr(message, 0);
				} else {
					delete(nodeValue, minHeap);
					delete(nodeValue, maxHeap);
				}

				break;
		}
	}

	freeHeap(minHeap);
	freeHeap(maxHeap);

	return 0;
}
