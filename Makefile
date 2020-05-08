CC = gcc
CFLAG = -Wall -Wextra -Werror -c

NAME = libftprintf.a
SRC = ft_printf.c get_flag_width_precision.c \
	  conv_csdix.c conv_upn.c \
	  tag_str_len.c front_space.c \
	  final_str.c final_add_flag.c \
	  itoa_unsigned.c hhu_itoa.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./Libft bonus
	cp ./Libft/libft.a $(NAME)
	$(CC) $(CFLAGS) -c $(SRC) -I. -I./Libft/
	ar cr $@ $(OBJ)

bonus : all

clean:
	make -C ./Libft clean
	rm -rf $(OBJ)

fclean: clean
	rm -rf ./Libft/libft.a
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
