#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>

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


int terminate_a_process(long int *p_id){
    int result = kill(*p_id, SIGKILL);

    if(result == 0){
        printf("Signal SIGKILL sent successfully to process %ld\n", *p_id);
        return 1;
    } else {
        perror("Error sending signal");
        return 0;
    }
}

void list_running_processes(){
    DIR *directory_stream;
    printf("attempting to open the root\n");
    directory_stream = opendir("/proc");
   
    if(directory_stream == NULL) {
        perror("ERROR: unable to return a pointer to the proc directory stream.\n");
        return;
    }

    struct dirent *read_ptr = readdir(directory_stream);
    while (read_ptr != NULL) {
        if(is_positive_interger_value(read_ptr->d_name) == 1) {
            printf("/%s\n", read_ptr->d_name);
        } 
        read_ptr = readdir(directory_stream);
    }
    closedir(directory_stream); 


}

int main(int argc, char *argvc[]){

    // for(int i = 0; i < argc; i++) {
    //     printf("%s\n", argvc[i]); 
    // }
    long int p_id = 0;
    while(p_id != -1){
            printf("Provide a process number to terminate (-1 to exit, -100 to list running processes): ");
            scanf("%ld", &p_id);
            printf("You entereed: %ld\n", p_id);
            if(p_id == -1){
                break;
            } else if(p_id == -100){
                list_running_processes();
            } else{
                terminate_a_process(&p_id);
            }
    }
    return 0;
}