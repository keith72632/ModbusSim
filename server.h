#ifndef SERVER_H
#define SERVER_H

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


#define PORT         5502

uint32_t create_socket();
uint32_t bind_socket(uint32_t server_sock);

#endif