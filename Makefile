# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: motero <motero@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 18:38:23 by motero            #+#    #+#              #
#    Updated: 2023/02/11 15:48:20 by motero           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#=============================================================================#
#                                 HEADERS                                     #
#=============================================================================#

HDR_NAME = minishell.h structures.h execution.h builtin.h expander.h lexer.h parsing.h signal_handling.h ast.h garbage_collector.h error_management.h
HDR_DIR = includes/
HDRS = $(addprefix $(HDR_DIR), $(HDR_NAME))
HDR_INC = -I includes -I libft/includes

#================================================================flx=============#
#                                 LIBRARIES                                     #
#=============================================================================#

LIBFT_HDIR = libft/includes
LIBFT_HDIR_INC = -I./libft/includes/
LIB_BINARY = -Llibft -lft -lreadline
LIBFT = libft/libft.a

#=============================================================================#
#                                 MiniLIBX                                    #
#=============================================================================#

MINILIBX_HDIR = includes/minilibx-linux/
MINILIBX_HDIR_INC = -I ./minilibx-linux/
MINILIBX_BINARY = -Lmlx_linux -lmlx_Linux -L$(MINILIBX_HDIR) -Imlx_linux -lXext -lX11 -lm -lz
MINILIBX = $(MINILIBX_HDIR)libmlx.a


#=============================================================================#
#                               SOURCES                                       #
#=============================================================================#

SRCS_DIR_project = sources/

SRCS_RAW_NAME_DIRECTORIES = $(wildcard $(SRCS_DIR_project)* )
SRCS_NAME_DIRECTORIES = $(patsubst sources/%,%,$(SRCS_RAW_NAME_DIRECTORIES))

#SRCS_ALL = $(wildcard $(SRCS_RAW_NAME_DIRECTORIES)/)
#SRCS_RAW_ALL = $(shell find $(SRCS_DIR_project) -type f -name "*.c")
#SRCS_ALL = $(patsubst sources/%,%,$(SRCS_RAW_ALL))
#SRCS_NAME_project = $(SRCS_ALL)
SRCS_NAME_project = \
[6]ast/[3]auxiliary_functions.c  \
[6]ast/[2]terminal_functions.c \
[6]ast/[1]no_terminal_functions.c \
[6]ast/[2-bis]terminal_functions.c \
[6]ast/[0]main_ast.c \
[6]ast/[4-bis]redirection_functions.c \
[6]ast/[4]redirection_functions.c \
[7]garbage_collector/[0]main_garbge_collector.c \
[7]garbage_collector/[1]free_functions.c \
[7]garbage_collector/[2]free_blocks.c \
[4]execution/[0]main_execution.c \
[4]execution/[2]redirection_handling.c \
[4]execution/[10]utilities.c \
[4]execution/[3]traversing_ast.c \
[4]execution/[5]builtins_exec.c \
[4]execution/[11]pid_management.c \
[4]execution/[1]pipe_traversing.c \
[4]execution/[4]fds_ands_redirs.c \
[0]parsing/[0]here_doc.c \
[0]parsing/[2]handle_quote.c \
[0]parsing/[1]parsing_error.c \
[1]init_mini.c \
[5]signal_handling/[0]signal_handling.c \
[5]signal_handling/[2]execution_signals.c \
[5]signal_handling/[1]here_doc_signal.c \
[8]error_management/[0]main_error.c \
[8]error_management/[1]error_messages.c \
[3]builtin/[2-d]export_sort.c \
[3]builtin/[4]echo.c \
[3]builtin/[5]pwd.c \
[3]builtin/[10]env_manipulation.c \
[3]builtin/[2-c]export_tools.c \
[3]builtin/[2-b]export.c \
[3]builtin/[1]cd.c \
[3]builtin/[3]exit.c \
[3]builtin/[2]ft_environment.c \
[3]builtin/[2-a]unset.c \
[3]builtin/[0]builtin_main.c \
[3]builtin/[11]utilities.c \
[0]main.c \
[1]lexer/[0]lexer.c \
[1]lexer/[1]lexer_utils.c \
[1]lexer/[3]tokens_utils.c \
[2]expand/[3-b]expand_export_utils.c \
[2]expand/[0-b]env_utils.c \
[2]expand/[0-a]env.c \
[2]expand/[1]expand.c \
[2]expand/[4]tild.c \
[2]expand/[2-a]expand_utils_2.c \
[2]expand/[3-a]expand_export.c \
[2]expand/[2-b]expand_utils.c \

SRCS_PROJECT = $(addprefix $(SRCS_DIR_project), $(SRCS_NAME_project))

#=============================================================================#
#                             		GNL                                       #
#=============================================================================#

GNL_DIR = gnl/
GNL_NAME = get_next_line.c \
			get_next_line_utils.c 
			
GNL = $(addprefix $(GNL_DIR), $(GNL_NAME))

GNL_OBJ = $(GNL:.c=.o)



#=============================================================================#
#                                OBJECTS                                      #
#=============================================================================#

OBJS_PATH = objs/
OBJS_NAME = $(SRCS_NAME_project:.c=.o)
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

#=============================================================================#
#                          COMPILATOR & FLAGS                                 #
#=============================================================================#

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fpie #-fsanitize=leak -fsanitize=address
LIBA = ar rc
LIBS = ranlib

RM = rm -Rf

#=============================================================================#
#                                 Profiler                                    #
#=============================================================================#

PROFILE = project_prof

OBJS_PATH_PROFILER = objs_prof/
OBJS_NAME_PROFILER = $(SRCS_NAME_project:.c=.o)
OBJS_PROFILER = $(addprefix $(OBJS_PATH_PROFILER), $(OBJS_NAME_PROFILER))

PROFILER_FLAG = -pg

#=============================================================================#
#                                 Fsanitize                                    #
#=============================================================================#

SANITIZE = project_sanitize

OBJS_PATH_SANITIZE = objs_sanitize/
OBJS_NAME_SANITIZE = $(SRCS_NAME_project:.c=.o)
OBJS_SANITIZE = $(addprefix $(OBJS_PATH_SANITIZE), $(OBJS_NAME_SANITIZE))

SANITIZE_FLAG = -g3 -fsanitize=address -fno-omit-frame-pointer

#=============================================================================#
#                                 Valgrind                                    #
#=============================================================================#

VALGND = project_valgrind

OBJS_PATH_VALGND = objs_valgrind/
OBJS_NAME_VALGND = $(SRCS_NAME_project:.c=.o)
OBJS_VALGND = $(addprefix $(OBJS_PATH_VALGND), $(OBJS_NAME_VALGND))

VALGND_FLAG = -g3

#=============================================================================#
#                                 Callgrind                                    #
#=============================================================================#

CALLGND = project_callgrind

OBJS_PATH_CALLGND = objyRatio
OBJS_PATH_GDB = objs_gdb/
OBJS_NAME_GDB = $(SRCS_NAME_project:.c=.o)
OBJS_GDB = $(addprefix $(OBJS_PATH_GDB), $(OBJS_NAME_GDB))

GDB_FLAG = -g

#=============================================================================#
#                                COLOURS                                      #
#=============================================================================#

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NONE = \033[0m

bold := $(shell tput bold)
normal := $(shell tput sgr0)

#=============================================================================#
#                                RULES                                        #
#=============================================================================#

all: check_libft project ${NAME} ${HDRS}
		@echo "\n $(GREEN) $(bold) \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/ \|/"
		@echo "\t \t[ $(GREEN)✔$(NONE)] $(bold)Project is ready [ $(GREEN)✔$(NONE)]"
		@echo "$(GREEN) $(bold) /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\ \n"

check_libft:
		@echo "\n[ $(BLUE)$(bold)CHECKING LIBFT$(NONE)]"
		@echo "============================================="
		@make -C libft


project:
		@echo "\n == $(bold)$(YELLOW)CHECKING PROJECT$(normal)=="
		@echo "==============================================="

run:
	make
	clear
	valgrind --suppressions=rl.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./$(NAME)

$(OBJS_PATH):
		@mkdir -p $(addprefix $(OBJS_PATH), $(SRCS_NAME_DIRECTORIES))
		@echo "\t [ $(GREEN)✔$(NONE)] $@directories"

$(OBJS_PATH)%.o: $(SRCS_DIR_project)%.c $(HDRS)
		@$(CC) $(CFLAGS) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project"

$(NAME): $(GNL_OBJ) $(OBJS_PATH) $(OBJS) $(HDRS)
		@echo $(SRCS_ALL)
		@$(CC) $(CFLAGS) $(GNL_OBJ) $(OBJS) $(LIB_BINARY) $(HDR_INC) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project"

malloc_test: $(OBJS_PATH) ${GNL_OBJ} $(OBJS)
		@make -C libft
		$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} ${GNL_OBJ} $(LIB_BINARY) -L. -lmallocator

#=============================================================================#
#                                RULES   PROFILER                             #
#=============================================================================#

#To xecute as follows :make sanitizer var="1 2 3"

prof: fclean check_libft project ${PROFILE} ${HDRS} run_prof execute_profiler

execute_profiler :
		@gprof -b ${PROFILE} gmon.out > analysis.txt
		@echo "\t[ $(GREEN) Profling done!$(NONE) ]"
		@echo "========================================"
		@cat analysis.txt

run_prof: project_prof
	@echo "\n[ $(BLUE)$(bold)Executing binary$(NONE) ]"
	./project_prof $(var)

$(OBJS_PATH_PROFILER):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_PROFILER)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(PROFILER_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_prof"

$(PROFILE) : $(OBJS_PATH_PROFILER) $(OBJS_PROFILER) $(LIBFT) $(HDRS)
		@echo " \n[$(bold)$(YELLOW) PROFILER COMPILATION $(NONE)]"
		$(CC) $(CFLAGS) $(PROFILER_FLAG) $(OBJS_PROFILER) $(LIB_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_prof"

#=============================================================================#
#                                RULES   SANITIZER                            #
#=============================================================================#

#to launch as folows  : make sanitizer var="1 2 3"
sanitizer: fclean check_libft project ${SANITIZE} ${HDRS} run_san

run_san: project_sanitize
	@echo "\n\[ $(BLUE)$(bold)===EXECUTING BINARY====$(NONE)]\n"
	./project_sanitize $(var)

$(OBJS_PATH_SANITIZE):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_SANITIZE)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(SANITIZE_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_sanitize"

$(SANITIZE) : $(OBJS_PATH_SANITIZE) $(OBJS_SANITIZE) $(LIBFT) $(HDRS)
		@echo "\n [$(GREEN)$(bold)FSANITIZE COMPILATION$(NONE) ]"
		@$(CC) $(CFLAGS) $(SANITIZE_FLAG) $(OBJS_SANITIZE) $(LIB_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_sanitize"

#make run_sanitize with good run

#=============================================================================#
#                                RULES  VALGRIND                              #
#=============================================================================#

#to launch as folows  : make valgnd var="1 2 3"
valgnd: fclean check_libft project ${VALGND} ${HDRS} run_valgnd

run_valgnd: project_valgrind
	@echo "\n [ $(BLUE)$(bold) Executing binary with valgrind$(NONE)]\n"
	@valgrind ./project_valgrind $(var)

$(OBJS_PATH_VALGND):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_VALGND)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(VALGND_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_valgrind"
ns a passer et  10 projets a rendre avant :(
$(VALGND) : $(OBJS_PATH_VALGND) $(OBJS_VALGND) $(LIBFT) $(HDRS)
		@echo "\n[$(GREEN)$(bold)VALGND COMPILATION"
		@$(CC) $(CFLAGS) $(VALGND_FLAG) $(OBJS_VALGND) $(LIB_BINARY) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_valgrind"


#=============================================================================#
#                                RULES  CALLLGRIND                              #
#=============================================================================#

#to launch as folows  : make valgnd var="1 2 3"
callgnd: fclean check_libft project ${VALGND} ${HDRS} run_callgnd

run_callgnd: project_callgrind
	@echo "\n [ $(BLUE)$(bold) Executing binary with callgrind$(NONE)]\n"
	@valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes  ./project_callgrind $(var)
	@kcachegrind callgrind.out.*

$(OBJS_PATH_CALLGND):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_CALLGND)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(CALLGND_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_callgrind"

$(CALLGND) : $(OBJS_PATH_CALLGND) $(OBJS_CALLGND) $(LIBFT) $(HDRS)
		@echo "\n[$(GREEN)$(bold)CALLGND COMPILATION]"
		@$(CC) $(CFLAGS) $(CALLGND_FLAG) $(LIB_BINARY) $(OBJS_CALLGND) -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_callgrind"

#=============================================================================#
#                                RULES   GDB                                  #
#=============================================================================#

#to launch as folows  : make BDG
bdg: fclean check_libft project ${BDG} ${HDRS} run_bdg

run_bdg: project_gdb
	@echo "\n\[ $(BLUE)$(bold)===EXECUTING BINARY====$(NONE)]\n"
	gdb project_gdb $(var)

$(OBJS_PATH_GDB):
		@mkdir $@
		@echo "\t [ $(GREEN)✔$(NONE)] $@directory"

$(OBJS_PATH_GDB)%.o: $(SRCS_DIR_project)%.c $(HDRS) $(LIBFT)
		@$(CC) $(CFLAGS) $(GDB_FLAG) $(HDR_INC) $(LIBFT_HDIR_INC) -o $@ -c $<
		@echo "\t[ $(GREEN)✔$(NONE) ] $@ objet project_gdb"

$(BDG) : $(OBJS_PATH_GDB) $(OBJS_GDB) $(LIBFT) $(HDRS)
		@echo "\n [$(GREEN)$(bold)BDG COMPILATION$(NONE) ]"
		@$(CC) $(CFLAGS) $(GDB_FLAG) $(OBJS_GDB) $(LIB_BINARY)  -o $@
		@echo "\t[ $(GREEN)✔$(NONE) ] project_gdb"

#=============================================================================#
#                                COMMANDS                                     #
#=============================================================================#

clean:
		@echo "[ $(RED)$(bold)STARTING CLEAN$(NONE) ]"
		@echo "==================================="
		@${RM} $(OBJS_PATH) $(OBJS_PATH_PROFILER) $(OBJS_PATH_SANITIZE) $(OBJS_PATH_VALGND) $(OBJS_CALLGND) $(OBJS_PATH_GDB) $(GNL_OBJ)
		@rm -rf analysis.txt gmon.out callgrind.out.* ${PROFILE}
		@echo "\t[ $(RED)✗$(NONE) ] $(OBJ_DIR) directory"
		@make -C ./libft/ clean

fclean: clean
		@rm -f ${NAME} ${PROFILE} ${SANITIZE} ${VALGND} ${CALLGND} ${BDG}
		@echo "\t[ $(RED)✗$(NONE) ] $(NAME) executable"
		@make -C ./libft/ fclean

re: fclean all

.PHONY: all clean fclean re