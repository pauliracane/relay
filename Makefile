CFLAGS+=-std=c11 -D_GNU_SOURCE
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline -fstack-usage

LDLIBS+=-lm

all: listener dispatcher

listener: listener.o

dispatcher: dispatcher.o

.PHONY: clean debug

clean:
	-rm *.o *.su listener dispatcher .echo_socket

debug: CFLAGS+=-g
debug: listener dispatcher

profile: CFLAGS +=-pg
profile: all

