/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksean <ksean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:24:33 by ksean             #+#    #+#             */
/*   Updated: 2020/11/19 00:11:24 by ksean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define IN_PATH 2

void 			set_bfs_children(t_vector * queue, t_node_ptr current, t_node_ptr dst) {
	t_node_ptr	*child;
	int			i;
dst = NULL; // заглушка
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


void un_mark_nodes(t_node_ptr src, t_node_ptr dst, t_node_ptr cur)
{
	t_node_ptr *child;
	int i;

	i = -1;
	while (++i < cur->links.size)
	{
		child = get_from_vec(&cur->links, i);
		if ((*child)->traversal_state == IN_PATH ||
			*child == dst || *child == src || (*child)->bfs == 0)
			continue;
		(*child)->traversal_state = NO_INVOLVED;
		(*child)->bfs = 0;
		un_mark_nodes(src, dst, *child);
	}
}

void un_mark_nodes_in_queue(t_vector * queue, t_node_ptr src, t_node_ptr dst)
{
	t_node_ptr *current;

	while (queue->size != 0)
	{
		current = pop_front_vec(queue);
		(*current)->traversal_state = NO_INVOLVED;
		un_mark_nodes(src, dst, *current);
	}
}

void mark_if_in_path(t_node_ptr dst, t_node_ptr src)
{
	t_node_ptr *parent = NULL;
	t_node_ptr prev = NULL;
	int i;
	int rev_bfs;

	i = -1;
	prev = dst;
	while (++i < prev->links.size)
	{
		rev_bfs = prev->bfs -1;
		parent = get_from_vec(&prev->links, i);
		if (*parent == src)
			return;
		if ((*parent)->bfs != rev_bfs)
			continue;
		else
		{
			prev = *parent;
			prev->traversal_state = IN_PATH;
			i = -1;
		}
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
		 if ((*current)->is_end_node)
		 {
			 //// Возникла проблема в поиске путей, а именно, у нас в бфс в очередь попадают узлы, не соединяющиеся с концом
			 //// Соответственно после выхода из очереди таких узлов им ставилась пометка, что они были задействованы "VISITED",
			 //// которая использовалась в поиске путей функция find_way_by_bfs 197 строчка
			 //// То, что мы тут делали до этого - помечали узлы как не посещенные если в очереди что то осталось
			 //// Я заглянул дальше, сначала в функции mark_if_in_path Я ставлю отметку если путь задействован в бфсе
			 //// После этого , я все незадействованные пути, которые были в очереди или уже вышли, помечаю как незадействованные функция un_mark_nodes_in_queue
			 //// Сейчас Вроде все ОК
		 	mark_if_in_path(*current, src);
		 	un_mark_nodes_in_queue(&queue, src, dst);
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
			{
				printf("Ways size %d\n", way->nodes.size);
				return TRUE;
			}

			if (current->traversal_state != IN_PATH)
				continue;

			current->traversal_state = NO_INVOLVED;
			if (min_bfs < current->bfs) {
				ptr = current;
				min_bfs = current->bfs;
				is_changed = TRUE;
			}
		}
	}
	printf("Ways size %d\n", way->nodes.size);
	free_ways(way);
	return FALSE;
}

char			*solve(t_node_ptr src, t_node_ptr dst)
{
	// t_vector	ways;
	// char		*result;

	src->bfs = 0;
	printf("BFS: %d\n", set_bfs(src, dst));

	// t_way  way;
	// printf("FIND_WAY: %d\n", find_way_by_bfs(src, &way));

	return "FUCK";
}
