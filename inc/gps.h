#ifndef __GPS_H__
#define __GPS_H__


#include "uart.h"
#include <stdlib.h>
#include <string.h>

void get_sentence(char c);
void parse_sentence(char c);
void filter_incomings();


#endif