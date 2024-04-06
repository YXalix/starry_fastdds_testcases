TARGET := eventfd-testcases

DIRS = .

FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

OBJS = $(patsubst %.c,%.o, $(FILES))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS) $(CFLAGES)

$(OBJS):%.o: %.c
	$(CC) -c $< -o $@ $(LIBS) $(CFLAGES)

clean:
	$(RM) $(OBJS) $(TARGET)
