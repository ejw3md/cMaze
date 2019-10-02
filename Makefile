OBJS = solve.o ECL_queue.o
CFLAGS = -c -g 
LDFLAGS = -lm

all: solve.o ECL_queue.o a.out

%.o : ./ECL/%.c	
	gcc $(CFLAGS) $^
%.o : %.c
	gcc $(CFLAGS) $^
solve.o : ./ECL/ECL_queue.h solve.c
	gcc $(CFLAGS) solve.c
a.out : $(OBJS)
	gcc $(OBJS) $(LDFLAGS) -o $@
clean:
	rm -f a.out
	rm -f $(OBJS)
