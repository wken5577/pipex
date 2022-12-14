/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:34:07 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/07/06 11:38:38 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ('a' <= c && c <= 'z')
		return (2);
	else if ('A' <= c && c <= 'Z')
		return (1);
	else if ('0' <= c && c <= '9')
		return (4);
	else
		return (0);
}
