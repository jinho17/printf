#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "Libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

typedef struct		s_tag
{
	va_list			ap;
	char			flag;
	char			hex;
	char			sign;
	int				width;
	int				precision;
	int				prec;
	char			length[3];
	char			specifier;
	char			*str;
	int				str_len;
	char			*s;
	int				rtn_len;
}					t_tag;
t_tag	*tag;

int		ft_printf(const char *format, ...);
int		is_tag(const char *format, int i);	

int		get_flag_width(const char *format, int i);
int		flag_sign(const char *format, int i);
int		get_length_specifier(const char *format, int i);
int		get_precision(const char *format, int i);

void	conv_csdixX(void);
void	conv_dixX(void);
int		conv_upn(int i);

void	conv_fg(void);
char	*conv_f_dec(double *b_d, int *len);
void	conv_f_b_dec(int len, double b_d, char *b_dec, char *dec);
void	conv_g(void);

void	conv_e(void);
char	*conv_e_dec(int *len, double *b_d, double *dou, double *f);
int		conv_e_idx(char *dec, double *b_d, double *dou, double *f);
char	*conv_e_t(char *dec, int idx, int len);
void	conv_e_s(char *t, int len, double b_d, double dou);

void	tag_str_len(void);
void	front_space(void);
void	final_str(void);
void	add_flag(void);
void	add_flag2(char *t);
void	sign_sort(void);
void	free_taginit(int fre, int init);
#endif
