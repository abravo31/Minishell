LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

SOURCES_FILES	=	

SOURCES_DIR		=	srcs

HEADER			=	$(SOURCES_DIR)/minishell.h

SOURCES			=	$(addprefix $(SOURCES_DIR)/, $(SOURCES_FILES))

OBJECTS			= 	$(SOURCES:.c=.o)

MAKE			=	make

NAME			=	minishell

CC				=	gcc
RM				=	rm -f

CFLAGS			=	-g3 -Wall -Wextra -Werror #-fsanitize=address

all:	$(NAME)

.c.o:		
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)


$(NAME):	$(MLX_LINUX) $(OBJECTS) $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(HEADER) $(LIBFT)
	@echo "\033[32m$ ${NAME} compiled !"
	@echo "----------------------------\033[0m"

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)
	@echo "\033[32m$ libft compiled !"
	@echo "----------------------------\033[0m"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(RM) $(OBJECTS) 
	@echo "\033[32mClean !\033[0m"

fclean:		clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME) 

re:			fclean all

.PHONY:		all clean fclean re 