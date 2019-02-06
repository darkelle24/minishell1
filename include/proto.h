/*
** EPITECH PROJECT, 2019
** proto.h
** File description:
** proto.h
*/

#ifndef PROTO_H_
    #define PROTO_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/wait.h>
    #include <assert.h>
    #include <errno.h>
    #include <string.h>
    #include <signal.h>
    #include "../include/struct.h"

    int my_strlen(char const *str);
    int my_strcmp(char const *s1, char const *s2);
    char **fcenv(char *line, int count, char **env);
    char *my_strcatspe(char *dest, char const *src);
    int do_it(char *dest, char const *src, int n, int count);
    char *my_strncpy(char *dest, char const *src, int n, int avance);
    int test_bin(char **arg);
    char *recup(char *env, int count, char *str);
    char *test_if_binnat_2(char *env, char **arg, int count_word, int count2);
    char *test_if_binnat(char **arg, char **env);
    void print_segfault(int sig);
    char *create_arg_2(int count, int *countletter, char *line, char *arg);
    char *create_arg_3(int count, int *countletter, char *line, char *arg);
    char **create_arg1(char *line, int countletter, char **arg, int count2);
    char **create_arg(char *line, int countword, int count2, int countletter);
    void error_write_exe(char **arg);
    char **check_path(char **env);
    int error_check_and_binarie(char **arg, char **env);
    void part_for_child_process(char **arg, char **env);
    int part_for_parent_process(char **arg, char **env, pid_t pid);
    int forkfc(char **arg, char **env);
    int execprogram_2(char **env, char *line, int countword);
    int execprogram(char *line, char **env);
    int fcfind(char *line, int count, char *commande);
    char **destroy_new_env_2(int pas, char **new_env, char *name, char **env);
    char **destroy_new_env(char **env, char *name);
    char *init_str_env(char *name, char *value, char *envadd);
    char **create_new_env_2(char **env, char *envadd, int size);
    char **create_new_env(char **env, char *name, char *value);
    char **fcsetenv_with_argument(int count, char *line, char **env);
    int check_alpha_num_without__(char *line, int count);
    char **fcsetenv_with_argument_2(int count2, char *line
    , char *name, char **env);
    int fcsetenv_with_argument_2_1(char *line, int count2);
    char *fcsetenv_with_argument_1(int *count, char *line);
    char **fcsetenv(char *line, int count, char **env);
    char **cd_add(char **env, char *dest, char *path);
    int fccd_1(char *line, int *count);
    char *fccd_2(int count_letter, char **dest);
    void recupoldpwd(toolbox_t *toolbox);
    char *fccd_strcont(char *dest, char *src);
    char **fccd_spe_minus(char **env, toolbox_t *toolbox, char *path);
    char *fccd_3_tiltd(char *path, char *home);
    char **fccd_3(char *path, char *dest, char **env, toolbox_t *toolbox);
    char **fccd(char *line, int count, char **env, toolbox_t *toolbox);
    char *fcunsetenv_1(char *line, int count2, int *count);
    char **fcunsetenv(char *line, int count, char **env);
    char **fccheck(char *line, toolbox_t *toolbox);
    void write_error(char *str);
    void print_prompt(void);
    void print_prompt_sig_2(int sig);
    void exitspe(void);


#endif /* !PROTO_H_ */
