
#include "server.h"

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
    remote.sin_addr.s_addr = inet_addr("192.168.0.139");
    remote.sin_family = AF_INET;
    remote.sin_port = htons(PORT);
    temp = bind(server_sock, (struct sockaddr *)&remote, sizeof(remote));
    return temp;
}