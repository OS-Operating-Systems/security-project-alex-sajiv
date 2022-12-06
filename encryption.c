#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_FREQ 2400000000
#define MAX_FREQ 2483500000
#define KEY 3


long generate_freq() {
    srand(time(0));
    long freq = rand() % (MAX_FREQ - MIN_FREQ + 1) + MIN_FREQ;
    return freq;
}

void encrypt(char* message) {

    int i;
    for(i = 0; (i < 100 && message[i] != '\0'); i++) {
        message[i] = message[i] + KEY;
    }
    printf("%s\n", message);
}

char* decrypt(char* message) {

    int i;
    for(i = 0; (i < 100 && message[i] != '\0'); i++) {
        //printf("%c\n", message[i] + 3);
        message[i] = message[i] - KEY;
        //printf("%s\n", message);
    }
    printf("%s\n", message);
    //return message;
}

int main() {

    long freq = generate_freq();
    printf("%ld\n", freq);

    //message to encrypt must be less than 100 characters long
    char* message = "hi";
    //printf("%ld\n", strlen(message));
    encrypt(message);
    //printf("%s\n", encryped_message);

    return 0;
}