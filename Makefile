BIN = opus2pcm ogginspect

MUSLDIR = /usr/local/musl
TCCDIR = /usr/local/lib/tcc
CRT = $(MUSLDIR)/lib/crt1.o $(MUSLDIR)/lib/libc.a $(TCCDIR)/libtcc1.a

CC = pcc
INC = -I$(MUSLDIR)/include -I/usr/local/include
CFLAGS = -Os -pedantic -std=c89 -Wall -Wextra $(INC)
LIB = -logg
LDFLAGS = -static $(LIB)

all: options $(BIN)

options:
	@echo "CFLAGS = $(CFLAGS)"
	@echo "CC     = $(CC)"
	@echo "LD     = $(LD)"

$(BIN): $(BIN:=.o)
	@echo "LD $@"
	@$(LD) -o $@ $@.o $(LDFLAGS) $(CRT)

.c.o:
	@echo "CC $<"
	@$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(BIN) $(BIN:=.o)
