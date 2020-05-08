/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 02:29:59 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/08 21:18:43 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "Libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_tag
{
	va_list		ap;
	char		flag;
	char		hex;
	char		sign;
	int			width;
	int			precision;
	int			prec;
	char		length[3];
	char		specifier;
	char		*str;
	int			str_len;
	char		*s;
	int			rtn_len;
}				t_tag;
t_tag			*g_tag;

int				ft_printf(const char *format, ...);
void			print(void);
void			print_null(int idx);
int				is_tag(const char *format, int i);
void			free_taginit(int fre, int init);

int				get_flag_width(const char *format, int i);
int				flag_sign(const char *format, int i);
int				get_length_specifier(const char *format, int i);
int				get_precision(const char *format, int i);

void			conv_csdix(void);
void			conv_s(void);
void			conv_di(void);
void			conv_x(void);
void			conv_x_hh(void);

int				conv_upn(int i);
void			conv_u(void);

void			tag_str_len(void);
void			add_0x(void);
void			hx_str_len(void);
void			hx_str_len2(void);

void			front_space(void);
int				get_t(int t);
int				front_space_sub(int idx);
int				percent_front_space(int idx);

void			add_flag(void);
void			add_flag2(char *t);
int				add_flag2_sub(int idx);
void			add_0x_after(int idx);

char			*make_tail(int sign, int zero);
void			final_str(void);
int				percent_hx_idx(int idx);
void			sign_sort(void);
void			sign_sort_sub(int sign, int zero, char *s);

void			init_hhu(unsigned char n,
				unsigned char *num, int *sign, int *len);
char			*ft_itoa_hhu(unsigned char n);

char			*ft_itoa_unlong(unsigned long long n);
char			*ft_itoa_unshortint(unsigned short int n);
void			init_unlong(unsigned long long n,
				unsigned long long *num, int *sign, int *len);
char			*ft_itoa_unsigned(long long n);
void			init_unsigned(long long n, long long *num, int *sign, int *len);

#endif
