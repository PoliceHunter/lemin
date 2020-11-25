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

void disable_edge(t_edge * edge)
{
	edge->capacity = 0;
	edge->backward->capacity = 0;
	edge->mark = MARK_DISABLE;
}

void reset_edge(t_edge * edge)
{
	if (edge->mark == MARK_DISABLE)
	{
		edge->capacity = 0;
		edge->backward->capacity = 0;
		return;
	}

	edge->capacity = edge->original_capacity;
	edge->backward->capacity = edge->backward->original_capacity;
}

void direct_edge(t_edge * edge)
{
    ft_assert(edge->capacity == 1 && edge->backward->capacity == 1,
			  "You try to reduce wrong edge");

	edge->capacity = 0;
	edge->backward->capacity = 1;
//	printf("reduced edge: %s->%s(%d)\n", edge->backward->dst->name, edge->dst->name, edge->capacity);
}

void mark_edge(t_edge * edge)
{
	edge->mark = MARK_FORWARD_PATH;
	edge->backward->mark = MARK_BACKWARD_PATH;
}

void direct_and_mark_way_edges(t_way * way)
{
    t_edge	*edge;
	int		i;

	i = -1;
	while(++i != way->edges.size)
	{
	    edge = *(t_edge**)get_from_vec(&way->edges, i);
		if (edge->mark == MARK_BACKWARD_PATH || edge->mark == MARK_FORWARD_PATH)
		{
			disable_edge(edge);
			continue;
		}
		direct_edge(edge);
		mark_edge(edge);
	}
}

int is_have_reverse_edge(t_node_ptr node)
{
	t_edge	*edge;
	int		i;

	i = -1;
	while (++i < node->links.size)
	{
		edge = get_from_vec(&node->links, i);
		if (edge->mark != MARK_BACKWARD_PATH)
			continue;
		if (edge->capacity == 0)
			continue;
		return TRUE;
	}
	return FALSE;
}

void 			set_bfs_children(t_vector * queue, t_node_ptr current)
{
	t_edge *edge;
	int			i;

	i = -1;
	while (++i < current->links.size)
	{
		edge = get_from_vec(&current->links, i);
		if (edge->capacity == 0)
			continue;
		/// Если узел уже находится в пути(ях), тогда он нам интересен, только если
		/// у него есть реверсивный путь.
		//// TODO НО Необходимо проверить, что до него можно добраться !!!!
		if (edge->dst->traversal_state == STATE_IN_PATH
			&& is_have_reverse_edge(edge->dst))
		{
			edge->dst->bfs = current->bfs + 1;
			push_back_vec(queue, &edge->dst);
			continue;
		}

		if (edge->dst->traversal_state != STATE_NO_INVOLVED)
			continue;
		edge->dst->bfs = current->bfs + 1;
		edge->dst->traversal_state = STATE_IN_QUEUE;
		push_back_vec(queue, &edge->dst);
	}
}

void reset_state(t_vector * nodes, int except_mark)
{
	t_node_ptr	ptr;
	int			index;

	index = -1;

	while (++index < nodes->size)
	{
		ptr = get_from_node_vec(nodes, index);
		if (ptr->traversal_state != except_mark)
			ptr->traversal_state = STATE_NO_INVOLVED;
		ptr->bfs = 0;
		remove_all_not_free(&ptr->ants);
	}
}

int reset_all_states(t_vector * nodes)
{
	reset_state(nodes, STATE_NONE);
	return TRUE;
}

int continue_for_reconstruct(t_edge *edge, t_node_ptr ptr)
{
	if (edge->capacity == 0)
		return TRUE;
	if (ptr->is_end_node)
	{
		if (ptr->bfs != edge->dst->bfs)
			return TRUE;
	}
	if (edge->dst->bfs == 1)
	{
		if (edge->backward->dst->is_start_node != 1)
			return TRUE;
	}
	if (edge->backward->dst->bfs != ptr->bfs - 1 || edge->backward->dst->traversal_state == STATE_IN_PATH)
		return TRUE;
	return FALSE;
}

void finish_reconstruct(t_way *way, t_edge *edge, t_vector *nodes)
{
	push_front_vec(&way->nodes, &edge->backward->dst);
	direct_and_mark_way_edges(way);
	reset_state(nodes, STATE_IN_PATH);
}

int reconstruct_way(t_node_ptr ptr, t_way * way, t_vector * nodes)
{
	t_edge *edge = NULL;
	int i;

	ft_assert(ptr->is_end_node, "Error. Can reconstruct only from end node");
	*way = init_way();
	i = -1;
	while (++i < ptr->links.size)
	{
		edge = get_from_vec(&ptr->links, i);
		edge = edge->backward; // Берем все узлы, которые заходят в текущий
		ft_assert(edge != NULL, "Edges corrupted");
		if (continue_for_reconstruct(edge, ptr) == TRUE)
			continue;
		edge->dst->traversal_state = STATE_IN_PATH;
		push_front_vec(&way->nodes, &ptr);
		push_front_vec(&way->edges, &edge);
		if (edge->mark == MARK_BACKWARD_PATH)
			way->state = IS_CROSS;
		ptr = edge->backward->dst;
		i = - 1;
		if (edge->backward->dst->is_start_node) // SRC
		{
			finish_reconstruct(way, edge, nodes);
			return TRUE;
		}
	}
	return FALSE;
}


int 			find_by_bfs(t_node_ptr src, t_way * way, t_vector * nodes)
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
			ft_assert(reconstruct_way(*current, way, nodes), "Error while `reconstruct_way`");
			free_vec(&queue);
			return TRUE;
		}
		(*current)->traversal_state = STATE_VISITED;
		set_bfs_children(&queue, *current);
		free(current);
	}
	free_vec(&queue);
	return FALSE;
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
	t_node_ptr dst;

	way_i = -1;
	while (++way_i < ways.size) {
		way = get_from_vec(&ways, way_i);
		i = 0;
		while (++i < way->nodes.size) {
			t_node_ptr node = *(t_node_ptr *) get_from_vec(&way->nodes, i);

			if (node->is_end_node) {
				dst = node;
				continue;
			}

			if (node->ants.size != 0)
				*history = ft_strjoin_free(*history, ft_strjoin_free(ft_strjoin_free(
						ft_strjoin_free(ft_strjoin_free2("L", ft_itoa(*(int *) get_from_vec(&node->ants, 0))), "-"),
						node->name), " "));
		}
	}

	while (dst->ants.size != 0)
		*history = ft_strjoin_free(*history, ft_strjoin_free(
				ft_strjoin_free(ft_strjoin_free(ft_strjoin_free2("L", ft_itoa(*(int *) pop_back_vec(&dst->ants))), "-"),
								dst->name), " "));

	*history = ft_strjoin_free(*history, "\n");
}

int					process_way(t_way *way, t_ants_tracker *tracker,
						 int *previous_ways_len, const int index) {
	t_node_ptr curr;
	int ant;

	ant = 1 + tracker->all - tracker->ready_to_go;
	curr = *(t_node_ptr *) get_from_vec(&way->nodes, 1);
	if (make_way_step(way) > index)
		tracker->finished++;
	// Запускаю нового муравья на путь по его номеру
	if (tracker->ready_to_go > (way->nodes.size * index - *previous_ways_len))
	{
		push_back_vec(&curr->ants, &ant);
		tracker->ready_to_go--;
	}
	if (curr->is_end_node == 1) {
		tracker->finished++;
	}
	if (tracker->ready_to_go <= 0)
		return (TRUE);
	*previous_ways_len += way->nodes.size;
	return (FALSE);
}

unsigned int		get_rest_ant_step(t_ants_tracker tracker, t_vector *ways, char **history)
{
	unsigned int steps_count;
	int way_index;
	int finish_hp;

	finish_hp = 0;
    steps_count = 0;
    while (tracker.finished != tracker.all) {
		ft_assert(tracker.finished < tracker.all, "Too much finished ants");

		way_index = 0;
		while (way_index != ways->size) {
			finish_hp = make_way_step(get_from_vec(ways, way_index));
			way_index++;
		}
		printf("%d, %d, %d\n", tracker.finished, finish_hp, tracker.all);
		tracker.finished += finish_hp;
		////Посмотреть кол-во мурашей за шаг на финише (get_last->size)
		steps_count++;
		write_history(*ways, history);
	}

    return (steps_count);
}

// Принимает неперескающиеся пути
size_t get_ant_step(t_node_ptr src, int ants_count, t_vector ways, char ** way_history)
{
	int				previous_ways_len;
	t_ants_tracker	tracker;
    size_t			steps_count;
    int				index;

	tracker = init_tracker(ants_count);
	remove_from_vec(&src->ants, 0); // Очищаем вектор с муравьями в стартовой ноде
	steps_count = 0;
	while (tracker.ready_to_go != 0)
	{
		index = -1;
		previous_ways_len = 0;
		while (++index != ways.size && tracker.ready_to_go > 0) {
			if (process_way(get_from_vec(&ways, index),
							&tracker, &previous_ways_len, index))
				break;
		}
		write_history(ways, way_history);
		++steps_count;
	}
	if (tracker.ready_to_go == 0)
		steps_count += get_rest_ant_step(tracker, &ways, way_history);
	return steps_count;
}

void print_way(t_way * way)
{
	printf("way:\nnodes:");
	for (int i = 0; i != way->nodes.size; ++i) {
		t_node_ptr * ptr = get_from_vec(&way->nodes, i);
		printf("%s,", (*ptr)->name);
	}
	printf("\nedges:");
	for (int i = 0; i != way->edges.size; ++i) {
		t_edge ** ptr = get_from_vec(&way->edges, i);
		printf("%s->%s;", (*ptr)->backward->dst->name, (*ptr)->dst->name);
	}
	printf("\n");
}

void print_node(t_node_ptr node)
{
	//printf("%s in state %d\n", node->name, node->traversal_state);
	for (int i = 0; i != node->links.size; ++i) {
		t_edge * edge = get_from_vec(&node->links, i);
		ft_assert(ft_strcmp(node->name, edge->backward->dst->name) == 0, "Error edge");
		printf("[%d]%s == %s-->%s\n", i, node->name, edge->backward->dst->name, edge->dst->name);
		//printf("%s -> %s (cap: %d, mark: %d); ", node->name, edge->dst->name, edge->capacity, edge->mark);
	}
	printf("\n");
}

void print_nodes(t_vector * nodes)
{
	for (int i = 0; i != nodes->size; ++i) {
		t_node_ptr ptr = get_from_vec(nodes, i);
		print_node(ptr);
	}
}

void reset_all_edges(t_vector * nodes)
{
	t_edge		*edge;
	t_node_ptr	node;
	int			way_i;
	int			i;

	way_i = -1;
	reset_state(nodes, STATE_NONE);
	while (++way_i != nodes->size)
	{
		node = get_from_vec(nodes, way_i);
		i = -1;
		while (++i != node->links.size)
		{
			edge = get_from_vec(&node->links, i);
			reset_edge(edge);
		}
	}
}

void printf_ways(t_vector ways)
{
	int i;

	i = -1;
	while (++i != ways.size)
	{
		print_way((t_way *)get_from_vec(&ways, i));
	}
}

t_way *get_place_for_way(t_vector * vec)
{
	if (vec->size == vec->capacity)
		expand_vec(vec, vec->capacity * 2);
	++vec->size;
	return get_last(vec);
}

t_way *get_last_way(t_vector * vec)
{
	return get_last(vec);
}

typedef struct s_solver_helper t_solver_helper;
struct s_solver_helper
{
	char * best_history;
	size_t best_ant_step;

	char * current_history;
	size_t current_ant_step;
};

t_solver_helper init_helper()
{
	t_solver_helper res;
	res.best_ant_step = INT_MAX;
	res.current_ant_step = 0;
	res.best_history = NULL;
	res.current_history = NULL;

	return res;
}

void candidate_win(t_solver_helper * helper)
{
	if (helper->best_history != NULL)
		free(helper->best_history);
	helper->best_ant_step = helper->current_ant_step;
	helper->best_history = helper->current_history;
	helper->current_history = NULL;
	helper->current_ant_step = 0;
}

int try_candidate(t_solver_helper * helper, t_node_ptr src, int ants_count, t_vector ways)
{
	if ((helper->current_ant_step = get_ant_step(src, ants_count, ways, &helper->current_history)) < helper->best_ant_step)
	    candidate_win(helper);
	else
	{
		ft_strclr(helper->current_history);
		return FALSE;
	}

	return TRUE;
}

char * solve(t_node_ptr src, int ants_count, t_vector * nodes)
{
	t_vector	ways;
	int 		is_need_recalculate;
	t_solver_helper helper;

	helper = init_helper();
	is_need_recalculate = TRUE;
	while (reset_all_states(nodes))
	{
		ways = new_vector(10, sizeof(t_way));
		while (find_by_bfs(src, get_place_for_way(&ways), nodes) == TRUE)
		{
			if (get_last_way(&ways)->state == IS_CROSS)
				break;
			is_need_recalculate = try_candidate(&helper, src, ants_count, ways);
			src->bfs = 0;
//			printf("\nThis first\n\n\n\n");
//			printf_ways(ways);
		}
		printf("%s\n", helper.best_history);
		if (is_need_recalculate == FALSE)
			return helper.best_history;
		is_need_recalculate = FALSE;
		reset_all_edges(nodes);
		free_vec(&ways);
	}
	return NULL;
}
