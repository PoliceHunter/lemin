/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addapt_vector2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:30:10 by ksean             #+#    #+#             */
/*   Updated: 2020/11/06 23:30:18 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	*get_from_vec(t_vector *vec, int index)
{
	if (index >= vec->size)
		return (NULL);
	return (vec->data + (index * vec->elem_size));
}

void	printf_node_vec(t_vector *vec)
{
	int i;

	i = 0;
	while (i != vec->size)
	{
		ft_printf("\"%s\",\n", get_from_node_vec(vec, i)->name);
		i++;
	}
}

void	emplace_front_node_vec(t_vector *vec, t_node node)
{
	return (emplace_front_vec(vec, &node));
}

void	emplace_back_node_vec(t_vector *vec, t_node node)
{
	return (emplace_back_vec(vec, &node));
}

int		insert_into_node_vec(t_vector *vec, size_t index, t_node node)
{
	return (insert_into_vec(vec, index, &node));
}
