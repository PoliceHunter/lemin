/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:24:34 by ksean             #+#    #+#             */
/*   Updated: 2020/11/29 16:49:55 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char			*parse_arguments(t_vector *vec)
{
	return (process_file(vec));
}

t_args			init_args(int ac, char **av)
{
	t_args	args;
	int		i;

	i = 1;
	args.flag_way = FALSE;
	args.flag_help = FALSE;
	args.flag_steps = FALSE;
	while (i != ac)
	{
		if (ft_strcmp(av[i], "-h") == 0)
			print_help();
		if (ft_strcmp(av[i], "-w") == 0)
			args.flag_way = TRUE;
		if (ft_strcmp(av[i], "-s") == 0)
			args.flag_steps = TRUE;
		i++;
	}
	return (args);
}

void			solve_by_helper(t_main_helper *helper)
{
	helper->map = parse_arguments(&helper->nodes_vec);
	helper->character = get_character(&helper->nodes_vec);
	if (!(error_map_and_vec(&helper->character)))
		free_map_and_vec(&helper->nodes_vec, helper->map, STDERR_FILENO);
	helper->ants = *(int *)get_from_vec(&helper->character.root->ants, 0);
	helper->ways = solve(helper->character.root, &helper->ants,
				&helper->nodes_vec, &helper->result);
	if (helper->ways.size == 0 || helper->ants == 0)
	{
		free_ways(&helper->ways);
		ft_printf("Error");
		free_map_and_vec(&helper->nodes_vec, helper->map, STDERR_FILENO);
	}
}

void			free_helper(t_main_helper *helper, t_args args)
{
	if (helper->result != NULL)
	{
		ft_printf("%s\n%s", helper->map, helper->result);
		free(helper->result);
	}
	print_by_helper(helper, &args);
	free_map_and_vec(&helper->nodes_vec, helper->map,
				helper->result == NULL ? STDERR_FILENO : -1);
	free_ways(&helper->ways);
}

int				main(int ac, char **av)
{
	t_args			args;
	t_main_helper	helper;

	args = init_args(ac, av);
	helper = init_main_helper();
	solve_by_helper(&helper);
	free_helper(&helper, args);
	return (0);
}
