// #include "include/listen.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../include/chat_socket.h"
#include "../include/listen.h"
#include "../include/print.h"

#define PORT 9099

void alloc_client() {
  printf("Starting client...\n");
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) {
    printf("Error creating required socket, exiting...");
    return;
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_port = htons(PORT);

  struct chat_socket data;
  data.socket_fd = sfd;
  data.role = "Client";

  if (connect(sfd, (struct sockaddr*)&address, sizeof(address)) != 0) {
    printf("Connection to server error!");
    return;
  }

  while (1) {
    char inputBuff[255];
    print_debug(&data, "Input your message: ", false);
    bzero(inputBuff, sizeof(char)*255);
    scanf("%s", inputBuff);
    write(sfd, inputBuff, sizeof(char)*255);
    sleep(1);
  }
}

void alloc_server() {
  printf("Starting server...\n");
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) {
    printf("Error creating required socket, exiting...");
    return;
  }

  struct chat_socket data;
  bzero(&data, sizeof(data));
  data.socket_fd = sfd;
  data.role = "Server";

  struct sockaddr_in address;

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_port = htons(PORT);

  if ((bind(sfd, (struct sockaddr *)&address, sizeof(address))) != 0) {
    printf("Error binding to port...");
    return;
  }
  listenChat(&data);
}

int main() {
  printf("Starting program...\n\n");

  pthread_t serverThread, clientThread;
  pthread_create(&serverThread, NULL, &alloc_server, NULL);
  sleep(1);
  pthread_create(&clientThread, NULL, &alloc_client, NULL);
  pthread_join(clientThread, NULL);

  return 0;
}