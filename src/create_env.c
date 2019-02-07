/*
** EPITECH PROJECT, 2019
** qdqd
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

char *init_str_env(char *name, char *value, char *envadd)
{
    int count2 = 0;
    int count3 = 0;

    while (name[count3] != '\0') {
        envadd[count2] = name[count3];
        count3++;
        count2++;
    }
    envadd[count2] = '=';
    count2++;
    count3 = 0;
    while (value[count3] != '\0') {
        envadd[count2] = value[count3];
        count3++;
        count2++;
    }
    envadd[count2] = '\0';
    return (envadd);
}

char **create_new_env_2(char **env, char *envadd, int size)
{
    char **new_env = malloc(sizeof(char *) * (size + 2));
    int count = 0;

    if (new_env == NULL)
        exit(84);
    while (env != NULL && env[count] != NULL) {
        new_env[count] = env[count];
        count++;
    }
    new_env[count] = envadd;
    new_env[count + 1] = NULL;
    free(env);
    return (new_env);
}

char **create_new_env(char **env, char *name, char *value)
{
    int count = 0;
    char *envadd = malloc(sizeof(char) * (my_strlen(name)
    + my_strlen(value) + 2));

    if (envadd == NULL)
        exit(84);
    while (env != NULL && env[count] != NULL
    && my_strcmp(env[count], name) != 0)
        count++;
    init_str_env(name, value, envadd);
    if (env == NULL || env[count] == NULL) {
        return (create_new_env_2(env, envadd, count));
    } else {
        free(env[count]);
        env[count] = envadd;
    }
    return (env);
}