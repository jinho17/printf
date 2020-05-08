/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 16:44:39 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/08 20:54:51 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*make_tail(int sign, int zero)
{
	char	*t1;
	char	*t2;
	char	*t3;
	char	*rtn;

	t1 = ft_substr(g_tag->str, zero, sign - zero);
	t2 = ft_substr(g_tag->str, sign + 1, (int)ft_strlen(g_tag->str));
	rtn = ft_strjoin(t1, t2);
	free(t1);
	free(t2);
	return (rtn);
}

void	sign_sort_sub(int sign, int zero, char *s)
{
	char	*head;
	char	*tail;
	char	*t;
	char	*t1;

	if (sign != (int)ft_strlen(g_tag->str))
	{
		head = ft_substr(g_tag->str, 0, zero);
		tail = make_tail(sign, zero);
		t1 = ft_strjoin(head, s);
		t = ft_strjoin(t1, tail);
		free(t1);
		free(g_tag->str);
		g_tag->str = ft_strdup(t);
		free(t);
		free(head);
		free(tail);
	}
	free(s);
}

void	sign_sort(void)
{
	int		sign;
	int		zero;
	char	*s;

	sign = 0;
	while (g_tag->str[sign] && g_tag->str[sign] != '+'
			&& g_tag->str[sign] != '-')
		sign++;
	if (sign == (int)ft_strlen(g_tag->str))
		return ;
	if (g_tag->sign == ' ' && g_tag->str[sign] == '+')
		s = ft_strdup(" ");
	else
		s = ft_substr(g_tag->str, sign, 1);
	zero = 0;
	while (g_tag->str[zero] && g_tag->str[zero] != '0'
			&& g_tag->str[zero] == ' ')
		zero++;
	sign_sort_sub(sign, zero, s);
}

int		percent_hx_idx(int idx)
{
	if (g_tag->specifier == '%' && g_tag->width != g_tag->str_len)
	{
		idx = 0;
		g_tag->str_len = g_tag->width - 1;
	}
	if (g_tag->length[0] == 'h' && g_tag->hex == '#'
		&& (g_tag->specifier == 'x' || g_tag->specifier == 'X'))
	{
		if (!(idx + 1 == g_tag->width && g_tag->prec == 0))
			idx++;
	}
	return (idx);
}

void	final_str(void)
{
	int		idx;
	int		s_i;
	char	*tmp;
	char	*space;

	add_flag();
	tmp = ft_strjoin(g_tag->str, g_tag->s);
	idx = ft_strlen(tmp);
	space = (char *)malloc(sizeof(char) * (g_tag->str_len - idx + 1));
	if (((g_tag->flag == '-') && (g_tag->str_len == g_tag->width))
		|| g_tag->specifier == '%' || g_tag->length[0] == 'h')
	{
		idx = percent_hx_idx(idx);
		s_i = 0;
		while (s_i < g_tag->str_len - idx)
			space[s_i++] = ' ';
		space[s_i] = '\0';
	}
	else
		space[0] = '\0';
	free(g_tag->str);
	g_tag->str = ft_strjoin(tmp, space);
	free(tmp);
	free(space);
	sign_sort();
}
