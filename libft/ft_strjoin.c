/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:30:44 by afaris            #+#    #+#             */
/*   Updated: 2022/10/26 21:03:55 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
int ft_strlen2(char *s)
{
	int i = -1;
	while(s[++i]);
	return (i);
}

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (i < ft_strlen2(s1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen2(s2))
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	free(s1);
	return (str);
}
