OBJDIR = points_o

SRCS = ft_check.c \
	ft_putchar.c \
	ft_put_u.c \
	ft_printf.c \
	ft_put_d.c \
	ft_put_x.c \
	ft_put_c.c \
	ft_put_s.c \
	ft_put_xmaj.c \
	ft_put_p.c \

CC = gcc
CFLAGS = -Wall -Werror -Wextra

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

DEPDIR = dep
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

NAME = libftprintf.a

AR = ar rcs

RM = rm -f

all : $(NAME)
	
$(NAME) : $(OBJS) | $(OBJDIR)
	@$(AR) $(NAME) $(OBJS)

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

-include $(wildcard $(DEPDIR)/*.d)

.PHONY : all re fclean clean re
