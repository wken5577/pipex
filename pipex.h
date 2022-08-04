/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:05:18 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/08/04 13:02:03 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<stdlib.h>

typedef struct s_arg_data	t_data;
struct s_arg_data
{
	int		argc;
	char	**argv;
	char	**envp;
};

void	ft_putstr_fd(char *s, int fd);
void	open_infile(char *infile, t_data *arg_data, int bonus_flag);
void	print_error(void);
void	conn_pipe(int fd_pipe[], t_data *arg_data);
pid_t	exe_fork(t_data *arg_data);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
void	make_fullpath_execute(char **comm, t_data *arg_data);
void	release(char **strs);
void	dup2_read(int fd_read, t_data *arg_data);
void	dup2_write(int fd_pipe[], t_data *arg_data);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
void	conn_out_file(t_data *arg_data, int n, int bonus_flag);
t_data	*init_data(int argc, char *argv[], char *envp[]);
void	print_error2(char **comm, char **paths, t_data *arg_data);
void	recursive_pipe(int fd_read, t_data *arg_data, int n, int bonus_flag);

# define STD_IN 0
# define STD_OUT 1
# define READ 0
# define WRITE 1
#endif
