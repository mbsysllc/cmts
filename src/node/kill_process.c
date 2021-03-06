#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <errno.h>

#include "config.h"
#include "kill_process.h"

void kill_converting_process(char *pid)
{
    char kill_cmd[16];
    char kill_result[128];
    FILE *pfp;

    memset(kill_result, 0, 128);
    memset(kill_cmd, 0, 16);

    snprintf(kill_cmd, 16, "kill -9 %s", pid);

    pfp = popen(kill_cmd, "r");
    if (!pfp) {
        printf("open cmd[%s] error: %s", kill_cmd, strerror(errno));
        return;
    }

    while(fgets(kill_result, sizeof(kill_result), pfp)){
    }

    pclose (pfp);
}

int kill_pid_handle(char *dst, char *msg)
{
    char *temp_pid = NULL;
    char *p = (char *)msg;

    p += strlen("pid=");
    temp_pid = p;
    while (*p != '\n' && *p != '\r') {
        p++;
    }
    *p = 0;
    p = temp_pid;
    kill_converting_process(p);
    printf("\t KILLPID: pid = %s", p);
    sprintf(dst, "killed pid=%s", p);

    if (strlen(dst) > strlen("killed pid=")) {
        return strlen(dst) - 1;
    } else {
        return 0;
    }
}


