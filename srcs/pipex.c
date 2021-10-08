/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:19:09 by ereali            #+#    #+#             */
/*   Updated: 2021/09/29 00:34:42 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void args_error(void)
{
	ft_putstr_fd("Wrong args", 2);
	exit(EXIT_FAILURE);
}

int	check_arg(char *s)
{
	if (!s)
		return (0);
	return (1);
}

int	main(int argc, char** argv)
{
	int in_pid;
	int i;

	i = 1;
	if (argc != 5)
		args_error();
	in_pid = open(argv[1], O_RDONLY);
	if (in_pid == -1)
		args_error();
	while (i <= 4)
	{
		if (!check_arg(argv[i]))
			args_error();
		i++;
	}
	return (0);
}
