/*
** EPITECH PROJECT, 2019
** dq
** File description:
** qdq
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

int my_strlen(char const *str)
{
    int nbchar = 0;

    while (str != NULL && str[nbchar] != '\0')
        nbchar++;
    return (nbchar);
}