/*
 *  nonblocking_server.c
 *
 *  Adapted from libLO nonblocking_server_example.c
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#include "lo/lo.h"
#include "synth.h"

int done = 0;

void error(int num, const char *m, const char *path);

int push_handler(const char *path, const char *types, lo_arg ** argv,
                int argc, void *data, void *user_data);

int runServer(Synth* synth) {
    int lo_fd;
    fd_set rfds;
#ifndef WIN32
    struct timeval tv;
#endif
    int retval;
    // Synth* synth = synth_new(44100, 5);

    /* start a new server on port 7770 */
    lo_server s = lo_server_new("7770", error);
    printf("Now listening on port 7770\n");

    /* add methods that will match the path /1/push*, with one int */
    int i;
    for (i = 1; i <= 12; i++) {
        char path[10];
        snprintf(path, 10, "/1/push%d", i);
        lo_server_add_method(s, path, "i", push_handler, synth);
    }

    /* get the file descriptor of the server socket, if supported */
    lo_fd = lo_server_get_socket_fd(s);

    if (lo_fd > 0) {
        /* select() on lo_server fd is supported, so we'll use select()
         * to watch both stdin and the lo_server fd. */
        do {

            FD_ZERO(&rfds);
#ifndef WIN32
            FD_SET(0, &rfds);   /* stdin */
#endif
            FD_SET(lo_fd, &rfds);

            retval = select(lo_fd + 1, &rfds, NULL, NULL, NULL);        /* no timeout */

            if (retval == -1) {
                printf("select() error\n");
                exit(1);
            } else if (retval > 0 && FD_ISSET(lo_fd, &rfds)) {
                lo_server_recv_noblock(s, 0);
            }

        } while (!done);

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

            retval = select(1, &rfds, NULL, NULL, &tv); /* timeout every 10ms */

            if (retval == -1) {
                printf("select() error\n");
                exit(1);
            }

            lo_server_recv_noblock(s, 0);

        } while (!done);
#endif
    }
    return 0;
}

int push_handler(const char *path, const char *types, lo_arg ** argv,
                int argc, void *data, void *user_data) {

    char *keystr = (char*) malloc(2);
    strncpy(keystr, path+7, strlen(path)-7);
    int key = atoi(keystr);
    int note_on = argv[0]->i;
    // printf("key: %d\n",key);
    // printf("note_on: %d\n\n", note_on);
    fflush(stdout);
    Synth* synth = (Synth*) user_data;
    if (note_on) {
        synth_on(key, synth);
    } else {
        synth_off(key, synth);
    }
    return 0;
}

void error(int num, const char *msg, const char *path) {
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
}

/* vi:set ts=8 sts=4 sw=4: */
