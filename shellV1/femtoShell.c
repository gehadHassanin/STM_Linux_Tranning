#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "commands.h"
#include <limits.h>

#define STDIN  (0)
#define STDOUT (1)
#define STDERR (2)

#define COMMAND_SIZE (100)
#define MSG_SIZE     (100)
#define BUFF_SIZE    (10)

void clearBuffer(uint8_t* buf, uint8_t size);

int main() {

        uint8_t command[COMMAND_SIZE];
	uint8_t echoMsg[MSG_SIZE];
	uint8_t *myargv[BUFF_SIZE];
	uint8_t pathBuf[PATH_MAX];
        uint8_t myargc = 0;
	uint8_t i = 0;
	ssize_t bytesR;
	ssize_t bytesW;
	uint8_t iterator = 0;

	while (1) {
		/* Print the prompt message */
		bytesW = write(STDOUT, "O2mor Ya Basha>:$ ", strlen("O2mor Ya Basha>:$ "));
		if (bytesW == -1) {
			perror("write");
		}
	    		
		/* Read command from the user */
		clearBuffer(command, COMMAND_SIZE);
		bytesR = read(STDIN, command, 100);
		if (bytesR == -1) {
			perror("read");
		}

		/* Skip to the next iteration to print the prompt again */
        	if (strlen(command) == 1) {
			command[0] = '\0';
            		continue; 
        	}

		/* Remove the newline character if present */ 
        	if (command[strlen(command) - 1] == '\n') {
			command[strlen(command) - 1] = '\0';
		}

		/* Store the rest of the input after the "echo " command */
		iterator = 0;
		i = 5;
		clearBuffer(echoMsg, MSG_SIZE);
		while (command[i] != '\0') {
			if (command[i] == '"' && command[i + 1] != '\0') {
				echoMsg[iterator++] = command[++i];
				i++;
			} else if (i == strlen(command) - 1 && command[strlen(command) - 1] == '"') {
				break;
			} else {
				echoMsg[iterator++] = command[i++];
			}
		}
		echoMsg[iterator] = '\0';

                uint8_t* token = strtok(command, " ");
		if (!strcmp(token, "exit")) {
                        write(STDOUT, "Goodbye\n", strlen("Goodbye\n"));
                        exit(EXIT_FAILURE);
                }

		myargc = 0;
        	while (token != NULL) {
			myargv[myargc++] = token; 	
			token = strtok(NULL, " ");
       		}
                        
		/*Check the user command and execute it*/     
	        if (!strcmp(myargv[0], "pwd")) {
			ImplementPwdCommand(myargc);

		} else if (!strcmp(myargv[0], "help")) {
			myargv[1] = "myhelp.txt";
			ImplementCatCommand(2, myargv);
			
		} else if (!strcmp(myargv[0], "cat")) {
			ImplementCatCommand(myargc, myargv);
			
		} else if (!strcmp(myargv[0], "cp")) {
			ImplementCpCommand(myargc, myargv);
			
		} else if (!strcmp(myargv[0], "mv")) {
			ImplementMvCommand(myargc, myargv);
			
		} else if (!strcmp(myargv[0], "echo")) {
			myargc == 1 ? printf("\n") : 
				 ImplementEchoCommand(echoMsg);
			
		} else if (!strcmp(myargv[0], "realpath")) {
			FindRealPath(myargv[1], pathBuf);
			printf("%s\n", pathBuf);
			
		} else if (!strcmp(myargv[0], "rmdir")) {
			for(iterator = 1; iterator < myargc; iterator++) {
				RemoveDirectory(myargv[iterator]);	
			}
			
		} else if (!strcmp(myargv[0], "rm")) {
            		for(iterator = 1; iterator < myargc; iterator++) {
                   	 	RemoveFile(myargv[iterator]);
			}

		} else if (!strcmp(myargv[0], "cd")) {
			ChangeCurrentDirectory(myargc, myargv);
			
		} else {
			printf("Command '%s' not found, but can be used help command:\n", myargv[0]);
			printf("  to know about my supported command\n"); 
			
		}
	}
        return 0;
}


void clearBuffer(uint8_t* buf, uint8_t size) {
    for (uint8_t i = 0; i < size; i++)  {
        buf[i] = '\0';
    }
}
