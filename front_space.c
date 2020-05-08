/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_str_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 16:13:37 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/07 18:55:48 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_t(int t)
{
	if ((g_tag->precision > (int)ft_strlen(g_tag->s))
		&& !(g_tag->specifier == '%' && g_tag->flag != '0'))
		t = g_tag->width - g_tag->precision;
	else
		t = g_tag->width - (int)ft_strlen(g_tag->s);
	if (g_tag->s[0] == '-' && g_tag->prec == 1 && g_tag->specifier != 's'
		&& g_tag->precision >= (int)ft_strlen(g_tag->s))
		t--;
	if ((g_tag->specifier == 'x' || g_tag->specifier == 'X')
		&& (g_tag->prec == 1 || g_tag->flag == '0') && g_tag->hex == '#'
		&& ft_strncmp(g_tag->s, "0", ft_strlen(g_tag->s)) != 0
		&& (ft_strlen(g_tag->s) < 2 || g_tag->width > 2))
	{
		g_tag->str_len -= 2;
		if (g_tag->precision > g_tag->str_len)
			g_tag->str_len = g_tag->precision;
		t -= 2;
	}
	return (t);
}

int		front_space_sub(int idx)
{
	int	t;

	t = 0;
	if (g_tag->s[0] == '-' && g_tag->prec == 1
		&& g_tag->str_len <= g_tag->precision && g_tag->specifier != 's')
		g_tag->str_len += 1;
	t = get_t(t);
	while (idx < t)
	{
		if (g_tag->flag == '0' && g_tag->prec == 0)
			g_tag->str[idx++] = '0';
		else if (g_tag->flag == '0' && g_tag->specifier == '%')
			g_tag->str[idx++] = '0';
		else
			g_tag->str[idx++] = ' ';
	}
	while ((idx < g_tag->str_len - (int)ft_strlen(g_tag->s)) && idx >= 0)
		g_tag->str[idx++] = '0';
	return (idx);
}

int		percent_front_space(int idx)
{
	while (idx < g_tag->width - 1 && g_tag->flag != '0')
		g_tag->str[idx++] = ' ';
	while (idx < g_tag->width - 1 && g_tag->flag == '0')
		g_tag->str[idx++] = '0';
	g_tag->precision = 0;
	g_tag->str_len = g_tag->width;
	return (idx);
}

void	front_space(void)
{
	int idx;
	int len;

	g_tag->str = (char *)malloc(sizeof(char) * (g_tag->str_len + 1));
	idx = 0;
	if (g_tag->flag != '-' && (g_tag->str_len == g_tag->width)
			&& !(g_tag->specifier == '%' && g_tag->sign == '-'))
		idx = front_space_sub(0);
	else if (g_tag->specifier != '%')
	{
		len = g_tag->precision - (int)ft_strlen(g_tag->s);
		if (g_tag->s[0] == '-' && g_tag->specifier != 's')
			len++;
		while ((idx < len) && idx >= 0)
			g_tag->str[idx++] = '0';
	}
	else if (g_tag->specifier == '%' && g_tag->precision != 0
			&& g_tag->flag != '-')
		idx = percent_front_space(0);
	g_tag->str[idx] = '\0';
}
