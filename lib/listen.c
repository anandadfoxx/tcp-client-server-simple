#include "../include/listen.h"
#include "../include/chat_socket.h"
#include "../include/print.h"
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

void* listenChat(void* input) {
  struct chat_socket* data = (struct chat_socket*) input;
  char buff[255];

  sprintf(buff, "Listening to incoming message...");
  print_debug(input, buff, true);

  struct sockaddr_in* receive;

  if ((listen(data->socket_fd, 5)) != 0) {
    printf("Error listening, exiting...");
    return NULL;
  }

  int acc_sfd = accept(data->socket_fd, (struct sockaddr*)receive, (socklen_t*)sizeof(receive));
  while (1) {
    bzero(buff, sizeof(char)*255);
    recv(acc_sfd, buff, sizeof(char)*255, 0);
    char fin[600];
    sprintf(fin, "New message : %s", buff);
    print_debug(input, fin, true);
  }
}