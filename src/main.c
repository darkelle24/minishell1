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
#include "../include/array.h"

void my_perror(char *str, int erreur)
{
    char *str_erreur = strerror(erreur);

    write(2, str, my_strlen(str));
    write(2, ": ", 2);
    write(2, str_erreur, my_strlen(str_erreur));
    write(2, ".\n", 2);
}

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

void exitspe(toolbox_t *toolbox)
{
    write(1, "exit\n", 5);
    fc_exit(toolbox);
}

char *clone_str(char *str)
{
    char *clone_str = malloc(sizeof(char) * (my_strlen(str) + 1));
    int count = 0;

    if (clone_str == NULL)
        exit(84);
    while (str[count] != '\0') {
        clone_str[count] = str[count];
        count++;
    }
    clone_str[count] = '\0';
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
    toolbox->agcv = NULL;
    return (toolbox);
}

void free_agcv(toolbox_t *toolbox)
{
    int count = 0;

    if (toolbox->agcv != NULL) {
        while (toolbox->agcv[count] != NULL) {
            free(toolbox->agcv[count]);
            count++;
        }
        free(toolbox->agcv);
    }
    toolbox->agcv = NULL;
}

int seperate_argument_3(char *str, toolbox_t *toolbox, int *count, int place)
{
    int count2 = *count;
    int lenght = 0;

    while (str[count2] != ' ' && str[count2] != '\t' && str[count2] != '\n') {
        lenght++;
        count2++;
    }
    toolbox->agcv[place] = malloc(sizeof(char) * lenght + 1);
    if (toolbox->agcv[place] == NULL)
        exit(84);
    toolbox->agcv[place][lenght] = '\0';
    count2 = 0;
    while (str[*count] != ' ' && str[*count] != '\t'
    && str[*count] != '\n') {
        toolbox->agcv[place][count2] = str[*count];
        *count = *count + 1;
        count2++;
    }
    return (place + 1);
}

void seperate_argument_2(char *str, toolbox_t *toolbox)
{
    int count = 0;
    int place = 0;

    toolbox->agcv = malloc(sizeof(char *) * (toolbox->nbrarg + 1));
    if (toolbox->agcv == NULL)
        exit(84);
    toolbox->agcv[toolbox->nbrarg] = NULL;
    while (str[count] != '\0') {
        if (str[count] != ' ' && str[count] != '\t')
            place = seperate_argument_3(str, toolbox, &count, place);
        count++;
    }
}

void seperate_argument(char *str, toolbox_t *toolbox)
{
    int count = 0;

    toolbox->nbrarg = 0;
    free_agcv(toolbox);
    while (str[count] != '\0') {
        if (str[count] != ' ' && str[count] != '\t' && str[count] != '\n') {
            toolbox->nbrarg = toolbox->nbrarg + 1;
            while (str[count] != ' ' && str[count] != '\t'
            && str[count] != '\n')
                count++;
        }
        count++;
    }
    if (toolbox->nbrarg != 0)
        seperate_argument_2(str, toolbox);
}

void recupoldpwd(toolbox_t *toolbox)
{
    char *pwd = NULL;

    pwd = getcwd(pwd, 0);
    if (toolbox->oldpwd != NULL)
        free(toolbox->oldpwd);
    toolbox->oldpwd = pwd;
}

void cd_add(toolbox_t *toolbox, char *dest)
{
    char **save;
    int count = 0;

    if (chdir(dest) == -1) {
        my_perror(dest, errno);
    } else {
        dest = NULL;
        dest = getcwd(dest, 0);
        save = create_new_env(toolbox->env, "PWD", dest);
        free(dest);
        toolbox->env = save;
    }
}

void cd_back(toolbox_t *toolbox)
{
    char *save;

    if (toolbox->oldpwd != NULL) {
        save = clone_str(toolbox->oldpwd);
        recupoldpwd(toolbox);
        cd_add(toolbox, save);
        free(save);
    } else
        my_perror("", ENOENT);
}

int find(char *str, char *find)
{
    int count = 0;

    while (str[count] != '\0') {
        if (str[count] != find[count])
            return (0);
        count++;
    }
    return (1);
}

char *my_strcatspe(char *dest, char const *src)
{
    int count = 0;
    int count1 = 0;

    while (dest[count] != '\0') {
        count++;
    }
    if (count != 0 && dest[count-1] != '/') {
        dest[count] = '/';
        count++;
    }
    while (src[count1] != '\0') {
        dest[count] = src[count1];
        count++;
        count1++;
    }
    dest[count] = src[count1];
    return (dest);
}

char *cd_tilt_2(char *path, char *home)
{
    char *return_str = malloc(sizeof(char) * my_strlen(home)
    + my_strlen(path) + 1);
    int count = 0;

    if (return_str == NULL)
        exit(84);
    while (home[count] != '\0') {
        return_str[count] = home[count];
        count++;
    }
    return_str[count] = '\0';
    if (path != NULL)
        return_str = my_strcatspe(return_str, &path[1]);
    return (return_str);
}

void cd_tilt(toolbox_t *toolbox)
{
    int count = 0;
    char *str;

    while (toolbox->env[count] != NULL
    && find("HOME", toolbox->env[count]) == 0)
        count++;
    str = cd_tilt_2(toolbox->agcv[1], &toolbox->env[count][5]);
    cd_add(toolbox, str);
    free(str);
}

void fc_cd(toolbox_t *toolbox)
{
    if (toolbox->nbrarg > 2) {
        write(2, "cd: Too many arguments.\n", 24);
        return;
    }
    if (toolbox->agcv[1] != NULL && toolbox->agcv[1][0] == '-') {
        cd_back(toolbox);
    } else {
        recupoldpwd(toolbox);
        if (toolbox->agcv[1] == NULL || toolbox->agcv[1][0] == '~') {
            cd_tilt(toolbox);
        } else
            cd_add(toolbox, toolbox->agcv[1]);
    }
}

int check_alpha_num_without__(char *line, int count)
{
    while (line[count] != '\0') {
        if ((line[count] < '0' || line [count] > '9')
        && (line[count] < 'A' || line [count] > 'Z')
        && (line[count] < 'a' || line [count] > 'z') && line[count] != '_')
            return (1);
        count++;
    }
    return (0);
}

void fc_setenv_2(toolbox_t *toolbox)
{
    if (toolbox->nbrarg == 2)
        toolbox->env = create_new_env(toolbox->env, toolbox->agcv[1], "");
    else {
        toolbox->env = create_new_env(toolbox->env
        , toolbox->agcv[1], toolbox->agcv[2]);
    }
}

void fc_setenv_1(toolbox_t *toolbox)
{
    if (toolbox->agcv[1][0] >= '0' && toolbox->agcv[1][0] <= '9') {
        write(2, "setenv: The name of variable need to start with a letter.\n"
        , 58);
        return;
    } else if (check_alpha_num_without__(toolbox->agcv[1], 0) == 1) {
        write(2, "setenv: Variable name must contain alphanumeric characters.\n"
        , 60);
        return;
    }
    fc_setenv_2(toolbox);
}

void fc_setenv(toolbox_t *toolbox)
{
    if (toolbox->nbrarg == 1) {
        fc_env(toolbox);
        return;
    }
    if (toolbox->nbrarg > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        return;
    }
    fc_setenv_1(toolbox);
}

int size_str_str(char **str_str)
{
    int count = 0;

    while (str_str[count] != NULL)
        count++;
    return (count);
}

void destroy_env_2(toolbox_t *toolbox, int size)
{
    char **new_env = malloc(sizeof(char *) * (size + 1));
    int count = 0;
    int count2 = 0;

    if (new_env == NULL)
        exit(84);
    while (toolbox->env[count2] != NULL) {
        if (find(toolbox->agcv[1], toolbox->env[count2]) == 0) {
            new_env[count] = toolbox->env[count2];
            count++;
        }
        count2++;
    }
    free(toolbox->env);
    new_env[size] = NULL;
    toolbox->env = new_env;
}

void destroy_env(toolbox_t *toolbox)
{
    int count = 0;
    int size = 0;

    while (toolbox->env[count] != NULL
    && find(toolbox->agcv[1], toolbox->env[count]) == 0)
        count++;
    if (toolbox->env[count] != NULL) {
        size = size_str_str(toolbox->env) - 1;
        destroy_env_2(toolbox, size);
    }
}

void fc_unsetenv(toolbox_t *toolbox)
{
    if (toolbox->nbrarg == 1)
        write(2, "unsetenv: Too few arguments.\n", 29);
    else if (toolbox->nbrarg > 2)
        write(2, "unsetenv: Too much arguments.\n", 30);
    else
        destroy_env(toolbox);
}

void fc_env(toolbox_t *toolbox)
{
    int count = 0;

    while (toolbox->env[count] != NULL) {
        write(1, toolbox->env[count], my_strlen(toolbox->env[count]));
        write(1, "\n", 1);
        count++;
    }
}

void fc_exit(toolbox_t *toolbox)
{
    int count = 0;

    free_agcv(toolbox);
    while (toolbox->env[count] != NULL) {
        free(toolbox->env[count]);
        count++;
    }
    free(toolbox->env);
    if (toolbox->oldpwd != NULL)
        free(toolbox->oldpwd);
    free(toolbox);
    exit(0);
}

void fc_other(toolbox_t *toolbox)
{

}

void test_command(toolbox_t *toolbox)
{
    int count = 0;
    while (count < 6) {
        if (Command_name[count] != NULL && fcfind(toolbox, Command_name[count]))
            Command[count](toolbox);
        else if (Command_name[count] == NULL)
            Command[count](toolbox);
        count++;
    }
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
            seperate_argument(line, toolbox);
            free(line);
            line = NULL;
            if (toolbox->nbrarg != 0)
                test_command(toolbox);
            print_prompt();
        } else
            exitspe(toolbox);
    }
}