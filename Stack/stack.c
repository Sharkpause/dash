#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define GREEN "\033[0;32m"
#define WHITE "\033[0;37m"
#define CYAN "\033[0;36m"

typedef struct Stack {
	int size;
	int capacity;
	int* array;
} Stack;

Stack* createStack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->array = (int*)calloc(10, sizeof(int));
	stack->size = 0;
	stack->capacity = 10;

	return stack;
}

void push(int value, Stack* stack) {
	if(stack->size >= stack->capacity) {
		stack->array = realloc(stack->array, (stack->capacity+10) * sizeof(int));
		stack->capacity += 10;
	}
	stack->array[stack->size] = value;
	++stack->size;
}

int pop(Stack* stack) {
	--stack->size;
	return stack->array[stack->size+1];
}

void printStack(Stack* stack) {
	if(stack->size <= 0) {
		printf("The list is empty!");
		return;
	}
	for(int i = 0; i < stack->size; ++i) {
		printf("%d ", stack->array[i]);
	}
}

void freeStack(Stack* stack) {
	free(stack->array);
	free(stack);
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
	Stack* stack = createStack();
	int input;
	int itemValue;
	char message[45];

	system("tput smcup");
	while(1) {
		system("clear");

		printf("%s", message);
		message[0] = '\0';

		printf("%sStack:%s\n", GREEN, MAGENTA);
		printStack(stack);
		printf("\n\n");

		printf("%sOperation list\n%s1 = Quits the program\n2 = PUSH - Pushes a value into the stack\n3 = POP - Deletes the last value from the stack\n%sEnter an operation: %s", BLUE, WHITE, BLUE, WHITE);
		if(scanf("%d", &input) != 1) {
			cpyerr(message, 0);
			continue;
		}

		switch(input) {
			default:
				snprintf(message, 100, "%s[ERROR] '%d' is not a valid operation!\n\n", RED, input);
				
				break;
			case 1:
				freeStack(stack);
				system("tput rmcup");

				return 0;
			case 2:
				printf("\n%s[PUSH]%s Input the value for the new item: ", CYAN, WHITE);
				if(scanf("%d", &itemValue) != 1) {
					cpyerr(message, 0);
				} else {
					push(itemValue, stack);
				}
				
				break;
			case 3:
				pop(stack);
		}
	}


	freeStack(stack);
	return 0;
}
