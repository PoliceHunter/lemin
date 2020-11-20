/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:32:35 by ksean             #+#    #+#             */
/*   Updated: 2020/11/18 22:56:59 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way				init_way(unsigned int len)
{
	len = 0;
	t_way result;
	result.nodes = new_vector(100, sizeof(t_node_ptr));
	result.edges = new_vector(100, sizeof(t_edge*));
	return result;
}

