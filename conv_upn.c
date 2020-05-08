/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_upn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 15:52:46 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/07 15:57:10 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conv_u(void)
{
	long long	temp;

	if (g_tag->specifier == 'u')
	{
		if (ft_strncmp(g_tag->length, "l", 3) == 0)
			temp = va_arg(g_tag->ap, long int);
		else if (!ft_strncmp(g_tag->length, "ll", 3))
			temp = va_arg(g_tag->ap, long long int);
		else if (!ft_strncmp(g_tag->length, "h", 3))
			temp = va_arg(g_tag->ap, int);
		else if (!ft_strncmp(g_tag->length, "hh", 3))
			temp = va_arg(g_tag->ap, int);
		else
			temp = va_arg(g_tag->ap, unsigned int);
		if (!ft_strncmp(g_tag->length, "h", 3))
			g_tag->s = ft_itoa_unshortint(temp);
		else if (!ft_strncmp(g_tag->length, "hh", 3))
			g_tag->s = ft_itoa_hhu(temp);
		else
			g_tag->s = ft_itoa_unlong(temp);
	}
}

int		conv_upn(int i)
{
	char	*tmp;
	int		*t;

	conv_u();
	if (g_tag->specifier == 'p')
	{
		tmp = ft_dectohex(va_arg(g_tag->ap, unsigned long), 'x');
		if (!ft_strncmp(tmp, "0", (int)ft_strlen(tmp)))
		{
			if (g_tag->prec == 1)
				g_tag->s = ft_strdup("0x");
			if (g_tag->prec == 0)
				g_tag->s = ft_strdup("0x0");
		}
		else
			g_tag->s = ft_strjoin("0x", tmp);
		free(tmp);
	}
	else if (g_tag->specifier == 'n')
	{
		t = va_arg(g_tag->ap, int *);
		*t = g_tag->rtn_len;
		return (++i);
	}
	return (i);
}
