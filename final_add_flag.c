/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 16:31:35 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/08 19:46:12 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_0x_after(int idx)
{
	char	*t;
	char	*space;
	char	*str;

	while (idx < ft_strlen(g_tag->str) && g_tag->str[idx] == ' ')
		idx++;
	space = ft_substr(g_tag->str, 0, idx);
	str = ft_substr(g_tag->str, idx, ft_strlen(g_tag->str) - idx);
	if (g_tag->specifier == 'x')
		t = ft_strjoin(space, "0x");
	else if (g_tag->specifier == 'X')
		t = ft_strjoin(space, "0X");
	free(g_tag->str);
	g_tag->str = ft_strjoin(t, str);
	if (g_tag->width != g_tag->str_len)
		g_tag->str_len += 2;
	else if (g_tag->width == g_tag->str_len && ((g_tag->prec == 1
			&& (g_tag->width <= g_tag->precision || g_tag->width < 3
				|| (g_tag->precision == 0 && g_tag->width < 3)))
			|| (g_tag->prec == 0 && g_tag->width < 4)))
		g_tag->str_len += 2;
	free(t);
	free(space);
	free(str);
}

int		add_flag2_sub(int idx)
{
	if (g_tag->flag == '0' && g_tag->prec == 0)
	{
		while (g_tag->str[idx] && g_tag->str[idx] == '0')
			idx++;
		if (idx >= 2)
			idx = 2;
		else if (idx == 1)
			idx = 1;
	}
	else
	{
		while (g_tag->str[idx] && g_tag->str[idx] == ' ')
			idx++;
	}
	return (idx);
}

void	add_flag2(char *t)
{
	int idx;

	if (g_tag->hex == '#' && g_tag->s[0] != '0' && g_tag->s[0] != '\0')
	{
		idx = 0;
		idx = add_flag2_sub(idx);
		if ((g_tag->flag == '0' || g_tag->prec == 1)
			&& (g_tag->specifier == 'x' || g_tag->specifier == 'X'))
			add_0x_after(0);
	}
	if (t)
	{
		free(g_tag->str);
		g_tag->str = ft_strdup(t);
		free(t);
	}
}

void	add_flag(void)
{
	char	*t;
	char	*tmp;

	t = 0;
	if (g_tag->specifier != 'c' && g_tag->specifier != 's'
		&& g_tag->specifier != 'u' && g_tag->specifier != '%'
		&& g_tag->specifier != 'n')
	{
		if (g_tag->s[0] != '-')
		{
			if ((int)ft_strlen(g_tag->str) >= 1 && g_tag->prec == 0)
				tmp = ft_substr(g_tag->str, 0, (int)ft_strlen(g_tag->str) - 1);
			else
			{
				if (g_tag->str[0] == ' ')
					tmp = ft_substr(g_tag->str, 1, (int)ft_strlen(g_tag->str));
				else
					tmp = ft_strdup(g_tag->str);
			}
			if (g_tag->sign == '+' || g_tag->sign == ' ')
				t = ft_strjoin(tmp, "+");
			free(tmp);
		}
	}
	add_flag2(t);
}
