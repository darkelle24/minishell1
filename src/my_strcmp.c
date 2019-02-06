/*
** EPITECH PROJECT, 2019
** lol
** File description:
** ll
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

int my_strcmp(char const *s1, char const *s2)
{
    int maj;

    while (*s1 != '=') {
        if (*s1 < *s2)
            return (-1);
        else if (*s1 > *s2)
            return (1);
        s1++;
        s2++;
    }
    return (0);
}