CC = gcc
CFLAGS = -O2 -g
LIBS = -lcdk -lncurses

TARGET = nih
SRCS = nih.c nih2.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
