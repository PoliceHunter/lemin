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

void print_way(t_way * way) //// Can add to give bonus points
{
	for (int i = 0; i != way->nodes.size; ++i) {
		t_node_ptr * ptr = get_from_vec(&way->nodes, i);
		printf("%s,", (*ptr)->name);
	}
	printf("\nedges:");
	for (int i = 0; i != way->edges.size; ++i) {
		t_edge ** ptr = get_from_vec(&way->edges, i);
		printf("%s-(%d)->%s;", (*ptr)->backward->dst->name, (*ptr)->capacity, (*ptr)->dst->name);
	}
	printf("\nsize: %d", way->nodes.size);
	printf("\n");
}

void printf_ways(t_vector ways) //// Can add to give bonus points
{
	int i;

	i = -1;
	while (++i != ways.size)
	{
		printf("way %d:\n", i);
		print_way((t_way *) get_from_vec(&ways, i));
	}
}

void ft_assert(int result, const char * error)
{
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
	edge->backward->mark = MARK_DISABLE;
}

void reset_edge(t_edge * edge)
{
	if (edge->mark == MARK_DISABLE || edge->backward->dst->is_first_cross == TRUE) {
		//printf("Edge disabled: %s->%s\n", edge->backward->dst->name, edge->dst->name);
		edge->capacity = 0;
		edge->backward->capacity = 0;
		return;
	}

	edge->capacity = edge->original_capacity;
	edge->backward->capacity = edge->backward->original_capacity;
	edge->mark = MARK_NONE;
}

void direct_edge(t_edge * edge)
{
    ft_assert(edge->capacity == 1 && edge->backward->capacity == 1,
			  "You try to reduce wrong edge");

	edge->capacity = 0;
	edge->backward->capacity = 1;
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
	while (++i != way->edges.size) {
		edge = *(t_edge **) get_from_vec(&way->edges, i);
		if ((edge->backward->dst->is_cross == 1 || edge->backward->dst->is_first_cross == TRUE) && edge->dst->is_cross) { //|| edge->dst->is_first_cross == TRUE)
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
		if (edge->mark != MARK_BACKWARD_PATH || edge->capacity == 0)
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
	while (++i < current->links.size) {
		edge = get_from_vec(&current->links, i);

		if (edge->capacity == 0)
			continue;
		if (current->is_cross && edge->mark != MARK_BACKWARD_PATH) // Change
			continue;
		if (edge->dst->traversal_state == STATE_IN_PATH
			&& is_have_reverse_edge(edge->dst)) {
			if (edge->dst->bfs != 0)
				continue;
			edge->dst->bfs = current->bfs + 1;
			edge->dst->is_first_cross = TRUE;
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
		if (except_mark == STATE_NONE)
		{
			ptr->is_first_cross = FALSE;
			ptr->is_cross = 0;
		}
		remove_all_not_free(&ptr->ants);
	}
}

int reset_all_states(t_vector * nodes)
{
	reset_state(nodes, STATE_NONE);
	return TRUE;
}

int is_skip_in_reconstruction(t_edge * edge, t_node_ptr src) {
	if (edge->capacity == 0)
		return TRUE;
	if (edge->dst->bfs == 1) {
		if (edge->backward->dst->is_start_node != 1)
			return TRUE;
	}

	if (edge->backward->dst->is_cross && edge->backward->capacity == 0) // src of edge is in path // add second if
		return edge->mark != MARK_BACKWARD_PATH;

	return (edge->backward->dst->bfs != src->bfs - 1 || edge->backward->dst->traversal_state != STATE_VISITED);
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
	while (++i < ptr->links.size) {
		edge = get_from_vec(&ptr->links, i);
		edge = edge->backward; // Берем все узлы, которые заходят в текущий

		ft_assert(edge != NULL, "Edges corrupted");
		if (is_skip_in_reconstruction(edge, ptr) == TRUE)
			continue;
		edge->dst->traversal_state = STATE_IN_PATH;
		push_front_vec(&way->nodes, &ptr);
		push_front_vec(&way->edges, &edge);
		if (edge->mark == MARK_BACKWARD_PATH || edge->backward->dst->is_first_cross == TRUE) // || edge->backward->dst->is_cross)
			way->state = IS_CROSS;
		//ft_assert(edge->mark == MARK_BACKWARD_PATH || edge->mark == MARK_NONE, "Wrong edge in way");
		ptr = edge->backward->dst;
		i = -1;
		if (edge->backward->dst->is_start_node) // SRC
		{
			finish_reconstruct(way, edge, nodes);
			return TRUE;
		}
	}
	return FALSE;
}

void printf_queue(t_vector q)
{
	t_node_ptr	* current;

	for (int i = 0; i != q.size; i++)
	{
		current = get_from_vec(&q, i);
		printf("%s -- %d <-bfs \n", (*current)->name, (*current)->bfs);
	}
}

int 			find_by_bfs(t_node_ptr src, t_way * way, t_vector * nodes)
{

	t_node_ptr	* current;
	t_vector    queue;

	queue = new_vector(10, sizeof(t_node_ptr));
	push_back_vec(&queue, &src);
	while (queue.size != 0) {
		current = pop_front_vec(&queue);
		if ((*current)->traversal_state == STATE_VISITED)
			continue;
		if ((*current)->is_end_node) {
			free_vec(&queue);
			return reconstruct_way(*current, way, nodes);
		}
//		if (strcmp((*current)->name, "Aqi6") == 0)
//			printf("zod2");
		if ((*current)->traversal_state == STATE_IN_PATH)
			(*current)->is_cross = TRUE;
		(*current)->traversal_state = STATE_IN_QUEUE; ////Если убрать, то нарушает логику, но рез-тат лучше
		set_bfs_children(&queue, *current);
		(*current)->traversal_state = STATE_VISITED;

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

void				write_history(t_vector ways, char **history) {
	int way_i;
	t_way * way;
	int i;
	t_node_ptr dst;

	if (history == NULL) {
		way = get_last(&ways);
		dst = *(t_node_ptr *) get_last(&way->nodes);
		ft_assert(dst->is_end_node == TRUE, "Last of way is't dst");
		dst->ants.size = 0;
		return;
	}

	way_i = -1;
	while (++way_i < ways.size) {
		way = get_from_vec(&ways, way_i);
		i = 0;
		while (++i < way->nodes.size)
		{
			t_node_ptr node = *(t_node_ptr *) get_from_vec(&way->nodes, i);
			if (node->is_end_node)
			{
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
	int step = make_way_step(way);
	if (step > index) //// Работает в случае отсортированного вектора путей
		tracker->finished++;
	// Запускаю нового муравья на путь по его номеру
	if (tracker->ready_to_go > (way->nodes.size * index - *previous_ways_len))
	{
		push_back_vec(&curr->ants, &ant);
		tracker->ready_to_go--;
	}
	if (curr->is_end_node == 1)
	{
		tracker->finished++;
	}
	if (tracker->ready_to_go <= 0)
	{
		return (TRUE);
	}
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
    while (tracker.finished != tracker.all)
    {
		ft_assert(tracker.finished < tracker.all, "Too much finished ants");

		way_index = 0;
		while (way_index != ways->size)
		{
			finish_hp = make_way_step(get_from_vec(ways, way_index));
			way_index++;
		}
//		printf("%d, %d, %d\n", tracker.finished, finish_hp, tracker.all);
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
		while (++index != ways.size)
		{
			if (process_way(get_from_vec(&ways, index), &tracker, &previous_ways_len, index) && ways.size == index + 1)
				break;
		}
//		printf("fi%d, re%d, all%d\n", tracker.finished, tracker.ready_to_go, tracker.all);
		write_history(ways, way_history);
		++steps_count;
	}
	if (tracker.ready_to_go == 0)
		steps_count += get_rest_ant_step(tracker, &ways, way_history);
	return steps_count;
}

void print_node(t_node_ptr node)
{
	//printf("%s in state %d\n", node->name, node->traversal_state);
	for (int i = 0; i != node->links.size; ++i)
	{
		t_edge * edge = get_from_vec(&node->links, i);
		ft_assert(ft_strcmp(node->name, edge->backward->dst->name) == 0, "Error edge");
		printf("[%d]%s == %s-->%s\n", i, node->name, edge->backward->dst->name, edge->dst->name);
		//printf("%s -> %s (cap: %d, mark: %d); ", node->name, edge->dst->name, edge->capacity, edge->mark);
	}
	printf("\n");
}

void print_nodes(t_vector * nodes)
{
	for (int i = 0; i != nodes->size; ++i)
	{
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
struct s_solver_helper {
	char * best_history;
	size_t best_ant_step;

	char * current_history;
	size_t current_ant_step;

	int is_history_need;
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
	helper->is_history_need = FALSE;
	helper->current_ant_step = 0;
}

int process_candidate(t_solver_helper * helper, t_node_ptr src, int ants_count, t_vector ways)
{
	helper->current_ant_step = get_ant_step(src, ants_count, ways,
											helper->is_history_need ? &helper->current_history : NULL);
	return helper->current_ant_step;
}

int try_candidate(t_solver_helper * helper, t_node_ptr src, int ants_count, t_vector ways) {
	if (process_candidate(helper, src, ants_count, ways) < helper->best_ant_step)
		candidate_win(helper);
	else {
		ft_strclr(helper->current_history);
		return FALSE;
	}

	return TRUE;
}

void is_cross2(t_node_ptr curr, int i, t_vector ways)
{
	for (int k = i; k != ways.size; k++)
	{
		t_way *way = get_from_vec(&ways, k);
		for (int j = 1; j != way->nodes.size - 1; j++)
		{
			t_node *child = *(t_node_ptr *) get_from_vec(&way->nodes, j);
			if (ft_strcmp(child->name, curr->name) == 0) {
				//(ways);
				printf("Ways is cross on %s!\n", (*curr).name);

			}
		}
	}
}

void is_cross(t_vector ways)
{
	for (int i = 0; i != ways.size - 1; i++) {
		t_way * way = get_from_vec(&ways, i);
		for (int j = 1; j != way->nodes.size - 1; j++) {
			t_node * curr = *(t_node_ptr *) get_from_vec(&way->nodes, j);
			is_cross2(curr, i + 1, ways);
		}
	}
}

void free_way(t_way * way)
{
	free_vec(&way->nodes);
	free_vec(&way->edges);
	free(way);
}

void free_ways(t_vector * ways)
{
	while (ways->size != 0)
		free_way(pop_back_vec(ways));
	free_vec(ways);
}

int
solve(t_node_ptr src, int ants_count, t_vector * nodes, char ** history) // Временно сделал возвращаемое значение int
{
	t_vector ways;
	int is_need_recalculate;
	t_solver_helper helper;
	int is_attendance;

	helper = init_helper();
	is_need_recalculate = TRUE;
	while (reset_all_states(nodes))
	{
		ways = new_vector(10, sizeof(t_way));
		while ((is_attendance = find_by_bfs(src, get_place_for_way(&ways), nodes)) == TRUE)
		{
			if (get_last_way(&ways)->state == IS_CROSS)
				break;
			is_cross(ways);
			is_need_recalculate = try_candidate(&helper, src, ants_count, ways);
			src->bfs = 0;
		}
		if (ways.size == 0)
			return 0; // NULL
		if (is_need_recalculate == FALSE && is_attendance == FALSE)
			return helper.best_ant_step;
		if (is_need_recalculate == FALSE || is_attendance == FALSE)
		{
			ways.size -= 1;
			helper.is_history_need = TRUE;
			process_candidate(&helper, src, ants_count, ways);
			*history = helper.best_history;
			free_ways(&ways);
		}
		if (is_need_recalculate == FALSE)
			return helper.best_ant_step;
		is_need_recalculate = FALSE;
		reset_all_edges(nodes);
		free_vec(&ways); //// change and fix free_ways
	}
	return 0; // NULL
}
