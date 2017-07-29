# opuscmd
Some ogg/opus commands

# hard dependencies
    libogg
    libopus

# soft dependencies
    pcc (may use BYACC and REFLEX to compile this, or just use tcc)
    tcc
    ld (TODO which ld? gnu works)
    musl
    (You can modify Makefile to use gcc quite easily)
