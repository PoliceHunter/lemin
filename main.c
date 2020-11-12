/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:24:34 by ksean             #+#    #+#             */
/*   Updated: 2020/11/10 13:01:12 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*parse_arguments(char **av, t_vector *vec)
{
	return (process_file(av[1], vec));
}

int		main(int ac, char **av)
{
	t_character	character;
	t_vector	nodes_vec;
	char		*result;
	char		*map;

	map = NULL;
	result = NULL;
	if (ac > 2)
		return (0);
	nodes_vec = new_vector(1, sizeof(t_node));
	map = parse_arguments(av, &nodes_vec);
	character = get_character(&nodes_vec);
	if (!(error_map_and_vec(&character)))
		free_map_and_vec(&nodes_vec, map, 5);
	result = solve(character.root, character.target);
	if (result != NULL)
	{
		ft_printf("%s%s", map, result);
		free(result);
	}
	else
		free_map_and_vec(&nodes_vec, map, 6);
	free_map_and_vec(&nodes_vec, map, -1);
	return (0);
}