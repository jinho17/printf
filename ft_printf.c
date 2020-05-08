/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 03:08:01 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/08 20:34:48 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	free_taginit(int fre, int init)
{
	if (fre)
	{
		g_tag->rtn_len = g_tag->rtn_len + (int)ft_strlen(g_tag->str);
		free(g_tag->s);
		free(g_tag->str);
	}
	if (init)
	{
		g_tag->flag = 0;
		g_tag->width = 0;
		g_tag->precision = 0;
		g_tag->str_len = 0;
		g_tag->length[0] = 0;
		g_tag->length[1] = 0;
		g_tag->specifier = 0;
		g_tag->prec = 0;
		g_tag->sign = 0;
		g_tag->hex = 0;
	}
}

void	print_null(int idx)
{
	char *tmp;

	if (idx != 0)
	{
		tmp = ft_substr(g_tag->str, 0, idx);
		ft_putstr_fd(tmp, 1);
		free(tmp);
	}
	write(1, "", 1);
	if (idx + 2 >= 0)
	{
		tmp = ft_substr(g_tag->str, idx + 2, ft_strlen(g_tag->str));
		ft_putstr_fd(tmp, 1);
		free(tmp);
	}
}

void	print(void)
{
	int	idx;
	int	find;

	if (g_tag->specifier != 'c')
		ft_putstr_fd(g_tag->str, 1);
	else
	{
		idx = 0;
		find = 0;
		while (g_tag->str[idx])
		{
			if (g_tag->str[idx] == '^'
				&& g_tag->str[idx + 1] == '@'
				&& g_tag->str[idx + 1])
			{
				find = 1;
				break ;
			}
			idx++;
		}
		if (find == 0)
			ft_putstr_fd(g_tag->str, 1);
		else
			print_null(idx);
	}
}

int		is_tag(const char *format, int i)
{
	if (format[i] != '%')
	{
		ft_putchar_fd(format[i], 1);
		g_tag->rtn_len++;
	}
	else
	{
		i++;
		i = get_flag_width(format, i);
		i = get_precision(format, i);
		conv_csdix();
		i = conv_upn(i);
		if (g_tag->specifier == 'n')
			return (i);
		tag_str_len();
		front_space();
		final_str();
		print();
		free_taginit(1, 1);
	}
	return (i);
}

int		ft_printf(const char *format, ...)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(format);
	g_tag = (t_tag *)malloc(sizeof(t_tag));
	va_start(g_tag->ap, format);
	free_taginit(0, 1);
	g_tag->rtn_len = 0;
	while (i < len)
	{
		i = is_tag(format, i);
		if (g_tag->specifier == 'n')
		{
			free_taginit(0, 1);
			continue ;
		}
		i++;
		free_taginit(0, 1);
	}
	i = g_tag->rtn_len;
	free(g_tag);
	va_end(g_tag->ap);
	return (i);
}
