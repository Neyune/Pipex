/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:19:09 by ereali            #+#    #+#             */
/*   Updated: 2021/10/10 02:16:48 by ereali           ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	int pipefd[2];
	int in_pid;
	int first_pid;
	int second_pid;
	int *status;
	int i;

	i = 1;
	(void)envp;
	if (argc != 5)
		args_error();
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
    }
	child = fork();
    if (child < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
    }
	if (child == 0)
	{
		first_pid = open(argv[1], O_RDONLY);
		if (first_pid < 0)
			args_error();
	}
	child2 = fork();
	if (child2 < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child2 == 0)
	{
		second_pid = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (second_pid < 0)
			args_error();
	}
	waitpid(child, &status, 0);
	close(pipefd[0]);
	waitpid(child2, &status, 0);
	close(pipefd[1]);
	return (0);
}
