/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:39:48 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/08/03 17:55:08 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>

void	print_error(void)
{
	perror("zsh");
	exit(1);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

t_data	*init_data(int argc, char *argv[], char *envp[])
{
	t_data	*arg_data;

	arg_data = malloc(sizeof(t_data));
	if (!arg_data)
		print_error();
	arg_data->argc = argc;
	arg_data->argv = argv;
	arg_data->envp = envp;
	return (arg_data);
}

void	conn_out_file(t_data *arg_data, int n, int bonus_flag)
{
	int	fd;
	int	status;

	if (!bonus_flag)
		fd = open (arg_data->argv[n + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open (arg_data->argv[n + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		free(arg_data);
		print_error();
	}
	status = dup2(fd, STD_OUT);
	if (status < 0)
	{
		free(arg_data);
		print_error();
	}
	close(fd);
}

void	print_error2(char **comm, char **paths, t_data *arg_data)
{
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(comm[0], 2);
	ft_putstr_fd("\n", 2);
	release(comm);
	free(arg_data);
	if (paths)
		release(paths);
	exit(1);
}
