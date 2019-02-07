/*
** EPITECH PROJECT, 2019
** qd
** File description:
** qd
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "../include/struct.h"
#include "../include/proto.h"

int fcfind(toolbox_t *toolbox, char const *commande)
{
    int count = 0;

    while (commande[count] != '\0') {
        if (commande[count] != toolbox->agcv[0][count])
            return (0);
        count++;
    }
    return (1);
}