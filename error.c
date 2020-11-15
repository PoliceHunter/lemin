/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:20:55 by ksean             #+#    #+#             */
/*   Updated: 2020/11/09 20:29:33 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		error_map_and_vec(t_character *character)
{
	if (character->root == NULL || character->target == NULL)
	{
		perror("Error\n");
		return (0);
	}
	if (character->target->links.size == 0 || character->root->links.size == 0)
	{
		perror("Error\n");
		return (0);
	}
	return (1);
}

int		read_flags(char **av, int ac)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i != ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][j] == '-' && av[i][j + 1] == 'h')
				ft_printf("Usage: ./lem_in < txt.map -flag(h/p)");
			if (av[i][j] == '-' && av[i][j + 1] == 'p')
				return (2);
			j++;
		}
		i++;
	}
	exit(1);
}

void	free_map_and_vec(t_vector *vec, char *map, int error_num)
{
	free(map);
	map = NULL;
	free_vec_node(vec);
	if (error_num == -1)
		return ;
	exit(error_num);
}
