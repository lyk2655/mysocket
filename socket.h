#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include "des.h"

#define BUF_SIZE 			20*1024

int k = 0;
/* 报文头结构 */
typedef struct _tabscale
{
        char Size[4];
        char txncode[6];
        char seqno[45];
}T;