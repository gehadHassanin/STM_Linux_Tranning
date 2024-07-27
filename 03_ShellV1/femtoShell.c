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
	uint8_t *buf[BUFF_SIZE];
	uint8_t pathBuf[PATH_MAX];
    uint8_t i = 0;
	ssize_t bytesR;
	ssize_t bytesW;
	uint8_t iterator = 0;

	while (1) {
		/* Print the prompt */
	    bytesW == -1 ? perror("write: error") :  
		               write(STDOUT, "O2mor Ya Basha>:$ ", strlen("O2mor Ya Basha>:$ "));			
		
		/* Read command from the user */
		bytesR == -1 ? perror("write: error") : 
			           read(STDIN, command, 100);

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

		/* Exit the loop if command is "exit" */
		if (!strcmp(token, "exit")) {
			write(STDOUT, "Goodbye\n", strlen("Goodbye\n"));
			exit(EXIT_FAILURE);
		}
		
		i = 0;
        while (token != NULL) {
			buf[i++] = token; 	
			token = strtok(NULL, " ");
       	}
                        
		/*Check the user command and execute it*/        
		if (!strcmp(buf[0], "pwd")) {

			ImplementPwdCommand(i);

		} else if (!strcmp(buf[0], "help")) {

			buf[1] = "myhelp.txt";
			ImplementCatCommand(2, buf);

		} else if (!strcmp(buf[0], "cat")) {

			ImplementCatCommand(i, buf);

		} else if (!strcmp(buf[0], "cp")) {

			ImplementCpCommand(i, buf);

		} else if (!strcmp(buf[0], "mv")) {

			ImplementMvCommand(i, buf);

		} else if (!strcmp(buf[0], "echo")) {

			i == 1 ? printf("\n") : 
				     ImplementEchoCommand(echoMsg);

		} else if (!strcmp(buf[0], "realpath")) {

			FindRealPath(buf[1], pathBuf);
			printf("%s\n", pathBuf);

		} else if (!strcmp(buf[0], "rmdir")) {

			for(iterator = 1; iterator < i; iterator++) {
				RemoveDirectory(buf[iterator]);
			}

		} else if (!strcmp(buf[0], "rm")) {

            for(iterator = 1; iterator < i; iterator++) {
                    RemoveFile(buf[iterator]);
            }

		} else {

			printf("Command '%s' not found, but can be used help command:\n", buf[0]);
			printf("  to know about my supported command\n"); 

		}

		clearBuffer(command, COMMAND_SIZE);
		clearBuffer(echoMsg, MSG_SIZE);
	}
        return 0;
}


void clearBuffer(uint8_t* buf, uint8_t size) {
    for (uint8_t i = 0; i < size; i++)  {
        buf[i] = '\0';
    }
}
