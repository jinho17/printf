#include "ft_printf.h"

void	free_taginit(int fre, int init)
{
	//free
	if (fre)
	{
		tag->rtn_len = tag->rtn_len + (int)ft_strlen(tag->str);
		if (tag->s)
			free(tag->s);
		free(tag->str);
	}
	//tag initialization
	if (init)
	{	tag->flag = 0;
		tag->width = 0;
		tag->precision = 0;
		tag->str_len = 0;
		tag->length[0] = 0;
		tag->length[1] = 0;
		tag->specifier = 0;
		tag->prec = 0;
		tag->sign = 0;
		tag->hex = 0;
	}
}

void	sign_sort(void)
{
	int		sign;
	char	*s;
	int		zero;
	char	*head;
	char	*tail;
	char	*t;

	sign = 0;
	while (tag->str[sign] && tag->str[sign] != '+' && tag->str[sign] != '-')
		sign++;
	if (tag->sign == ' ' && tag->str[sign] == '+')
		s = ft_strdup(" ");
	else
		s = ft_substr(tag->str, sign, 1);
	if (sign == (int)ft_strlen(tag->str))
		return ;
	zero = 0;
	while (tag->str[zero] && tag->str[zero] != '0' && tag->str[zero] == ' ')
		zero++;
	if (sign != (int)ft_strlen(tag->str))
	{
		head = ft_substr(tag->str, 0, zero);
		tail = ft_strjoin(ft_substr(tag->str, zero, sign - zero), ft_substr(tag->str, sign + 1, (int)ft_strlen(tag->str)));
		t = ft_strjoin(ft_strjoin(head, s), tail);
		free(tag->str);
		tag->str = ft_strdup(t);
		free(t);
	}
}

void	add_flag2(char *t)
{
	int		idx;

	if (tag->hex == '#' && tag->s[0] != '0' && tag->s[0] != '\0')
	{
		idx = 0;
		if (tag->flag == '0' && tag->prec == 0)
		{
			while (tag->str[idx] && tag->str[idx] == '0')
				idx++;
			if (idx >= 2)
				idx = 2;
			else if (idx == 1)
				idx = 1;
		}
		else
		{
			while (tag->str[idx] && tag->str[idx] == ' ')
				idx++;
		}
		//printf("str[%s]\n",tag->str);
		//printf("idx : %d\n", idx);
		if (idx >= 2)
		{
			tag->str[idx - 2] = '0';
			tag->str[idx - 1] = tag->specifier;
		}
		else if (idx == 1)
		{
			tag->str[0] = tag->specifier;
			t = ft_strjoin("0", tag->str);
			if (tag->str_len != tag->width || tag->flag != '-')
				tag->str_len = tag->str_len + 1;
		}
		else
		{
			if (tag->specifier == 'x')
				t = ft_strjoin("0x", tag->str);
			else
				t = ft_strjoin("0X", tag->str);
			if (tag->str_len != tag->width || tag->flag != '-')
				tag->str_len = tag->str_len + 2;
		}
	}
	if (t)
	{
		free(tag->str);
		tag->str = ft_strdup(t);
	}
}

void	add_flag(void)
{
	char	*t;
	char	*tmp;

	//cspdiuxX% nfge
	t = 0;
	if (tag->specifier != 'c' && tag->specifier != 's' && tag->specifier != 'u' && tag->specifier != '%' && tag->specifier != 'n')
	{
		if (tag->s[0] != '-')
		{
			if ((int)ft_strlen(tag->str) >= 1 && tag->prec == 0)
				tmp = ft_substr(tag->str, 0, (int)ft_strlen(tag->str) - 1);
			else
			{
				if (tag->str[0] == ' ')
					tmp = ft_substr(tag->str, 1, (int)ft_strlen(tag->str));
				else
					tmp = ft_strdup(tag->str);
			}
			if (tag->sign == '+' || tag->sign == ' ')
				t = ft_strjoin(tmp, "+");
			free(tmp);
		}
	}
	add_flag2(t);
}

void	final_str(void)
{
	int		idx;
	int		s_i;
	char	*tmp;
	char	*space;
	
	add_flag();
	tmp = ft_strjoin(tag->str, tag->s);
	idx = ft_strlen(tmp);
	space = (char *)malloc(sizeof(char) * (tag->str_len - idx + 1));
	//printf("width : %d, precision : %d, len : %d, idx : %d\n", tag->width, tag->precision, tag->str_len, idx);
	if (tag->flag == '-' && (tag->str_len == tag->width))
	{
		s_i = 0;
		while (s_i < tag->str_len - idx)
			space[s_i++] = ' ';
		space[s_i] = '\0';
	}
	else
		space[0] = '\0';
	free(tag->str);
	tag->str = ft_strjoin(tmp, space);
	free(tmp);
	free(space);
	sign_sort();
}

void	front_space(void)
{
	int idx;
	int	t;
	int len;

	tag->str = (char *)malloc(sizeof(char) * (tag->str_len + 1));
	idx = 0;
	if (tag->flag != '-' && (tag->str_len == tag->width))
	{
		if (tag->precision > (int)ft_strlen(tag->s))
			t = tag->width - tag->precision;
		else
			t = tag->width - (int)ft_strlen(tag->s);
		if (tag->s[0] == '-' && tag->prec == 1 && tag->precision > (int)ft_strlen(tag->s))
			t--;
		while (idx < t)
		{
			if (tag->flag == '0' && tag->prec == 0)
				tag->str[idx++] = '0';
			else
				tag->str[idx++] = ' ';
		}
		while ((idx < tag->str_len - (int)ft_strlen(tag->s)) && idx >= 0)
			tag->str[idx++] = '0';
	}
	else
	{
		if (tag->s[0] != '-')
			len = tag->precision - (int)ft_strlen(tag->s);
		else
			len = tag->precision - (int)ft_strlen(tag->s) + 1;
		while ((idx < len) && idx >= 0)
			tag->str[idx++] = '0';
	}
	tag->str[idx] = '\0';
}

void	tag_str_len(void)
{
	if (tag->specifier == 's' && tag->precision > (int)ft_strlen(tag->s))
		tag->precision = (int)ft_strlen(tag->s);
	if (!tag->s)
		tag->s = ft_strdup("");
	if (tag->specifier != 'c' && tag->specifier != 'f' && tag->precision == 0 && tag->prec == 1 && !ft_strncmp(tag->s, "0", 2))
		tag->s = ft_strdup(""); 
	tag->str_len = (int)ft_strlen(tag->s);
	//width > precision > strlen
 	if (tag->width >= tag->precision && tag->precision >= tag->str_len)
		tag->str_len = tag->width;
	//width > strlen > precison
	else if (tag->width >= tag->str_len && tag->str_len >= tag->precision)
		tag->str_len = tag->width;
	//precision > width > strlen
	else if (tag->precision >= tag->width && tag->width >= tag->str_len)
		tag->str_len = tag->precision;
	//precision > strlen > width
	else if (tag->precision >= tag->str_len && tag->str_len >= tag->width)
		tag->str_len = tag->precision;
	if (tag->specifier == '%')
		tag->str_len = 1;
}

void	conv_e_s(char *t, int len, double b_d, double dou)
{
	char	*dec;
	int		idx;

	dec = (char *)malloc(sizeof(char) * (len + 1));
	idx = 0;
	while(idx < len)
	{
		b_d = (b_d + dou) * 10;
		dec[idx] = (int)b_d + '0';
		b_d = b_d - (double)((int)b_d);
		idx++;
	}
	dec[idx] = '\0';
	tag->s = ft_strjoin(t, dec);
	free(t);
	free(dec);
}

char	*conv_e_t(char *dec, int idx, int len)
{
	int		new_len;
	char	*t;

	if (idx < (int)ft_strlen(dec))
	{
		new_len = 6;
		if (len == 0 && (int)ft_strlen(dec) > tag->precision && tag->precision != 0)
			new_len = tag->precision;
		else if (ft_strlen(dec) < 6)
			new_len = ft_strlen(dec);
		t = ft_strjoin(tag->s, ft_substr(dec, idx, new_len));
	}
	else
		t = ft_strdup(tag->s);
	free(tag->s);
	free(dec);
	return (t);
}

int		conv_e_idx(char *dec, double *b_d, double *dou, double *f)
{
	int		idx;
	char	*t;

	idx = 1;
	if ((int)*f == 0)
	{
		t = (char *)malloc(sizeof(char) * 3);
		*b_d = (*b_d + *dou) * 10;
		idx = 0;
		if (*f < 0)
			t[idx++] = '-';
		t[idx++] = (int)*b_d + '0';
		t[idx++] = '\0';
		*b_d = *b_d - (double)((int)*b_d);
	}
	else if (*f < 0)
		t = ft_substr(dec, 0, ++idx);
	else
		t = ft_substr(dec, 0, 1);
	tag->s = ft_strjoin(t, ".");
	free(t);
	return (idx);
}

char	*conv_e_dec(int *len, double *b_d, double *dou, double *f)
{
	char	*dec;
	int		idx;

	*f = va_arg(tag->ap, double);
	*b_d = *f - (double)((int)*f);
	if (*f < 0)
		*b_d = *b_d * (-1);
	dec = ft_itoa((int)*f);
	if (tag->precision == 0)
		*len = 6;
	else
		*len = tag->precision;

	if (*f < 0 && (int)*f != 0)
		*len = *len - ft_strlen(dec) + 2;
	else if (*f > 0 && (int)*f != 0)
		*len = *len - ft_strlen(dec) + 1;
	if (*len < 0)
		*len = 0;
	*dou = 0.5;
	idx = *len + 1;
	while (idx--)
		*dou /= 10;
	return (dec);
}

void	conv_e(void)
{
	double	f;
	double	b_d;
	int		len;
	char	*dec;
	double	dou;
	char	*t;
	
	if (tag->specifier == 'e')
	{
		dec = conv_e_dec(&len, &b_d, &dou, &f);
		f = (double)conv_e_idx(dec, &b_d, &dou, &f);
		t = conv_e_t(dec, (int)f, len);
		conv_e_s(t, len, b_d, dou);
	}
}

void	conv_g(void)
{
	char	*t;
	int		len;
	int		idx;

	len = 7;
	if (tag->precision)
		len = tag->precision;
	idx = 0;
	if (tag->s[idx] == '-')
	{
		len++;
		idx++;
	}
	if (tag->s[idx] == '0')
		len++;
	t = ft_substr(tag->s, 0, len);
	free(tag->s);
	tag->s = ft_strdup(t);
	free(t);
}

void	conv_f_b_dec(int len, double b_d, char *b_dec, char *dec)
{
	int		idx;
	double	dou;
	int		ten;
	char	*t;

	idx = len;
	dou = 0.5;
	while (idx--)
		dou /= 10;
	idx = len;
	ten = 10;
	while (idx--)
		ten = ten * 10;
	ten = ((int)(b_d * ten)) % 10;
	idx = 0;
	while (idx < len)
	{
		b_d = (b_d + dou) * 10;
		b_dec[idx] = (int)b_d + '0';
		b_d = b_d - (double)((int)b_d);
		idx++;
	}
	b_dec[idx--] = '\0';
	if (ten == 4)
	{
		if (b_dec[idx] == '0')
		{
			b_dec[idx--] = '9';
			while (idx >= 0)
			{
				if (b_dec[idx] != '0')
				{
					b_dec[idx] = b_dec[idx] - 1;
					break ;
				}
				b_dec[idx--] = '9';
			}
		}
		else
			b_dec[idx] = b_dec[idx] - 1;
	}
	if (b_dec[0] == '9' + 1)
	{
		b_dec[0] = '0';
		idx = ft_strlen(dec) - 1;
		if (dec[idx] == '9')
		{
			dec[idx--] = '0';
			while (dec[idx])
			{
				if (dec[idx] != '9')	
				{
					dec[idx] = dec[idx] + 1;
					break ;
				}
				dec[idx--] = '0';
			}
			if (idx == 0 && dec[0] == '0')
			{
				t = ft_strjoin("1", dec);
				free(dec);
				dec = ft_strdup(t);
				free(t);
			}
		}
		else
			dec[idx] = dec[idx] + 1;
	}
}

char	*conv_f_dec(double *b_d, int *len)
{
	double	f;

	f = va_arg(tag->ap, double);
	*b_d = f - (double)((long long)f);
	if (*b_d < 0)
		*b_d = *b_d * (-1);
	if (tag->precision == 0)
		*len = 6;
	else
		*len = tag->precision;
	if (f < 0 && (long long)f == 0)
		return (ft_strjoin("-", ft_itoa_unsigned((long long)f)));
	return (ft_itoa_unsigned((long long)f));
}

void	conv_fg(void)
{
	double	b_d;
	char	*dec;
	int		len;
	char	*b_dec;
	char	*t;

	if (tag->specifier == 'f' || tag->specifier == 'g')
	{
		dec = conv_f_dec(&b_d, &len);
		b_dec = (char *)malloc(sizeof(char) * (len + 1));
		conv_f_b_dec(len, b_d, b_dec, dec);
		if (tag->prec == 1 && tag->precision == 0)
		{
			if (b_dec[0] > '4')
			{
				int idx;

				idx = ft_strlen(dec) - 1;
				if (dec[idx] == '9')
				{
					while (dec[idx])
					{
						if (dec[idx] != '9')
						{
							dec[idx] = dec[idx] + 1;
							break ;
						}
						dec[idx--] = '0';
					}
					if (idx == -1 && dec[0] == '0')
					{
						t = ft_strjoin("1", dec);
						free(dec);
						dec = ft_strdup(t);
						free(t);
					}
				}
				else
					dec[idx] = dec[idx] + 1;
			}
			tag->s = ft_strdup(dec);
		}
		else
		{	
			t = ft_strjoin(dec, ".");
			tag->s = ft_strjoin(t, b_dec);
			free(t);
		}
		free(dec);
		free(b_dec);
	}
	if (tag->specifier == 'g')
		conv_g();
}

int		conv_upn(int i)
{
	long long	temp;
	char		*t;

	if (tag->specifier == 'u')
	{
		if (ft_strncmp(tag->length, "l", 3) == 0)
			temp = va_arg(tag->ap, long int);
		else if (!ft_strncmp(tag->length , "ll", 3))
			temp = va_arg(tag->ap, long long int);
		else if (!ft_strncmp(tag->length , "h", 3) || !ft_strncmp(tag->length , "hh", 3))
			temp = va_arg(tag->ap, int);
		else
			temp = va_arg(tag->ap, unsigned int);
		tag->s = ft_itoa_unlong(temp);
	}
	else if (tag->specifier == 'p')
	{
		t = ft_dectohex(va_arg(tag->ap, unsigned long), 'x');
		if (!ft_strncmp(t, "0", (int)ft_strlen(t)))
			tag->s = ft_strdup("(nil)");
		else
			tag->s = ft_strjoin("0x", t);	
		free(t);
	}
	else if (tag->specifier == 'n')
	{
		t = (char *)va_arg(tag->ap, int *);
		*t = tag->rtn_len;
		i++;
		return (i);
	}
	return (i);
}

void	conv_dixX(void)
{
	int		temp;

	if (tag->specifier == 'd' || tag->specifier == 'i')
	{
		if (ft_strncmp(tag->length, "l", 3) == 0)
			tag->s = ft_itoa_unsigned(va_arg(tag->ap, long int));
		else if (!ft_strncmp(tag->length , "ll", 3))
			tag->s = ft_itoa_unsigned(va_arg(tag->ap, long long int));
		else if (!ft_strncmp(tag->length , "h", 3) || !ft_strncmp(tag->length , "hh", 3))
			tag->s = ft_itoa_unsigned(va_arg(tag->ap, int));
		else
			tag->s = ft_itoa(va_arg(tag->ap, int));
	}
	else if (tag->specifier == 'x' || tag->specifier == 'X')
	{
		if (ft_strncmp(tag->length, "l", 3) == 0)
			tag->s = ft_dectohex(va_arg(tag->ap, long int), tag->specifier);
		else if (!ft_strncmp(tag->length , "ll", 3))
			tag->s = ft_dectohex(va_arg(tag->ap, long long int), tag->specifier);
		else if (!ft_strncmp(tag->length , "h", 3))
			tag->s = ft_dectohex(va_arg(tag->ap, int), tag->specifier);
		else if (!ft_strncmp(tag->length , "hh", 3))
		{
			temp = va_arg(tag->ap, signed int);
			while (1)
			{
				if (temp <= 255 && temp >= 0)
					break ;
				if (temp > 0)
					temp = temp - 256;
				if (temp < 0)
					temp = temp + 256;
			}
			if (temp < 0)
				temp = temp * (-1);
			tag->s = ft_dectohex(temp, tag->specifier);
		}
		else
			tag->s = ft_dectohex(va_arg(tag->ap, long long int), tag->specifier);
	}
}

void	conv_csdixX(void)
{
	char *t;

	if (tag->specifier == 'c')
	{
		tag->s = (char *)malloc(sizeof(char) * 2);
		tag->s[0] = va_arg(tag->ap, int);
		tag->s[1] = '\0';
		if (tag->s[0] == '\0')
		{
			if (tag->width != 0)
				tag->width = tag->width - 1;
			if (tag->precision != 0)
				tag->precision = tag->precision - 1;
			tag->rtn_len = tag->rtn_len + 1;
		}
	}
	else if (tag->specifier == '%')
		tag->s = ft_strdup("%");
	else if (tag->specifier == 's')
	{
		t = va_arg(tag->ap, char *);
		if (!t)
		{
			if (tag->precision < 6 && tag->prec == 1)
				tag->s = ft_strdup("");
			else
				tag->s = ft_strdup("(null)");
		}
		else if (tag->prec == 1)
			tag->s = ft_substr(t, 0, tag->precision);
		else
			tag->s = ft_substr(t, 0, ft_strlen(t));
	}
	conv_dixX();
}

int		get_length_specifier(const char *format, int i)
{
	int idx;

	//length		ex) l, ll, h, hh
	idx = 0;
	while (format[i] == 'l' || format[i] == 'h')
		tag->length[idx++] = format[i++];
	tag->length[idx] = '\0';
	//specifier		ex) cspdiuxX% nfge
	tag->specifier = format[i];
	return (i);
}

int		get_precision(const char *format, int i)
{
	if (format[i] == '.')
	{
		i++;
		//.precision	ex) .10
		if (format[i] == '*')
		{
			tag->precision = va_arg(tag->ap, int);
			i++;
		}
		else if (format[i] >= '0' && format[i] <= '9')
			tag->precision = format[i++] - '0';
		while (format[i] >= '0' && format[i] <= '9')
			tag->precision = (format[i++] - '0') + (tag->precision * 10);
		i = get_length_specifier(format, i);
		tag->prec = 1;
	}
	else
		i = get_length_specifier(format, i);
	return (i);
}

int		flag_sign(const char *format, int i)
{
	if (format[i] == '+')
		tag->sign = format[i++];
	else if (format[i] == ' ' && tag->sign != '+')
		tag->sign = format[i++];
	else if (format[i] == ' ' && tag->sign == '+')
		i++;
	if (tag->flag == '0' && format[i] == '-')
		tag->flag = format[i++];
	return (i);
}

int		get_flag_width(const char *format, int i)
{
	while (format[i] == '+' || format[i] == '-' || format[i] == '0' || format[i] == '#' || format[i] == ' ')
	{
		if (format[i] == '-')
			tag->flag = format[i++];
		if (format[i] == '#')
			tag->hex = format[i++];
		else if (format[i] == '0')
			tag->flag = format[i++];
		i = flag_sign(format, i);
	}
	if (format[i] == '*')
	{
		tag->width = va_arg(tag->ap, int);
		i++;
	}
	else if (format[i] >= '0' && format[i] <= '9')
		tag->width = format[i++] - '0';
	while (format[i] >= '0' && format[i] <= '9')
		tag->width = (format[i++] - '0') + (tag->width * 10);
	return (i);
}

int 	is_tag(const char *format, int i)
{
	if (format[i] != '%')
	{
		ft_putchar_fd(format[i], 1);
		tag->rtn_len++;
	}
	else
	{
		i++;
		i = get_flag_width(format, i);
		i = get_precision(format, i);
		conv_csdixX();
		i = conv_upn(i);
		if (tag->specifier == 'n')
			return (i);
		conv_fg();
		conv_e();
		tag_str_len();
		front_space();
		final_str();
		ft_putstr_fd(tag->str, 1);
		free_taginit(1, 1);
	}
	return (i);
}

int		ft_printf(const char *format, ...)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(format);
	tag = (t_tag *)malloc(sizeof(t_tag));
	va_start(tag->ap, format);
	while (i < len)
	{
		i = is_tag(format, i);
		if (tag->specifier == 'n')
		{
			free_taginit(0, 1);
			continue ;
		}
		i++;
	}
	i = tag->rtn_len;
	free(tag);
	va_end(tag->ap);
	return (i);
}
