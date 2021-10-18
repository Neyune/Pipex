/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errorandfree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 03:04:39 by ereali            #+#    #+#             */
/*   Updated: 2021/10/18 03:20:48 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	args_error(void)
{
	ft_putstr_fd("Wrong args\n", 2);
	exit(EXIT_FAILURE);
}

void	use_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}
