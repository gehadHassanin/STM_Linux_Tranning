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
#include <sys/types.h>
#include <sys/wait.h>

void clearBuffer(uint8_t* buf, int32_t size);
void StoreMsg(uint8_t command[], uint8_t *echoMsg);
void ParsingInput(uint8_t command[], uint8_t *__token[], uint8_t *token_num);

int main() {
        uint8_t *command;
	uint8_t *echoMsg;
	uint8_t **myargv;
	uint8_t pathBuf[PATH_MAX];
        uint8_t myargc = 0;
	pid_t ret_pid;
	uint8_t iterator = 0;
	ProcessInfo_t Info;
	ProcessHist_t History;
	History.top__ = 0;

	while (1) {
	/* allocate dynamic memory */
        command = (uint8_t *) malloc(COMMAND_SIZE); 
        myargv = (uint8_t **) malloc(BUFF_SIZE * sizeof(uint8_t **)); 
	echoMsg = (uint8_t *) malloc(COMMAND_SIZE); 

        /* Print the prompt message */
        if (write(STDOUT, "O2mor Ya Basha>:$ ", strlen("O2mor Ya Basha>:$ ")) == -1) 
	{
            perror("write");
        }

        /* Read command from the user */
	clearBuffer(command, COMMAND_SIZE);
        if (read(STDIN, command, 100) == -1) 
	{
            perror("read");
        }

        /* Remove the newline character if present */
        if (command[strlen(command) - 1] == '\n') 
	{  
            command[strlen(command) - 1] = '\0';
        }
		

        /* Skip to the next iteration to print the prompt again */
        if (strlen(command) == 0) 
	{
			continue;
        }

	/* Store the rest of the input after the "echo " command */
	StoreMsg(command, echoMsg);

	ParsingInput(command, myargv, &myargc);
                      
	/*Check the user command and execute it*/ 
	if (Is_InternalCmd(myargv[0]) == 0)
	{
		if (!strcmp(myargv[0], "exit")) 
		{
        	    write(STDOUT, "Goodbye\n", strlen("Goodbye\n"));
        	    exit(EXIT_FAILURE);

        	} else if (!strcmp(myargv[0], "mypwd")) 
		{
			ImplementPwdCommand(myargc);

		} else if (!strcmp(myargv[0], "help")) 
		{
			myargv[1] = "myhelp.txt";
			ImplementCatCommand(2, myargv);

		} else if (!strcmp(myargv[0], "mycat")) 
		{
			ImplementCatCommand(myargc, myargv);

		} else if (!strcmp(myargv[0], "mycp")) 
		{
			ImplementCpCommand(myargc, myargv);

		} else if (!strcmp(myargv[0], "mymv")) 
		{
			ImplementMvCommand(myargc, myargv);

		} else if (!strcmp(myargv[0], "myecho")) 
		{
			myargc == 1 ? printf("\n") : 
			ImplementEchoCommand(echoMsg);
			free(echoMsg);

		} else if (!strcmp(myargv[0], "myrealpath")) 
		{
			if (myargc == 2) 
			{
				FindRealPath(myargv[1], pathBuf);
				printf("%s\n", pathBuf);

			} else 
			{
				perror("realpath: Invalid argument");
				continue;
			}

		} else if (!strcmp(myargv[0], "myrmdir")) 
		{
			for(iterator = 1; iterator < myargc; iterator++) 
			{
				RemoveDirectory(myargv[iterator]);	
			}

		} else if (!strcmp(myargv[0], "myrm"))
		{
			for(iterator = 1; iterator < myargc; iterator++) 
			{ 
				RemoveFile(myargv[iterator]);
			}

		} else if (!strcmp(myargv[0], "cd")) 
		{
			ChangeCurrentDirectory(myargc, myargv);

		} else if (!strcmp(myargv[0], "envir")) 
		{
			ImplementEnvCommand(myargc, myargv);

		} else if (!strcmp(myargv[0], "type")) 
		{
			ImplementTypeCommand(myargc, myargv);

		} else if (!strcmp(myargv[0], "clear")) 
		{
			clear_screen();

		}else if (!strcmp(myargv[0], "phist")) 
		{
			printf("%-8s %-10s %s\n", "PID", "Status", "Command");

			if (Get_Size(&History) < NUM_PROCESS) 
			{
				Traverse_History(&History, Get_Size(&History));

			} else 
			{
				Traverse_History(&History, NUM_PROCESS);
			}

		}

		free(myargv);
        	free(command);

	} else if (Is_ExternalCmd(myargv[0]) == 0)
	{
        	ret_pid = fork();
	
        	if (ret_pid == 0) 
        	{
			// CHILD
        	        myargc++;
	    	        myargv[myargc - 1] = NULL;
	    	        execvp (myargv[0], myargv);
	    	        printf ("Exec failed\n");
        	        exit(EXIT_FAILURE);

        	} else if (ret_pid > 0) 
        	{ 
			// PARENT
        	        int32_t wstatus;
        	        if (wait(&wstatus) == -1) 
		        {
				perror("wait");
        	        }
			
		        Info.status__ = WIFEXITED(wstatus);
		        Info.pid__ = ret_pid;
		        strcpy(Info.__cmd, myargv[0]);

		        Push_Process(&History, &Info);
			
		        free(myargv);
        	        free(command);
				
        	}else 
        	{
			printf("Failed to create child process\n");
        	}


		} else 
		{
			printf("Command '%s' not found, but can be used help command:\n", myargv[0]);
			printf("  to know about my supported command\n"); 

		}
	}
        return 0;
}

void clearBuffer(uint8_t* buf, int32_t size) {
    for (uint8_t i = 0; i < size; i++)  
    {
        buf[i] = '\0';
    }
}

void ParsingInput(uint8_t __command[], uint8_t *__token[], uint8_t *token_num) {    
        *(token_num) = 0;   

        for (int32_t Iterator = 0; Iterator < BUFF_SIZE; Iterator++) 
	{
                __token[Iterator] = NULL;
        }

        uint8_t* token = strtok(__command, SPACE_DELIMETER);

        while (token != NULL) 
	{
                __token[(*(token_num))++] = token;
                token = strtok(NULL, SPACE_DELIMETER);
        }
}

void StoreMsg(uint8_t command[], uint8_t *echoMsg) {
		uint8_t i = 7;
	        uint8_t iterator = 0;

		clearBuffer(echoMsg, COMMAND_SIZE);
		while (command[i] != '\0') 
		{
			if (command[i] == '"' && command[i + 1] != '\0') 
			{
				echoMsg[iterator++] = command[++i];
				i++;
				
			} else if (i == strlen(command) - 1 && command[strlen(command) - 1] == '"') 
			{
				break;

			} else 
			{
				echoMsg[iterator++] = command[i++];
			}
		}
		echoMsg[iterator] = '\0';
}

