/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:24:33 by ksean             #+#    #+#             */
/*   Updated: 2020/11/15 12:37:04 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0



void 			set_bfs_children(t_vector * queue, t_node_ptr current, t_node_ptr dst) {
	t_node_ptr	*child;
	int			i;

	i = -1;
	while (++i < current->links.size)
	{
		child = get_from_vec(&current->links, i);
		if ((*child)->traversal_state != NO_INVOLVED)
			continue;

		(*child)->bfs = current->bfs + 1;
		(*child)->traversal_state = IN_QUEUE;
		push_back_vec(queue, child);
	}
}

int 			set_bfs(t_node_ptr src, t_node_ptr dst)
{
	t_node_ptr	* current;
	t_vector    queue;

	queue = new_vector(10, sizeof(t_node_ptr));
	push_back_vec(&queue, &src);

	while (queue.size != 0)
	{
		 current = pop_front_vec(&queue);
		 if ((*current)->traversal_state == VISITED)
			 continue;
		 if ((*current)->is_end_node) {
		     while (queue.size != 0) {
				 current = pop_front_vec(&queue);
				 (*current)->traversal_state = NO_INVOLVED;
		     }
			 free_vec(&queue);
			 return TRUE;
		 }
		 (*current)->traversal_state = VISITED;
		 set_bfs_children(&queue, *current, dst);
		 free(current);
	}

	free_vec(&queue);
	return FALSE;
}

char			*ft_strjoin_free3(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s2 != NULL)
		free(s2);
	if (s1 != NULL)
		free(s1);
	return (str);
}

//char			*get_ant_pos(const t_vector *ways)
//{
//	char			*result;
//	char			*node;
//	int				way_i;
//	unsigned int	i;
//	const t_way		*way;
//
//	way_i = -1;
//	result = NULL;
//	while (++way_i != ways->size)
//	{
//		i = 0;
//		way = get_from_vec_const(ways, way_i);
//		while (++i < way->way_len)
//		{
//			if (way->ants[i] != 0)
//			{
//				node = (!result) ? ft_strjoin_free2("L", ft_itoa(way->
//				ants[i])) : ft_strjoin_free2(" L", ft_itoa(way->ants[i]));
//				node = ft_strjoin_free(node, "-");
//				node = ft_strjoin_free(node, way->way_nodes[i]);
//				result = ft_strjoin_free3(result, node);
//			}
//		}
//	}
//	return (result);
//}

int find_unsorted(t_vector vec, char *name)
{
	int index;

	index = 0;
	t_node_ptr *ptr;

	while (index != vec.size)
	{
		ptr = get_from_vec(&vec, index);
		if (ft_strcmp((*ptr)->name, name) == 0)
			return index;
		index++;
	}
	return -1;
}

void delete_useles_links(t_node_ptr cur, t_node_ptr dst)
{
	t_node_ptr	*child;
	int			i;
	int 		remove;

	i = -1;
	while (++i < (cur)->links.size)
	{
		if (!(child = get_from_vec(&(cur)->links, i)))
			return;
		if ((*child) == dst)
			continue;
		remove = find_unsorted((*child)->links, cur->name);
		if (remove >= 0 && (*child)->bfs > cur->bfs)
			remove_from_vec(&(*child)->links, remove);
		if ((*child)->bfs == cur->bfs)
			remove_from_vec(&cur->links, i);
	}
	i = -1;
	while (++i < (cur)->links.size)
	{
		child = get_from_vec(&(cur)->links, i);
		if ((*child) == dst)
			continue;
		if ((*child)->is_start_node != 1 && (*child)->bfs > cur->bfs)
			delete_useles_links(*child, dst);
	}
}

int find_way_by_bfs(t_node_ptr ptr, t_way * way) {
	t_vector current_children;
	t_node_ptr current;
	int i;
	int min_bfs;
	int is_changed;

	*way = init_way();
	is_changed = TRUE;
	ptr->traversal_state = IN_QUEUE;

	while (is_changed) {
		is_changed = FALSE;
		push_back_vec(&way->nodes, ptr);
		i = -1;
		current_children = ptr->links;
		min_bfs = -1;
		while (++i < current_children.size) {
			current = *(t_node_ptr *) get_from_vec(&current_children, i);

			if (current->is_end_node) // TODO подумать, нужен ли в пути последний узел
				return TRUE;

			if (current->traversal_state != VISITED)
				continue;

			current->traversal_state = IN_QUEUE;
			if (min_bfs < current->bfs) {
				ptr = current;
				min_bfs = current->bfs;
				is_changed = TRUE;
			}
		}
	}

	free_ways(way);
	return FALSE;
}

char			*solve(t_node_ptr src, t_node_ptr dst)
{
	t_vector	ways;
	char		*result;

	src->bfs = 0;
	printf("BFS: %d\n", set_bfs(src, dst));

	t_way  way;
	printf("FIND_WAY: %d", find_way_by_bfs(src, &way));

	return "FUCK";
}
