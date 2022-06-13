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

#include "server.h"
#include "registers.h"

coil coil_regs[1000], coil_res;
discrete_input discrete_input_regs[1000];
input input_regs[1000];
word holding_regs[1000];


char function_code[8][2] = {
    "1", "2", "3", "4", "5", "6", "15", "16"
};

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
        int new_sock, action, iResult, client_action, modbus_addr, modbus_val, converted;
        struct sockaddr_in client;
        memset(&client, '\0', sizeof(client));
        int clientLen = sizeof(client);
        char sendbuf[16], recvbuf[16]; 
        
        if((new_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&clientLen)) < 0){
            printf("client could not connect\n");
            exit(1);
        }
        printf("[+]Connection made with %s\n", inet_ntoa(client.sin_addr));

        randomize_coils(coil_regs);
        client_action = recv(new_sock, recvbuf, 16, 0);
        printf("Recv buffer %s\n", recvbuf);
        action = atoi(recvbuf);
        printf("Action: %d\n", action);

        memset(recvbuf, 0, 16);
        client_action = recv(new_sock, recvbuf, 16, 0);
        modbus_addr = atoi(recvbuf);
        printf("Modbus addr %d\n", modbus_addr);        
        memset(recvbuf, 0, 16);

        // iResult = send(new_sock, sendbuf, (int) strlen(sendbuf), 0);
        // printf("Pick Address\n");
        // printf("\t1. Read Coil Status\n\t2. Read Input Status\n\t3. Read Holding Register\n\t4. Read Internal Register\n\t5. Force Single Coil\n\t6. Write Single Register\n\t15. Force Multiple Coils\n\t16. Mask Write Register\n");
        // scanf("%d", &action);
        switch(action){
            case 1:
                printf("Read Coil Status\n");
                coil_res = read_coil_status(modbus_addr, coil_regs);
                converted = htonl(coil_res);
                uint32_t x = 6969;
                client_action = send(new_sock, &coil_res, sizeof(coil_res), 0);
                printf("Read Coil Result: %hd\n", coil_res);
                break;
            case 2: 
	        	printf("Read input status\n");
                break;
            case 3:
                printf("Read Holding Register\n");
                word res = read_holding_register(modbus_addr, holding_regs);
                uint32_t n = 6969;
                converted = htonl(n);
                printf("Value from holding register %hd\n", res);
                client_action = send(new_sock, &converted, 16, 0);
                printf("Data send\n");
                break;
            case 4:
                printf("Read Internal Register\n");
                break;
            case 5:
                write_coil(modbus_addr, coil_regs);
                printf("Coil address %d written to\n", modbus_addr);
                break;
            case 6:
                printf("Write Single Register\n");
                write_holding_register(modbus_addr, holding_regs);
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

