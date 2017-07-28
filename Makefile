BIN = opus2pcm
CFLAGS = -Os -pedantic -std=c89 -Wall -Wextra

all: options $(BIN)

options:
	@echo "CFLAGS = $(CFLAGS)"
	@echo "CC     = $(CC)"
	@echo "LD     = $(LD)"

$(BIN): $(BIN:=.o)
	@echo "CC -o $@"
	@$(CC) -o $@ $@.o

.c.o:
	@echo "CC $<"
	@$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(BIN) $(BIN:=.o)
