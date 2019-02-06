/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** minishell1
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

void write_error(char *str)
{
    write(2, str, my_strlen(str));
    write(2, "\n", 1);
}

void print_prompt(void)
{
    char *pwd = NULL;

    pwd = getcwd(pwd, 0);
    write(1, "\e[36m", 5);
    write(1, pwd, my_strlen(pwd));
    write(1, " ", 1);
    write(1, "\x1b[35m$>\x1b[0m ", 12);
    free(pwd);
}

void print_prompt_sig_2(int sig)
{
    write(1, "\n", 1);
    print_prompt();
}

void exitspe(void)
{
    write(1, "exit\n", 5);
    exit(0);
}

char *clone_str(char *str)
{
    char *clone_str = malloc(sizeof(char) * my_strlen(str) + 1);
    int count = 0;

    if (clone_str == NULL)
        exit(84);
    while (str[count] != '\0') {
        clone_str[count] = str[count];
        count++;
    }
    str[count] = '\0';
    return (clone_str);
}

char **clone_env(char **env)
{
    int count = 0;
    char **clone_env;

    while (env[count] != NULL)
        count++;
    clone_env = malloc(sizeof(char *) * (count + 1));
    if (clone_env == NULL)
        exit(84);
    clone_env[count] = NULL;
    count = 0;
    while (env[count] != NULL){
        clone_env[count] = clone_str(env[count]);
        count++;
    }
    return (clone_env);
}

toolbox_t *prep_toolbox(char **env)
{
    toolbox_t *toolbox = malloc(sizeof(toolbox_t) * 1);

    if (toolbox == NULL)
        exit(84);
    toolbox->env = clone_env(env);
    toolbox->oldpwd = NULL;
    return (toolbox);
}

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    size_t len = 0;
    int sig = 0;
    toolbox_t *toolbox = prep_toolbox(env);

    signal(SIGINT, print_prompt_sig_2);
    print_prompt();
    while (sig != -1) {
        sig = getline(&line, &len, stdin);
        if (sig != -1) {
            
            print_prompt();
        } else
            exitspe();
    }
}