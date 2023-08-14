# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 08:49:24 by mhabib-a          #+#    #+#              #
#    Updated: 2023/08/09 09:25:40 by youlhafi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFTFUNC = libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_atoi.c libft/ft_calloc.c libft/ft_strdup.c libft/ft_strnstr.c libft/ft_strmapi.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putchar_fd.c libft/ft_putnbr_fd.c libft/ft_itoa.c libft/ft_striteri.c libft/ft_strlcpy.c libft/ft_memmove.c libft/ft_strlcat.c 
PARS  = main.c tools.c tools2.c tokenize.c env.c ft_lex.c parse_input.c ft_quotes.c ft_free.c env_tools.c tokenize_tools.c ft_quotes_tools.c parse_input_tools.c trim_quotes.c parse_quote.c signals.c ft_quotes_tools2.c
EXC =  minishell.c ft_split.c utils.c ft_cd.c ft_echo.c ft_env.c ft_export.c check_pipe.c exec.c open_file.c multiple_pipe.c here_doc.c get_next_line_utils.c error.c ft_unset.c ft_export2.c  dup_fd.c ft_free2.c single_cmd.c builtins.c export_help.c init.c loop_help.c
SRC = $(PARS) $(EXC)
OBJLIBFT = $(LIBFTFUNC:.c=.o)
OBJ = $(SRC:.c=.o)
OBJDIR = object
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS=  ${shell brew --prefix}/opt/readline/include
LDFLAGS= ${shell brew --prefix}/opt/readline/lib
RFLAG = -lreadline
VAR = $(CPPFLAGS) $(LDFLAGS)
CC = cc 
RM = rm -f
LIB = minishell.h
LIBFT = libft/libft.h

all : $(NAME)

$(NAME) : $(OBJ) $(OBJLIBFT)
	$(CC) $(CFLAGS) -L $(LDFLAGS) $(OBJ) $(OBJLIBFT) -o $(NAME) $(RFLAG) -g

%.o : %.c $(LIB) $(LIBFT)
	$(CC) $(CFLAGS) -I $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJLIBFT)

fclean : clean
	$(RM) $(NAME)

re : fclean all