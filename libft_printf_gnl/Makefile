OBJDIR = points_o

SRCS = ft_memset.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_putchar_fd.c \
	ft_bzero.c \
	ft_putendl_fd.c \
	ft_strrchr.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_putstr_fd.c \
	ft_substr.c \
	ft_isalpha.c \
	ft_split.c \
	ft_tolower.c \
	ft_isascii.c \
	ft_strchr.c \
	ft_toupper.c \
	ft_isdigit.c \
	ft_strdup.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strlcpy.c \
	ft_itoa.c \
	ft_putnbr_fd.c \
	ft_strnstr.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strtrim.c \
	ft_memmove.c \
	ft_striteri.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_put_u_p.c \
	ft_printf.c \
	ft_put_d.c \
	ft_put_x.c \
	ft_put_c_s.c \

CC = gcc
CFLAGS = -Wall -Werror -Wextra

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

DEPDIR = dep
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

AR = ar rcs

RM = rm -f

NAME = libft.a

all: $(NAME)

$(NAME) : $(OBJS) | $(OBJDIR)
	@$(AR) $(NAME) $(OBJS)
	@echo "🧚 tout est prêt 🧚"

$(OBJDIR)/%.o:%.c | $(OBJDIR) $(DEPDIR)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DEPDIR):
	mkdir -p $(DEPDIR)

clean : 
	@rm -rf $(OBJDIR) $(DEPDIR)
	clear
	@echo "🧚 tout propre 🧚"

fclean : clean
	@rm -f $(NAME)
	clear
	@echo "🧚 tout propre 🧚"

re : fclean all

git : fclean
	git add *
	git commit
	git push

-include $(wildcard $(DEPDIR)/*.d)

.PHONY : all clean fclean re git
