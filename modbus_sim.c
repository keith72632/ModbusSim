#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>


#define WORD_SIZE    16
#define MAX_LINE     2048
#define PORT         5502

typedef uint8_t coil, discrete_input;
typedef uint16_t input, word;

coil coil_regs[1000], coil_res;
discrete_input discrete_input_regs[1000];
input input_regs[1000];
word holding_regs[1000];

// Prototypes
coil read_coil_status();
void write_coil();
word read_holding_register();
void write_holding_register();

uint32_t create_socket();
uint32_t bind_socket(uint32_t server_sock);

int main() {

    uint32_t server_sock;

    server_sock = create_socket();

    if(server_sock < 0) {
        perror("Could not create socket");
        exit(1);
    }

    if(bind_socket(server_sock) < 0) {
        perror("Could not bind socket");
        exit(1);
    }
    printf("[+]Socket bound...\n");

    printf("[+]Listening on port %d...\n", PORT);
    listen(server_sock, 1);

    while(1){
        int new_sock, action, iResult;
        struct sockaddr_in client;
        memset(&client, '\0', sizeof(client));
        int clientLen = sizeof(client);
        char sendbuf[] = "\t1. Read Coil Status\n\t2. Read Input Status\n\t3. Read Holding Register\n\t4. Read Internal Register\n\t5. Force Single Coil\n\t6. Write Single Register\n\t15. Force Multiple Coils\n\t16. Mask Write Register\n"; 
        
        if((new_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&clientLen)) < 0){
            printf("client could not connect\n");
            exit(1);
        }
        printf("[+]Connection made with %s\n", inet_ntoa(client.sin_addr));

        iResult = send(new_sock, sendbuf, (int) strlen(sendbuf), 0);
        printf("Pick Address\n");
        printf("\t1. Read Coil Status\n\t2. Read Input Status\n\t3. Read Holding Register\n\t4. Read Internal Register\n\t5. Force Single Coil\n\t6. Write Single Register\n\t15. Force Multiple Coils\n\t16. Mask Write Register\n");
        scanf("%d", &action);
        switch(action){
            case 1:
                printf("Read Coil Status\n");
                coil_res = read_coil_status();
                printf("Read Coil Result: %hd\n", coil_res);
                break;
            case 2: 
                printf("Read Input Status\n");
                break;
            case 3:
                printf("Read Holding Register\n");
                word res = read_holding_register();
                break;
            case 4:
                printf("Read Internal Register\n");
                break;
            case 5:
                printf("Force Single Coil\n");
                write_coil();
                break;
            case 6:
                printf("Write Single Register\n");
                write_holding_register();
                break;
            case 15:
                printf("Force Multiple Coils");
                break;
            case 16:
                printf("Masked Write Register\n");
                break;
            default: 
                printf("Invalid input\n");
                break;            
        }
    }
}

coil read_coil_status() {
    uint32_t reg;
    printf("Enter address of coil to be read (1 - 1000)\n\n");
    scanf("%d", &reg);
    return coil_regs[reg];
}

void write_coil() {
    uint32_t reg;
    printf("Enter address of coil to be written to (1 - 1000)\n");
    scanf("%d", &reg);
    coil_regs[reg] |= 0x01;
    printf("Coil register %d set to %hhd\n\n", reg, coil_regs[reg]);
}

word read_holding_register() {
    uint32_t reg;
    FILE *fp = NULL;
    char status;
    char output[MAX_LINE];
    bool keep_reading = true;
    int current_line = 1;

    fp = fopen("./holding_registers.txt", "r");

    if(fp == NULL) {
        perror("Cannot access holding registers\n");
    }

    printf("Enter address of holding register to be read (1 - 1000)\nAddress>");
    scanf("%d", &reg);

    do {
        fgets(output, MAX_LINE, fp);

        if(feof(fp))
        {
            keep_reading = false;
            printf("File %d lines.\n", (current_line - 1));
        } else if (current_line == reg){
            keep_reading = false;
            printf("Address %d value: %s", reg, output);
        }

        current_line++;
    } while(keep_reading);

    fclose(fp);

    return holding_regs[reg];
}

void write_holding_register() {
    FILE *fp = NULL;
    uint32_t reg;
    word val;
    printf("Enter address of holding register to be written to (1 - 1000)\n");
    scanf("%d", &reg);
    printf("Enter value to be written to address\n");
    scanf("%hd", &val);
    holding_regs[reg] = val;
    printf("Holding register %d set to %hd\n\n", reg, val);

    fp = fopen("./holding_registers.txt", "w+");

    if(fp == NULL) {
        perror("Cannot access holding registers\n");
    }


    fclose(fp);

}


uint32_t create_socket(){
    uint32_t temp = -1;
    temp = socket(AF_INET, SOCK_STREAM, 0);
    printf("[+]Socket created...\n");
    return temp;
}

uint32_t bind_socket(uint32_t server_sock){
    uint32_t temp = -1;
    struct sockaddr_in remote;
    memset(&remote, '\0', sizeof(remote)); 
    remote.sin_addr.s_addr = inet_addr("");
    remote.sin_family = AF_INET;
    remote.sin_port = htons(PORT);
    temp = bind(server_sock, (struct sockaddr *)&remote, sizeof(remote));
    return temp;
}