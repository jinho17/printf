/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 03:19:28 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/07 16:10:46 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_length_specifier(const char *format, int i)
{
	int idx;

	idx = 0;
	while (format[i] == 'l' || format[i] == 'h')
		g_tag->length[idx++] = format[i++];
	g_tag->length[idx] = '\0';
	if (format[i] == 'c' || format[i] == 's' || format[i] == 'p'
			|| format[i] == 'd' || format[i] == 'i' || format[i] == 'u'
			|| format[i] == 'x' || format[i] == 'X' || format[i] == '%'
			|| format[i] == 'n' || format[i] == 'f' || format[i] == 'g'
			|| format[i] == 'e')
		g_tag->specifier = format[i];
	else
	{
		g_tag->specifier = 0;
		g_tag->s = ft_strdup("");
	}
	return (i);
}

int		get_precision(const char *format, int i)
{
	g_tag->prec = 0;
	if (format[i] == '.')
	{
		i++;
		if (format[i] == '*')
		{
			g_tag->precision = va_arg(g_tag->ap, int);
			i++;
		}
		else if (format[i] >= '0' && format[i] <= '9')
			g_tag->precision = format[i++] - '0';
		while (format[i] >= '0' && format[i] <= '9')
			g_tag->precision = (format[i++] - '0') + (g_tag->precision * 10);
		i = get_length_specifier(format, i);
		g_tag->prec = 1;
	}
	else
		i = get_length_specifier(format, i);
	if (g_tag->precision < 0)
	{
		g_tag->prec = 0;
		g_tag->precision = 0;
	}
	return (i);
}

int		flag_sign(const char *format, int i)
{
	if (format[i] == '+')
		g_tag->sign = format[i++];
	else if (format[i] == ' ' && g_tag->sign != '+')
		g_tag->sign = format[i++];
	else if (format[i] == ' ' && g_tag->sign == '+')
		i++;
	else if (g_tag->flag == '-' && format[i] == '0')
		g_tag->sign = '-';
	if (g_tag->flag == '0' && format[i] == '-')
		g_tag->flag = format[i++];
	return (i);
}

int		get_flag_width(const char *format, int i)
{
	while (format[i] == '+' || format[i] == '-' ||
			format[i] == '0' || format[i] == '#' || format[i] == ' ')
	{
		if (format[i] == '-' || format[i] == '0')
			g_tag->flag = format[i++];
		else if (format[i] == '#')
			g_tag->hex = format[i++];
		i = flag_sign(format, i);
	}
	if (format[i] == '*')
	{
		g_tag->width = va_arg(g_tag->ap, int);
		if (g_tag->width < 0)
		{
			g_tag->width *= -1;
			g_tag->flag = '-';
		}
		i++;
	}
	else if (format[i] >= '0' && format[i] <= '9')
		g_tag->width = format[i++] - '0';
	while (format[i] >= '0' && format[i] <= '9')
		g_tag->width = (format[i++] - '0') + (g_tag->width * 10);
	return (i);
}
