NAME = minishell

HEADERS_DIR		= ./includes/
SOURCES_DIR		= ./sources/

HEADERS_LIST	= minishell.h
SOURCES_LIST	= check.c \
				error.c \
				exp_var.c \
				free.c \
				ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_export.c \
				ft_pwd.c \
				ft_unset.c \
				get.c \
				read_utils.c \
				read.c \
				run_instruction.c \
				run_main.c \
				run_redirect.c \
				setup.c \
				split.c \
				start_env.c \
				ft_exit.c \
				setup_signal.c \
				handle_signal.c \
				clear_fd.c \
				main.c \
				# test.c \

HEADERS			= ${addprefix ${HEADERS_DIR}, ${HEADERS_LIST}}
SOURCES			= ${addprefix ${SOURCES_DIR}, ${SOURCES_LIST}}
INCLUDES		= -I ${HEADERS_DIR} -I ${LIBFT_HEADERS}

OBJECTS_DIR		= ./objects/
OBJECTS_LIST	= ${patsubst %.c, %.o, ${SOURCES_LIST}}
OBJECTS			= ${addprefix ${OBJECTS_DIR}, ${OBJECTS_LIST}}

LIBFT			= ${LIBFT_DIR}libft.a
LIBFT_DIR		= ./libft/
LIBFT_HEADERS	= ${LIBFT_DIR}inc/

CC				= cc
CFLAGS			= -g3 #-Wall -Werror -Wextra

RM 				= rm -f

all:			${NAME}
				@echo Everything went well!

libft:			${LIBFT}

${NAME}:		${LIBFT} ${OBJECTS_DIR} ${OBJECTS}
			${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} ${INCLUDES} -lreadline -o ${NAME}

${OBJECTS_DIR}:
			mkdir -p ${OBJECTS_DIR}
			@echo objects folder has been created!
${OBJECTS_DIR}%.o : ${SOURCES_DIR}%.c ${HEADERS}
			${CC} ${CFLAGS} -c ${INCLUDES} $< -o $@

${LIBFT}:
			make -sC ${LIBFT_DIR}
			@echo libft has been compiled!

clean:
			make -sC ${LIBFT_DIR} clean
			rm -rf ${OBJECTS_DIR}

fclean:		clean
			${RM} ${LIBFT}
			${RM} ${NAME}

re:			fclean all

.PHONY:		all, clean, fclean, re, test
