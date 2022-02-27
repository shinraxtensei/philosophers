
# This is a minimal set of ANSI/VT100 color codes
_END=$'\x1b[0m'
_BOLD=$'\x1b[1m'
_UNDER=$'\x1b[4m'
_REV=$'\x1b[7m'

# Colors
_GREY=$'\x1b[30m'
_RED=$'\x1b[31m'
_GREEN=$'\x1b[32m'
_YELLOW=$'\x1b[33m'
_BLUE=$'\x1b[34m'
_PURPLE=$'\x1b[35m'
_CYAN=$'\x1b[36m'
_WHITE=$'\x1b[37m'

# Inverted, i.e. colored backgrounds
_IGREY=$'\x1b[40m'
_IRED=$'\x1b[41m'
_IGREEN=$'\x1b[42m'
_IYELLOW=$'\x1b[43m'
_IBLUE=$'\x1b[44m'
_IPURPLE=$'\x1b[45m'
_ICYAN=$'\x1b[46m'
_IWHITE=$'\x1b[47m'





NAME = philo

SRCS = src/philo.c src/pimp_my_philos.c src/utils.c \
		src/monitor.c src/philos_lifespan.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread

HEADER = src/philo.h

all: $(NAME) $(HEADER)

$(NAME): $(SRCS) $(OBJS) $(HEADER)
	@gcc $(CFLAGS) $(SRCS) -o $@
	@echo                                                        
	@echo " ${_IGREY} ------------------------------------  ${_END} "
	@echo " ${_CYAN} ${_REV}  ----------- R E A D Y --------------  ${_END} "
	@echo " ${_IGREY} ------------------------------------  ${_END} "
	@echo                                                        

clean :
	@rm -rf $(OBJS) 

fclean :
	@rm -rf $(OBJS) $(NAME) 

re :
	@Make fclean all


.PHONY : all clean fclean re