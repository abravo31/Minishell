# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: motero <motero@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 18:38:23 by motero            #+#    #+#              #
#    Updated: 2023/01/28 20:10:41 by motero           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

#=============================================================================#
#                                 HEADERS                                     #
#=============================================================================#

HDR_NAME = libft.h
HDR_DIR = includes/
HDRS = $(addprefix $(HDR_DIR), $(HDR_NAME))
HDR_INC = $(addprefix -I./, $(HDR_DIR))

HDR_NAME_PRINT = ft_printf.h
HDR_PATH_PRINT = printf/includes/
HDRS_PRINT = $(addprefix $(HDR_DIR_PRINT), $(HDR_NAME_PRINT))
HDR_INC_PRINT = $(addprefix -I./, $(HDR_DIR_PRINT))

#=============================================================================#
#                               SOURCES                                       #
#=============================================================================#

SRCS_PATH = sources/
SRCS_NAME = ft_atof.c \
ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_strlen.c \
ft_memset.c \
ft_bzero.c \
ft_memcpy.c \
ft_memmove.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_toupper.c \
ft_tolower.c \
ft_strchr.c \
ft_strrchr.c \
ft_strncmp.c \
ft_memchr.c \
ft_memcmp.c \
ft_strnstr.c \
ft_atoi.c \
ft_calloc.c \
ft_strdup.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_split.c \
ft_itoa.c \
ft_strmapi.c \
ft_striteri.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstmap.c \
ft_atoi_base.c \
ft_print_addr.c \
ft_printf.c \
ft_putchar.c \
ft_putnbr_base.c \
ft_putstr.c \
ft_switch_cases.c\
ft_switch_case_two.c\
ft_printerror.c \
ft_strcmp.c \
ft_strconcat.c \
ft_strcpy.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

SRCS_PATH_PRINT = printf/sources
SRCS_PRINT_NAME = ft_atoi_base.c \
ft_print_addr.c \
ft_printf.c \
ft_putchar.c \
ft_putnbr_base.c \
ft_putstr.c \
ft_strlen.c \
ft_switch_cases.c\
ft_switch_case_two.c
SRCS_PRINT = $(addprefix $(SRCS_PATH_PRINT), $(SRCS_PRINT_NAME))

#=============================================================================#
#                                OBJECTS                                      #
#=============================================================================#

OBJS_PATH = objs/
OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

OBJS_NAME_PRINT = $(SRCS_PRINT_NAME:.c=.o)
OBJS_PRINT = $(addprefix $(OBJS_PATH), $(OBJS_NAME_PRINT))

#=============================================================================#
#                          COMPILATOR & FLAGS                                 #
#=============================================================================#

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBA = ar rc
LIBS = ranlib

RM = rm -Rf

#=============================================================================#
#                                COLOURS                                      #
#=============================================================================#

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m

#=============================================================================#
#                                RULES                                        #
#=============================================================================#

$(NAME): $(OBJS_PATH) $(OBJS) $(HDRS)
		@echo "\t Wait for it ..."
		@echo "\t─────▄▀▄─────▄▀▄"
		@echo "\t────▄█░░▀▀▀▀▀░░█▄"
		@echo "\t▄▄──█░░░░░░░░░░░█──▄▄"
		@echo "\t▄▄█─█░░▀░░┬░░▀░░█─█▄▄█"
		@ar rc $@ $(OBJS)
		@$(LIBS) $@
		@echo "\t[ $(GREEN)✔$(NONE) ] libft.a library"

$(OBJS_PATH):
			@mkdir $@

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HDRS)
			@$(CC) $(CFLAGS) $(HDR_INC) -c $< -o $@


all: ${NAME} ${HDRS}

clean:
	@${RM} $(OBJS_PATH)
	@echo "\t[ $(RED)✗$(NONE) ] libft/$(OBJ_DIR) directory"

fclean: clean
		@rm -f ${NAME}
		@echo "\t[ $(RED)✗$(NONE) ] libft/$(NAME) library"

re: fclean all

.PHONY: all clean fclean re
