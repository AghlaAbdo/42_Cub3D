/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab_map_lst_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:42:13 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/07 18:14:12 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d_bonus.h"

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
