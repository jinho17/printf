/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_str_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 16:13:37 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/08 21:12:57 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_0x(void)
{
	char *t;

	if (g_tag->specifier == 'x')
		t = ft_strjoin("0x", g_tag->s);
	else if (g_tag->specifier == 'X')
		t = ft_strjoin("0X", g_tag->s);
	free(g_tag->s);
	g_tag->s = ft_strdup(t);
	free(t);
}

void	hx_str_len2(void)
{
	if (g_tag->s[0] == 0 && g_tag->width < 4)
		g_tag->str_len = g_tag->width + 1;
	else if (g_tag->s[0] == 0 && g_tag->width >= 4 && g_tag->flag == '-')
		g_tag->str_len = ++g_tag->width;
	else if (g_tag->s[0] == '0' && g_tag->width <= 4
			&& g_tag->precision <= g_tag->width)
	{
		if (g_tag->flag == '-' && g_tag->str_len > 5)
			g_tag->width++;
		g_tag->str_len = g_tag->width;
	}
	else if (g_tag->s[0] != 0 && g_tag->s[0] != '0'
			&& ft_strlen(g_tag->s) == 4 && g_tag->width < 5)
		g_tag->str_len += 1;
}

void	hx_str_len(void)
{
	if (g_tag->hex == '#' && g_tag->length[0] == 'h'
		&& (g_tag->specifier == 'x' || g_tag->specifier == 'X')
		&& !(g_tag->s[0] && (g_tag->s[1] == 'x' || g_tag->s[1] == 'X')))
	{
		if (g_tag->precision == 0 && g_tag->prec == 1
			&& g_tag->width < g_tag->precision)
			g_tag->str_len = 5;
		if (ft_strlen(g_tag->s) == 5)
			g_tag->str_len += 2;
		else if (ft_strlen(g_tag->s) == 6)
			g_tag->str_len += 1;
		else if (g_tag->s[0] != '\0' && g_tag->flag == '-'
				&& !(g_tag->width == g_tag->str_len
					&& g_tag->width == 1)
				&& !(g_tag->prec == 0 && g_tag->precision == 0
					&& g_tag->flag != '-'))
		{
			g_tag->width += 1;
			if (g_tag->width > g_tag->str_len)
				g_tag->str_len = g_tag->width;
		}
		hx_str_len2();
	}
}

void	exception(void)
{
	if (g_tag->specifier == 's' && g_tag->precision > (int)ft_strlen(g_tag->s))
		g_tag->precision = (int)ft_strlen(g_tag->s);
	if (!g_tag->s)
		g_tag->s = ft_strdup("");
	if (g_tag->specifier != 'c' && g_tag->precision == 0
		&& g_tag->prec == 1 && !ft_strncmp(g_tag->s, "0", 2))
	{
		if (g_tag->s)
			free(g_tag->s);
		g_tag->s = ft_strdup("");
	}
}

void	tag_str_len(void)
{
	if (g_tag->hex == '#' && g_tag->flag != '0' && g_tag->prec != 1
			&& (g_tag->specifier == 'x' || g_tag->specifier == 'X')
			&& (ft_strncmp(g_tag->s, "0", ft_strlen(g_tag->s)) != 0))
		add_0x();
	exception();
	g_tag->str_len = (int)ft_strlen(g_tag->s);
	if (g_tag->width >= g_tag->precision && g_tag->precision >= g_tag->str_len)
		g_tag->str_len = g_tag->width;
	else if (g_tag->width >= g_tag->str_len
			&& g_tag->str_len >= g_tag->precision)
		g_tag->str_len = g_tag->width;
	else if (g_tag->precision >= g_tag->width && g_tag->width >= g_tag->str_len)
		g_tag->str_len = g_tag->precision;
	else if (g_tag->precision >= g_tag->str_len
			&& g_tag->str_len >= g_tag->width)
		g_tag->str_len = g_tag->precision;
	hx_str_len();
}
