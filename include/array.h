/*
** EPITECH PROJECT, 2019
** qd
** File description:
** qd
*/

#ifndef ARRAY_H_
	#define ARRAY_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/wait.h>
    #include <assert.h>
    #include <errno.h>
    #include <string.h>
    #include <signal.h>
    #include "../include/proto.h"
    #include "../include/struct.h"

    const char * Command_name[] = {
        "cd",
        "setenv",
        "unsetenv",
        "env",
        "exit",
        NULL
    };

    void (* const Command[])(toolbox_t *) = {
        &fc_cd,
        &fc_setenv,
        &fc_unsetenv,
        &fc_env,
        &fc_exit,
        &fc_other
    };
#endif /* !ARRAY_H_ */
