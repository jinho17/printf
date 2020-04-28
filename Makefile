CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

NAME = libftprintf.a
SRC = ft_printf.c
OBJ = $(SRC:.c=.o)

LIB_DIR = Libft/
LIB_TAR = libft.a
LIB_SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
	ft_dectohex.c ft_itoa_unsigned.c ft_itoa_unlong.c

LIB_S = $(addprefix $(LIB_DIR), $(LIB_SRC))
LIB_OBJ = $(LIB_SRC:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) $(LIB_S) -I $(LIB_DIR)
	$(CC) $(CFLAGS) $(SRC)

$(NAME): $(OBJ)
	ar cr $@ $(OBJ) $(LIB_OBJ)

clean:
	rm -f $(OBJ) $(LIB_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
