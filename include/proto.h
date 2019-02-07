/*
** EPITECH PROJECT, 2019
** proto.h
** File description:
** proto.h
*/

#ifndef PROTO_H_
    #define PROTO_H_

    #include "../include/struct.h"

    int main(int ac, char **av, char **env);
    void test_command(toolbox_t *toolbox);
    void fc_other(toolbox_t *toolbox);
    void fc_exit(toolbox_t *toolbox);
    void fc_env(toolbox_t *toolbox);
    void fc_unsetenv(toolbox_t *toolbox);
    void fc_setenv(toolbox_t *toolbox);
    void fc_cd(toolbox_t *toolbox);
    void seperate_argument(char *str, toolbox_t *toolbox);
    void seperate_argument_2(char *str, toolbox_t *toolbox);
    int seperate_argument_3(char *str, toolbox_t *toolbox
    , int *count, int place);
    void free_agcv(toolbox_t *toolbox);
    toolbox_t *prep_toolbox(char **env);
    char **clone_env(char **env);
    char *clone_str(char *str);
    void exitspe(toolbox_t *toolbox);
    void print_prompt_sig_2(int sig);
    void print_prompt(void);
    void write_error(char *str);
    char **create_new_env(char **env, char *name, char *value);
    char **create_new_env_2(char **env, char *envadd, int size);
    char *init_str_env(char *name, char *value, char *envadd);
    int my_strcmp(char const *s1, char const *s2);
    int my_strlen(char const *str);
    int fcfind(toolbox_t *toolbox, char const *commande);

#endif /* !PROTO_H_ */
