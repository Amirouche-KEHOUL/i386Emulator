#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include </usr/include/linux/limits.h>

#include "../config.h"
#include "../status/status.h"

extern int status;

int str_length(char str[]);

/**
 * @brief Open a binary file as read only
 *
 * @param device_name (file name)
 * @return FILE*: file descriptor pointer
 */
FILE *open_file_ro(char *device_name);

void print_start(void);
void print_end(void);

#endif // _UTILS_H_
