#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

char user_input[100]; 
int input_received = 0;  

void *update_time(void *arg) {
    while (!input_received) {
        time_t t;
        struct tm *tm_info;
        char buffer[50];

        time(&t);
        tm_info = localtime(&t);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);

        printf("\rCurrent Time: %s", buffer);
        fflush(stdout);  

        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t time_thread;
    
    pthread_create(&time_thread, NULL, update_time, NULL);

    printf("\n\nEnter a string: ");
    fgets(user_input, sizeof(user_input), stdin);
    input_received = 1;  

    user_input[strcspn(user_input, "\n")] = '\0';

    
    pthread_join(time_thread, NULL);

    printf("\nYou entered: %s\n", user_input);

    return 0;
}