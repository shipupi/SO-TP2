#ifndef PIPE_H
#define PIPE_H
#include <stdint.h>

void pipe_create(char * pipeid);
void pipe_delete(char * pipeid);
void pipe_read(char * pipeid , char * buffer , int messageSize);
void pipe_write(char * pipeid , char * buffer , int messageSize);

#endif