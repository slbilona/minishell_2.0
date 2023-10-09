SRCDIR = srcs
OBJDIR = points_o/
DEPDIR = dep
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

SRCS = main.c \
		cd.c \
		exit.c \
		exec.c \
		init.c \
		echo.c \
		free.c \
		expand.c \
		signaux.c \
		utils_1.c \
		utils_2.c \
		heredoc.c \
		ft_space.c \
		parsing_1.c \
		parsing_2.c \
		ft_quotes.c \
		builtins_1.c \
		builtins_2.c \
		pre_parsing.c \
		redirection.c \
		utils_expand.c \
		ft_new_split.c \
		utils_builtins.c \
		ft_clean_quotes.c \
		ft_expand_heredoc.c \

OBJFILES = $(SRCS:.c=.o)
OBJS 	= $(addprefix $(OBJDIR), $(OBJFILES))
VPATH   = srcs pars utils exec builtins

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I /usr/include
NAME = minishell
LIBFT = libft_printf_gnl/libft.a

all : $(NAME)

${NAME}: $(OBJDIR) ${OBJS}
	@make -C libft_printf_gnl
	@$(CC) $(CFLAGS) ${OBJS} $(LIBFT) -o $(NAME) -lreadline
	@echo "🧚 tout est prêt 🧚"
		
${OBJDIR}%.o: %.c $(DEPDIR) 
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DEPDIR):
	mkdir -p $(DEPDIR)

clean :
	rm -rf $(OBJDIR) $(DEPDIR)
	make clean -C libft_printf_gnl
	clear
	@echo "🧚 tout propre 🧚"

fclean : clean
	make fclean -C libft_printf_gnl
	rm -f $(NAME)
	clear
	@echo "🧚 tout propre 🧚"

leaks: $(NAME)
	valgrind --suppressions=autre/ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

git : fclean
	git add *
	git commit
	git push

re : fclean all

-include $(wildcard $(DEPDIR)/*.d)

.PHONY : all clean fclean re git

.SILENT : all clean fclean re git $(NAME) $(OBJDIR)
