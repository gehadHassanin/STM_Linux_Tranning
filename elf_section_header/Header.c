#include <stdio.h>
#include <unistd.h>
#include <elf.h>
#include "myElfHeader.h"
#include "mySectionHeader.h"

int main(int argc, char** argv) {
        FILE *file = fopen(argv[1], "r");
	int retOpt;
	
        while((retOpt = getopt(argc, argv, "hS")) != -1) {
	   switch(retOpt) {
               case 'h' : PrintElfHeader(file); break;
	       case 'S' : PrintSectionHeaders(file); break;
	       default  : printf("Unknown option");
	  }
	}
        fclose(file);
        return 0;
}

