#include "myls.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        ExecuteOption_l(".");
    } else {
        int i = 0;
        while(++i < argc){
            if (argc != 2) {
                printf("%s:\n", argv[i]);
            }
            ExecuteOption_l(argv[i]);
            if ((i + 1) < argc) {
                printf("\n");
            }
        }
    }
}