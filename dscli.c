#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BLUE "\033[0;34m"
#define WHITE "\033[0;37m"
#define RED "\033[0;31m"

int main() {
	char command[6];

	while(1) {
		printf("%sdscli>%s ", BLUE, WHITE);
		scanf("%5s", &command);
		int c;
		while(c = getchar() != '\n' && c != EOF);

		if(strcmp(command, "q") == 0) {
			break;
		} else if(strcmp(command, "help") == 0) {
			printf("help - Prints out this help text\nlist - Executes the linked list program\nq - Exits out dscli\nclear - Clears the screen\n");
		} else if(strcmp(command, "clear") == 0) {
			system("clear");
		} else if(strcmp(command, "list") == 0) {
			pid_t childPID = fork();
			if(childPID == 0) {
				if(system("/home/sharkpause/Code/C/dscli/LinkedList/linkedlist") != 0) exit(1);
				exit(0);
			} else if(childPID < 0) {
				printf("%s[ERROR] Child process failed to create!", RED);
			} else {
				int childStatus;
				wait(&childStatus);
			}
		} else {
			printf("%s[ERROR] Invalid command!\n", RED);
		}
	}

	return 0;
}
