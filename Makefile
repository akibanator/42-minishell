NAME = minishell

HEADERS_DIR		= ./includes/
SOURCES_DIR		= ./sources/

HEADERS_LIST	= minishell.h
SOURCES_LIST	= builtin/ft_cd.c \
				builtin/ft_echo.c \
				builtin/ft_env.c \
				builtin/ft_export.c \
				builtin/ft_pwd.c \
				builtin/ft_unset.c \
				builtin/ft_exit.c \
				error/error.c \
				memory/free.c \
				memory/clear_fd.c \
				parse/check.c \
				parse/read.c \
				parse/read_utils.c \
				run/run_instruction.c \
				run/run_main.c \
				run/run_redirect.c \
				run/here_doc.c \
				setup/start_env.c \
				setup/exp_var.c \
				setup/setup.c \
				setup/split.c \
				signal/setup_signal.c \
				signal/handle_signal.c \
				util/get.c \
				main.c \
				# test.c \

HEADERS			= ${addprefix ${HEADERS_DIR}, ${HEADERS_LIST}}
SOURCES			= ${addprefix ${SOURCES_DIR}, ${SOURCES_LIST}}
INCLUDES		= -I ${HEADERS_DIR} -I ${LIBFT_HEADERS}

OBJECTS_DIR		= ./objects/
OBJECTS_SUBDIR	= ${OBJECTS_DIR}builtin/
OBJECTS_SUBDIR	+= ${OBJECTS_DIR}memory/
OBJECTS_SUBDIR	+= ${OBJECTS_DIR}parse/
OBJECTS_SUBDIR	+= ${OBJECTS_DIR}run/
OBJECTS_SUBDIR	+= ${OBJECTS_DIR}signal/
OBJECTS_SUBDIR	+= ${OBJECTS_DIR}setup/
OBJECTS_SUBDIR	+= ${OBJECTS_DIR}error/
OBJECTS_SUBDIR	+= ${OBJECTS_DIR}util/
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
			mkdir -p ${OBJECTS_SUBDIR}
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
