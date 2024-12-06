/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab_map_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Apple <Apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:10:32 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/05 12:49:37 by Apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

t_maplst	*ab_maplst_new(char *line)
{
	t_maplst	*new;

	new = ft_malloc(sizeof(t_maplst), 0);
	if (!new)
		return (NULL);
	new->line = line;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ab_maplstaddb(t_maplst **lst, t_maplst *new)
{
	t_maplst	*ptr;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
}

int	ab_maplst_size(t_maplst *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
