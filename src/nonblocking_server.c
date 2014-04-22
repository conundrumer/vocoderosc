/*
 *  nonblocking_server_example.c
 *
 *  This code demonstrates two methods of monitoring both an lo_server
 *  and other I/O from a single thread.
 *
 *  Copyright (C) 2014 Steve Harris et al. (see AUTHORS)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation; either version 2.1 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  $Id$
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

int quit_handler(const char *path, const char *types, lo_arg ** argv,
                 int argc, void *data, void *user_data);

void read_stdin(void);

int main()
{
    int lo_fd;
    fd_set rfds;
#ifndef WIN32
    struct timeval tv;
#endif
    int retval;
    Synth* synth = synth_new(44100, 5);

    /* start a new server on port 7770 */
    lo_server s = lo_server_new("7770", error);

    /* add methods that will match the path /1/push*, with one int */
    int i;
    for (i = 1; i <= 12; i++) {
        char path[10];
        snprintf(path, 10, "/1/push%d", i);

        lo_server_add_method(s, path, "i", push_handler, synth);
    }

    /* add method that will match the path /quit with no args */
    lo_server_add_method(s, "/quit", "", quit_handler, NULL);

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

            } else if (retval > 0) {

                if (FD_ISSET(0, &rfds)) {

                    read_stdin();

                }
                if (FD_ISSET(lo_fd, &rfds)) {

                    lo_server_recv_noblock(s, 0);

                }
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

            } else if (retval > 0 && FD_ISSET(0, &rfds)) {

                read_stdin();

            }

            lo_server_recv_noblock(s, 0);

        } while (!done);
#endif
    }

    return 0;
}

void error(int num, const char *msg, const char *path)
{
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
}

int push_handler(const char *path, const char *types, lo_arg ** argv,
                int argc, void *data, void *user_data)
{
    char *keystr = (char*) malloc(2);
    strncpy(keystr, path+7, strlen(path)-7);
    int key = atoi(keystr);
    int note_on = argv[0]->i;
    printf("%d\n",key);
    printf("note_on: %d\n\n", note_on);
    fflush(stdout);
    Synth* synth = (Synth*) user_data;
    synth_on(key, synth);
    return 0;
}

int quit_handler(const char *path, const char *types, lo_arg ** argv,
                 int argc, void *data, void *user_data)
{
    done = 1;
    printf("quiting\n\n");

    return 0;
}

void read_stdin(void)
{
    char buf[256];
    int len = read(0, buf, 256);
    if (len > 0) {
        printf("stdin: ");
        fwrite(buf, len, 1, stdout);
        printf("\n");
        fflush(stdout);
    }
}

/* vi:set ts=8 sts=4 sw=4: */
