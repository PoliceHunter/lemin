/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:24:34 by ksean             #+#    #+#             */
/*   Updated: 2020/11/18 22:21:38 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char * parse_arguments(char ** av, t_vector * vec) {
    return (process_file(av[1], vec));
}

int print_help() {
    exit(0);
}

t_args init_args(int ac, char ** av) {
    t_args args;

    args.flag_way = FALSE;
    args.flag_help = FALSE;
    args.flag_steps = FALSE;

    while (ac != 1) {
        if (strcmp(av[ac], "-h") == 0)
            print_help();
        if (strcmp(av[ac], "-w") == 0)
            args.flag_way = TRUE;
        if (strcmp(av[ac], "-s") == 0)
            args.flag_steps = TRUE;
        --ac;
    }
    return args;
}

struct s_main_helper {
    t_character character;
    char * result;
    t_vector nodes_vec;
    char * map;
    int ants;
    t_vector ways;
};

typedef struct s_main_helper t_main_helper;

t_main_helper init_main_helper() {
    t_main_helper helper;
    helper.map = NULL;
    helper.result = NULL;
    helper.nodes_vec = new_vector(1, sizeof(t_node));
    return helper;
}

void solve_by_helper(char ** av, t_main_helper * helper) {
    helper->map = parse_arguments(av, &helper->nodes_vec);
    helper->character = get_character(&helper->nodes_vec);
    if (!(error_map_and_vec(&helper->character)))
        free_map_and_vec(&helper->nodes_vec, helper->map, STDERR_FILENO);
    helper->ants = *(int *) get_from_vec(&helper->character.root->ants, 0);
    helper->ways = solve(helper->character.root, &helper->ants, &helper->nodes_vec, &helper->result);
}

void print_by_helper(t_main_helper * helper, t_args * args) {
    if (args->flag_way)
        printf_ways(helper->ways);
    if (args->flag_steps)
        printf("%d", helper->ants);
}

void free_helper(t_main_helper * helper) {
    if (helper->result != NULL) {
        ft_printf("%s%s", helper->map, helper->result);
        free(helper->result);
    }
    free_map_and_vec(&helper->nodes_vec, helper->map, helper->result == NULL ? STDERR_FILENO : -1);
}

int main(int ac, char ** av) {
    t_args args;
    t_main_helper helper;

    args = init_args(ac, av);
    helper = init_main_helper();
    solve_by_helper(av, &helper);
    print_by_helper(&helper, &args);
    free_helper(&helper);
    return (0);
}
