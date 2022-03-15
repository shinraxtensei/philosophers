

NAME = philo

BONUS = philo_bonus

SRCS = src/philo.c src/pimp_my_philos.c src/utils.c \
		src/monitor.c src/philos_lifespan.c

SRCS_BONUS = src_bonus/monitor.c src_bonus/philo_bonus.c \
			src_bonus/philos_lifespan.c src_bonus/pimp_my_philos.c \
			src_bonus/utils.c src_bonus/processes_ruler.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread

HEADER = src/philo.h

HEADER_BONUS = src_bonus/philo_bonus.h

all: $(NAME) $(HEADER)

$(NAME): $(SRCS) $(OBJS) $(HEADER)
#	@gcc $(CFLAGS) $(SRCS) -o $@
#	@echo                                                        
#	@echo " ${_IGREY} ------------------------------------  ${_END} "
#	@echo " ${_CYAN} ${_REV}  ----------- R E A D Y --------------  ${_END} "
#	@echo " ${_IGREY} ------------------------------------  ${_END} "
#	@echo
	@gcc $(CFLAGS) $(SRCS) -o $@
	@printf '$(shell tput setaf 29)Finished Compiling √ %s\n$(shell tput sgr0)' $1
	@printf '$(shell tput setaf 69)Linking objs...\n$(shell tput sgr0)'
	@printf '$(shell tput setaf 29)Finished linking √ %s\n$(shell tput sgr0)' $1


bonus: $(SRCS_BONUS) $(OBJS_BONUS) $(HEADER_BONUS)
	@gcc $(CFLAGS) $(SRCS_BONUS) -o $(BONUS)
	@printf '$(shell tput setaf 29)Finished Compiling √ %s\n$(shell tput sgr0)' $1
	@printf '$(shell tput setaf 69)Linking objs...\n$(shell tput sgr0)'
	@printf '$(shell tput setaf 29)Finished linking √ %s\n$(shell tput sgr0)' $1

clean :
	@rm -rf $(OBJS) $(OBJS_BONUS)

fclean :
	@rm -rf $(OBJS) $(NAME)  $(OBJS_BONUS) $(BONUS)

re :
	@Make fclean all


.PHONY : all clean fclean re