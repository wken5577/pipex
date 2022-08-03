/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:24:59 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/08/03 17:58:49 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

void	release(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**get_paths(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (0);
}

char	*get_full_path(char *path, char *comm, t_data *arg_data)
{
	int		p_len;
	int		c_len;
	char	*full_path;

	p_len = ft_strlen(path);
	c_len = ft_strlen(comm);
	full_path = malloc(sizeof(char) * (p_len + c_len + 2));
	if (!full_path)
	{
		free(arg_data);
		print_error();
	}
	full_path[0] = 0;
	ft_strlcat(full_path, path, p_len + 1);
	full_path[p_len] = '/';
	full_path[p_len + 1] = 0;
	ft_strlcat(full_path, comm, p_len + c_len + 2);
	return (full_path);
}

void	execute2(char **comm, char *full_path)
{
	if (execve(full_path, comm, 0) == -1)
	{
		free(full_path);
		release(comm);
		print_error();
	}
}

void	make_fullpath_execute(char **comm, t_data *arg_data)
{
	int		i;
	char	**paths;
	char	*full_path;
	int		flag;

	paths = get_paths(arg_data->envp);
	i = 0;
	flag = 0;
	while (paths[i])
	{
		full_path = get_full_path(paths[i], comm[0], arg_data);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			flag = 1;
			free(arg_data);
			release(paths);
			execute2(comm, full_path);
		}
		free(full_path);
		i++;
	}
	if (!flag)
		print_error2(comm, paths, arg_data);
}
