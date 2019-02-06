/*
** EPITECH PROJECT, 2019
** struct.h
** File description:
** struct.h
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    typedef struct toolbox
    {
        char **env;
        char *oldpwd;
        char **agcv;
        int nbrarg;
    }       toolbox_t;
#endif /* !STRUCT_H_ */
