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

char	*parse_arguments(char **av, t_vector *vec)
{
	return (process_file(av[1], vec));
}

int		main(int ac, char **av) ///28/25
{
	t_character	character;
	t_vector	nodes_vec;
	char		*result;
	char		*map;
	int			steps;

	map = NULL;
	result = NULL;
	ac = 1;
	nodes_vec = new_vector(1, sizeof(t_node));
	map = parse_arguments(av, &nodes_vec);
	character = get_character(&nodes_vec);
	if (!(error_map_and_vec(&character)))
	{
		free_map_and_vec(&nodes_vec, map, STDERR_FILENO);
		return (0);
	}
	steps = solve(character.root, *(int *)
	get_from_vec(&character.root->ants, 0), &nodes_vec, &result);
	if (result != NULL)
	{
		ft_printf("%s\n%s", map, result);
		free(result);
	}
	else
		free_map_and_vec(&nodes_vec, map, STDERR_FILENO);
	free_map_and_vec(&nodes_vec, map, -1);
	return (0);
}
