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

void ft_assert(int result, const char * error) {
	if (result == FALSE) {
		printf("%s\n", error);
		exit(-1);
	}
}

void disable_link(t_edge * edge)
{
	edge->capacity = 0;
	edge->backward->capacity = 0;
}

void reset_edge(t_edge * edge)
{
	edge->capacity = edge->original_capacity;
	edge->backward->capacity = edge->backward->original_capacity;
}

void reduce_edge(t_edge * edge, const int diff)
{
	edge->capacity -= diff;
	edge->backward->capacity += diff;
}

void reduce_way(t_way * way, const int diff)
{
	int i;
	i = -1;

	while(++i != way->edges.size)
	{
		reduce_edge(get_from_vec(&way->edges, i), diff);
	}
}

void 			set_bfs_children(t_vector * queue, t_node_ptr current, t_node_ptr dst)
{
	t_edge *edge;
	int			i;

	i = -1;
	while (++i < current->links.size)
	{
		edge = get_from_vec(&current->links, i);
		if (edge->capacity == 0 || edge->dst->traversal_state != STATE_NO_INVOLVED)
			continue;

		edge->dst->bfs = current->bfs + 1;
		edge->dst->traversal_state = STATE_IN_QUEUE;
		push_back_vec(queue, edge);
	}
}


int reconstruct_way(t_node_ptr dst, t_way * way)
{
	t_edge *edge = NULL;
	t_node_ptr ptr = NULL;
	int i;

	*way = init_way();
	ptr = dst;
	i = -1;
	push_front_vec(&way->nodes, &dst);
	while (++i < ptr->links.size)
	{
		edge = get_from_vec(&ptr->links, i);

		ft_assert(edge != NULL, "Edges corrupted.");

		if (edge->dst->is_start_node) // SRC
		{
			reduce_edge(edge, 1);
			edge->dst->traversal_state = STATE_IN_PATH;
			push_front_vec(&way->nodes, &ptr);
			push_front_vec(&way->edges, edge);
			return TRUE;
		}
		if (edge->dst->bfs != ptr->bfs - 1) // NO
			continue;
		else // IN PATH
		{
			reduce_edge(edge, 1);
			push_front_vec(&way->nodes, &ptr);
			push_front_vec(&way->edges, edge);
			ptr = edge->dst;
			ptr->traversal_state = STATE_IN_PATH;
			i = -1;
		}
	}

	return FALSE;
}


int 			set_bfs(t_node_ptr src, t_node_ptr dst, t_way * way)
{
	t_node_ptr	* current;
	t_vector    queue;

	queue = new_vector(10, sizeof(t_node_ptr));
	push_back_vec(&queue, &src);

	while (queue.size != 0)
	{
		 current = pop_front_vec(&queue);
		 if ((*current)->traversal_state == STATE_VISITED)
			 continue;
		if ((*current)->is_end_node)
		 {
			ft_assert(reconstruct_way(*current, way), "Error while `reconstruct_way`");
		 	free_vec(&queue);
		 	return TRUE;
		 }
		 (*current)->traversal_state = STATE_IN_PATH;
		 set_bfs_children(&queue, *current, dst);
		 free(current);
	}

	free_vec(&queue);
	return FALSE;
}

int 			set_bfs_hacked(t_node_ptr src, t_node_ptr dst, t_vector * selected_edges, t_way * way)
{
	t_node_ptr	* current;
	t_vector    queue;

	queue = new_vector(10, sizeof(t_node_ptr));
	push_back_vec(&queue, &src);

	while (queue.size != 0)
	{
		current = pop_front_vec(&queue);
		if ((*current)->traversal_state == STATE_VISITED)
			continue;
		if ((*current)->is_end_node)
		{
			ft_assert(reconstruct_way(*current, way), "Error while `reconstruct_way`");
			free_vec(&queue);
			return TRUE;
		}
		(*current)->traversal_state = STATE_IN_PATH;
		set_bfs_children(&queue, *current, dst);
		free(current);
	}

	free_vec(&queue);
	return FALSE;
}

void reset_state(t_vector * nodes, size_t except_mark) {
	t_node_ptr ptr;
	size_t index;

	index = -1;

	while (++index < nodes->size) {
	    ptr = get_from_node_vec(nodes, index);
		if (ptr->traversal_state != except_mark) {
			ptr->traversal_state = STATE_NO_INVOLVED;
		}

		ptr->bfs = 0;
	}
}

typedef struct s_ant_tracker t_ants_tracker;
struct s_ant_tracker {
	int finished;
	int ready_to_go;
	int all;
};

t_ants_tracker init_tracker(size_t count) {
	t_ants_tracker result;
	result.ready_to_go = count;
	result.all = count;
	result.finished = 0;
	return result;
}

void				write_history(t_vector ways, char **history)
{
	int way_i;
	t_way * way;
	int i;

	way_i = -1;
	while (++way_i < ways.size)
	{
		way = get_from_vec(&ways, way_i);
		i = -1;

		while (++i < way->nodes.size - 1) {
			t_node_ptr node = *(t_node_ptr*)get_from_vec(&way->nodes, i);

			if (node->is_end_node && way_i != ways.size - 1)
				continue;
			if (node->ant_number != NO_ANT)
				*history = ft_strjoin_free(*history, ft_strjoin_free(ft_strjoin_free(ft_strjoin_free(ft_strjoin_free2("L", ft_itoa(node->ant_number)), "-"), node->name), " "));
		}
	}

	*history = ft_strjoin_free(*history, "\n");
}

int					process_way(t_way *way, t_ants_tracker *tracker,
						unsigned int *previous_ways_len, const int index)
{
	if (make_way_step(way) != NO_ANT)
		++tracker->finished;
	// Запускаю нового муравья на путь по его номеру
	if (tracker->ready_to_go > (way->nodes.size * index - *previous_ways_len))
		(*(t_node_ptr*)get_first(&way->nodes))->ant_number = 1 + tracker->all - tracker->ready_to_go--;
	if (tracker->ready_to_go <= 0)
		return (TRUE);
	*previous_ways_len += way->nodes.size;
	return (FALSE);
}

unsigned int		get_rest_ant_step(t_ants_tracker tracker, t_vector *ways, char **history)
{
    unsigned int	steps_count;
    int				index;

    steps_count = 0;
    while (tracker.finished != tracker.all)
    {
        index = 0;
        while (index != ways->size)
        {
			if (make_way_step(get_from_vec(ways, index)) != NO_ANT)
				++tracker.finished;
            index++;
        }
        write_history(*ways, history);
    }

    return (steps_count);
}

// Принимает неперескающиеся пути
size_t get_ant_step(t_node_ptr src, t_vector ways, char ** way_history) {
	unsigned int previous_ways_len;
	t_ants_tracker tracker;
    size_t steps_count;
    int index;

	tracker = init_tracker(src->ant_number);
	src->ant_number = NO_ANT;
	steps_count = 0;

	while (tracker.ready_to_go != 0)
	{
		index = 0;
		previous_ways_len = 0;
		while (index != ways.size && tracker.ready_to_go > 0)
		{
			if (process_way(get_from_vec(&ways, index),
							&tracker, &previous_ways_len, index))
				break ;
			++index;
		}
		write_history(ways, way_history);
		++steps_count;
	}

	steps_count += get_rest_ant_step(tracker, &ways, way_history);

	return steps_count;
}

char			*solve(t_node_ptr src, t_node_ptr dst, t_vector * nodes)
{
	t_way 		way;
	t_vector 	ways;

	ways = new_vector(10, sizeof(t_way));

	src->bfs = 0;
	reset_state(nodes, STATE_NONE);

	ft_assert(set_bfs(src, dst, &way), "Error while getting bfs");
	reset_state(nodes, STATE_IN_PATH);
	reduce_way(&way, 1);
	push_back_vec(&ways, &way);

	char * history = NULL;
	size_t ant_step = get_ant_step(src, ways, &history);
	printf("%s\n", history);

	return "FUCK";
}
