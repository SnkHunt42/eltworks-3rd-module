#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MAX_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_SIZE];
};

int main() {
    key_t key;
    int msg_id;
    struct msg_buffer message;

    key = ftok("msgq_file", 65);
    msg_id = msgget(key, 0666 | IPC_CREAT);

    if(msg_id == -1) {
        perror("msgget");
        exit(1);
    }

    while(1) {
        printf("Введите сообщение: ");
        fgets(message.msg_text, MAX_SIZE, stdin);
        message.msg_type = 2;
        
        msgsnd(msg_id, &message, sizeof(message), 0);

        msgrcv(msg_id, &message, sizeof(message), 1, 0);

        printf("Получено сообщение: %s", message.msg_text);
    }

    msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}
