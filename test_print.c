//
// Created by Taisha Myrcella on 11/28/20.
//

#include "lem_in.h"

void ft_assert(int result, const char * error)
{
	if (result == FALSE) {
		printf("%s\n", error);
		exit(-1);
	}
}

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

void print_node(t_node_ptr node)
{
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