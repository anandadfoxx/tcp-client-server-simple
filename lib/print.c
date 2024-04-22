#include "../include/print.h"
#include <stdio.h>
#include <stdbool.h>

void print_debug(void* input, char* msg, bool newline) {
  struct chat_socket* data = (struct chat_socket*) input;
  printf((newline) ? "%s | %s\n" : "%s | %s", data->role, msg);
}