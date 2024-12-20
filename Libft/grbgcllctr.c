/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grbgcllctr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:28:11 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/07 18:32:46 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstadd_front(t_addr **lst, t_addr *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}

static void	ft_dstry(t_addr **addr)
{
	t_addr	*current;
	t_addr	*next;

	if (addr == NULL || *addr == NULL)
		return ;
	current = *addr;
	while (current != NULL)
	{
		next = current->next;
		free(current->addr);
		free(current);
		current = next;
	}
	*addr = NULL;
}

static t_addr	*ft_new(void *addr)
{
	t_addr	*new_node;

	new_node = malloc(sizeof(t_addr));
	if (!new_node)
		return (NULL);
	new_node->addr = addr;
	new_node->next = NULL;
	return (new_node);
}

void	*ft_malloc(size_t size, int mode)
{
	static t_addr	*head;
	void			*addr;

	if (!mode)
	{
		addr = malloc(size);
		if (!addr)
		{
			ft_dstry(&head);
			exit(1);
		}
		ft_lstadd_front(&head, ft_new(addr));
		return (addr);
	}
	else
	{
		ft_dstry(&head);
		return (NULL);
	}
}
