CC = gcc
CFLAGS = -Wall
OBJS = simpledu.o args.o logRegister.o
XHDRS = simpledu.h args.h logRegister.h
EXEC = simpledu

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c %.h $(XHDRS)
	$(CC) $(CFLAGS) -c $<

.PHONY : clean
clean :
	-rm $(OBJS) $(EXEC)