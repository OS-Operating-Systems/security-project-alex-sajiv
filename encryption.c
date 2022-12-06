#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_FREQ 2400000000 //min frequency (hz) for bluetooth
#define MAX_FREQ 2483500000 //max frequency (hz) for bluetooth
#define KEY 3 //chosen key for frequency


long generate_freq() {
    srand(time(0));
    long freq = rand() % (MAX_FREQ - MIN_FREQ + 1) + MIN_FREQ;
    return freq;
}

char* encrypt(char message[]) {

    int i;
    for(i = 0; i < strlen(message); i++) {
        message[i] = message[i] + KEY;
    }

    return message;
}

char* decrypt(char message[]) {

    int i;
    for(i = 0; i < strlen(message); i++) {
        message[i] = message[i] - KEY;
    }
    return message;
}

int main() {

    long freq = generate_freq();
    printf("%ld\n", freq);

    char message[] = "hi";
    char* encrypted_message = encrypt(message);
    printf("%s\n", encrypted_message);

    char* decryped_message = decrypt(encrypted_message);
    printf("%s\n", decryped_message);

    return 0;
}