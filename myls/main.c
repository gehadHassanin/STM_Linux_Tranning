#include "myls.h"

extern uint16_t option;

int main(int argc, char** argv) {

    int opt;
    int i = 0;
    if (argc == 1) {
        argv[argc++] = "."; 
    }
    while ((opt = getopt(argc, argv, "latucifd1")) != -1) {
        switch (opt) {
            case 'l': SET_BIT(option, kOpt_l); break;
            case 'a': SET_BIT(option, kOpt_a); break;
            case 't': SET_BIT(option, kOpt_t); break;
            case 'u': SET_BIT(option, kOpt_u); break;
            case 'c': SET_BIT(option, kOpt_c); break;
            case 'i': SET_BIT(option, kOpt_i); break;
            case 'f': SET_BIT(option, kOpt_f); break;
            case 'd': SET_BIT(option, kOpt_d); break;
            case '1': SET_BIT(option, kOpt_1); break;
            case '?': perror("Unrecognized option");
        }
    }
    i = (option == 0) ? 0 : 1;
    while (++i < argc) {
        if (argc > 3 || ((argc > 2) && !option)) {
            printf("%s:\n", argv[2]);
        }   

        if (GET_BIT(option, kOpt_d)) {

        } else {
            DefaultPrinting(argv[i]);
        }
        
        if ((i + 1) < argc) {
            printf("\n");
        }    
   }
   
}