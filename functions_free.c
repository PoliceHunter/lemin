/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:31:38 by ksean             #+#    #+#             */
/*   Updated: 2020/11/06 23:38:02 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_node(t_node *node)
{
	free_vec(&node->links);
	free_vec(&node->ants);
	if (node->name)
	{
		free(node->name);
		node->name = NULL;
	}
}

void	free_vec_node(t_vector *vec)
{
	int i;

	i = 0;
	while (i != vec->size)
	{
		free_node(get_from_node_vec(vec, i));
		i++;
	}
	free_vec(vec);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
