/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:19:09 by ereali            #+#    #+#             */
/*   Updated: 2021/10/08 18:19:03 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void args_error(void)
{
	ft_putstr_fd("Wrong args", 2);
	exit(EXIT_FAILURE);
}

// int	check_arg(char *s)
// {
// 	if (!s)
// 		return (0);
// 	return (1);
// }

int	main(int argc, char** argv)
{
	int pipefd[2];
	int in_pid;
	int i;

	i = 1;
	if (argc != 5)
		args_error();
	in_pid = open(argv[1], O_RDONLY);
	if (in_pid == -1)
		args_error();
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
    }
	in_pid = fork();
    if (in_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
    }
	if (in_pid == 0)
	{
		close(pipefd[0]);

	}
	else
	{

	}
	return (0);
}
