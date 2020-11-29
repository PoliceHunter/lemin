/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmyrcell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:52:19 by tmyrcell          #+#    #+#             */
/*   Updated: 2020/11/28 22:52:20 by tmyrcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			enqueue(t_queue **head, t_node_ptr val)
{
	t_queue *new_node;

	new_node = malloc(sizeof(t_queue));
	if (!new_node)
		return ;
	new_node->val = val;
	new_node->next = *head;
	*head = new_node;
}

t_node_ptr		dequeue(t_queue **head)
{
	t_queue		*current;
	t_queue		*prev;
	t_node_ptr	retval;

	current = NULL;
	prev = NULL;
	if (*head == NULL)
		return (NULL);
	current = *head;
	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
	}
	retval = current->val;
	free(current);
	if (prev)
		prev->next = NULL;
	else
		*head = NULL;
	return (retval);
}

void			queue_up(t_queue **queue, t_node_ptr node, int new_bfs)
{
	enqueue(queue, node);
	node->bfs = new_bfs;
	if (node->is_start_node)
		return ;
	node->traversal_state = STATE_IN_QUEUE;
}

void			clear_queue(t_queue *queue)
{
	while (queue != NULL)
		dequeue(&queue);
}
