#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "lo/lo.h"
#include "../headers/synth.h"

#define NUM_KEYS (12)
#define DONE (0)

void error(int num, const char *m, const char *path);

void readStdIn(void);

int generic_handler(const char *path, const char *types, lo_arg ** argv,
                    int argc, void *data, void *user_data);

int generic_handler(const char *path, const char *types, lo_arg ** argv,
                    int argc, void *data, void *user_data)
{
    (void) data;
    (void) user_data;
    int i;

    printf("path: <%s>\n", path);
    for (i = 0; i < argc; i++) {
        printf("arg %d '%c' ", i, types[i]);
        lo_arg_pp((lo_type)types[i], argv[i]);
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

    return 1;
}

void readStdIn(void) {
    char buf[256];
    int len = read(0, buf, 256);
    if (len > 0) {
        printf("stdin: ");
        fwrite(buf, len, 1, stdout);
        printf("\n");
        fflush(stdout);
    }
}

int main() {
    int lo_fd;
    fd_set rfds;
    #ifndef WIN32
    struct timeval tv;
    #endif
    int retval;

    /* start a new server on port 7770 */
    lo_server s = lo_server_new("7770", error);
    printf("Now listening on port 7770\n");

    lo_server_add_method(s, NULL, NULL, generic_handler, NULL);

    /* get the file descriptor of the server socket, if supported */
    lo_fd = lo_server_get_socket_fd(s);

    if (lo_fd > 0) {
        /* select() on lo_server fd is supported, so we'll use select()
         * to watch both stdin and the lo_server fd. */
        do {
            FD_ZERO(&rfds);
            #ifndef WIN32
            FD_SET(0, &rfds); // stdin
            #endif
            FD_SET(lo_fd, &rfds);
            
            retval = select(lo_fd + 1, &rfds, NULL, NULL, NULL); // no timeout
            
            if (retval == -1) {
                printf("select() error\n");
                exit(1);
            } else if (retval > 0) {
                if (FD_ISSET(0, &rfds)) {
                    readStdIn();
                }
                if (FD_ISSET(lo_fd, &rfds)) {
                    lo_server_recv_noblock(s, 0);
                }
            }
        } while (!DONE);
    } else {
        /* lo_server protocol does not support select(), so we'll watch
         * stdin while polling the lo_server. */
        #ifdef WIN32
        printf
            ("non-blocking input from stdin not supported under Windows\n");
        exit(1);
        #else
        do {
            FD_ZERO(&rfds);
            FD_SET(0, &rfds);
            tv.tv_sec = 0;
            tv.tv_usec = 10000;

            retval = select(1, &rfds, NULL, NULL, &tv); // timeout every 10ms

            if (retval == -1) {
                printf("select() error\n");
                exit(1);
            } else if (retval > 0 && FD_ISSET(0, &rfds)) {
                readStdIn();
            }

            lo_server_recv_noblock(s, 0);
        } while (!DONE);
        #endif
    }
    return 0;
}
