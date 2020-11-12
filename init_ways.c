/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:32:35 by ksean             #+#    #+#             */
/*   Updated: 2020/11/06 15:32:38 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way				*init_way(unsigned int len)
{
	t_way *result;

	if (!(result = malloc(sizeof(t_way))))
		ft_printf("Eror with malloc way");
	result->way_len = len;
	result->way_nodes = malloc(sizeof(char **) * len);
	return (result);
}

t_group_handler		init_group_handler(void)
{
	t_group_handler	result;

	result.min_group = new_vector(0, sizeof(t_way));
	result.min_group_step = INT_MAX;
	result.result = NULL;
	return (result);
}
