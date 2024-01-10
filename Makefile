
OBJS=src/sha256.o
TESTS=tests/basic tests/stream tests/sha256sum

CFLAGS += -Iinclude

.PHONY: all tests clean
.SUFFIXES: .c .o

all: libsha2.so libsha2.a
tests: $(TESTS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

libsha2.so: $(OBJS) src/streaming.c
	$(CC) $(LDFLAGS) -shared -o $@ $(OBJS)

libsha2.a: $(OBJS) src/streaming.c
	$(AR) $(ARFLAGS) $@ $(OBJS)

tests/basic: libsha2.a tests/basic.o
	$(CC) $(LDFLAGS) -o $@ tests/basic.o libsha2.a

tests/stream: libsha2.a tests/stream.o
	$(CC) $(LDFLAGS) -o $@ tests/stream.o libsha2.a

tests/sha256sum: libsha2.a tests/sha256sum.o
	$(CC) $(LDFLAGS) -o $@ tests/sha256sum.o libsha2.a

clean:
	rm -f $(OBJS) $(TESTS) tests/*.o libsha2.so libsha2.a
