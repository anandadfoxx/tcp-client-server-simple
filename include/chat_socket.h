#ifndef CHATSOCKET_H
#define CHATSOCKET_H

struct chat_socket {
  int socket_fd;
  char* role;
  char buffer[255];
};

#endif