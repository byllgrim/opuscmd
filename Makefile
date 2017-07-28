BIN = opus2pcm

MUSLDIR = /usr/local/musl
TCCDIR = /usr/local/lib/tcc
INC = -I$(MUSLDIR)/include
CRT = $(MUSLDIR)/lib/crt1.o $(MUSLDIR)/lib/libc.a $(TCCDIR)/libtcc1.a

CC = pcc
CFLAGS = -Os -pedantic -std=c89 -Wall -Wextra $(INC)

all: options $(BIN)

options:
	@echo "CFLAGS = $(CFLAGS)"
	@echo "CC     = $(CC)"
	@echo "LD     = $(LD)"

$(BIN): $(BIN:=.o)
	@echo "LD $@"
	@$(LD) -o $@ $@.o $(CRT)

.c.o:
	@echo "CC $<"
	@$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(BIN) $(BIN:=.o)
