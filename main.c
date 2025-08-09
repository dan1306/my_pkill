#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

int is_positive_interger_value(const char *str) {
    if(str == NULL || strlen(str) == 0) {
        return 0;
    }

    char *endptr;
    long int num;

    num = strtol(str, &endptr, 10);
    if(endptr == str) {
        // printf("No digits were found.\n");
        return 0;
    } else if(*endptr != '\0') {
        // printf("Invalid character: %c\n");
        return 0;
    }

    return 1;
}



int main(int argc, char *argvc[]){

    // for(int i = 0; i < argc; i++) {
    //     printf("%s\n", argvc[i]); 
    // }
    DIR *directory_stream;
    printf("attempting to open the root");
    directory_stream = opendir("/proc");
   
    if(directory_stream == NULL) {
        perror("ERROR: unable to return a pointer to the proc directory stream.\n");
        return 0;
    }

    struct dirent *read_ptr = readdir(directory_stream);
    while (read_ptr != NULL) {
        if(is_positive_interger_value(read_ptr->d_name) == 1) {
            printf("/%s\n", read_ptr->d_name);
        } 
        read_ptr = readdir(directory_stream);
    }
    closedir(directory_stream); 
    return 0;
}