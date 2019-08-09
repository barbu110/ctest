CFLAGS := -fPIC -Iinclude

SRC := example.c

OBJECTS := src/ctest_main.o src/assertions.o

LDYNAMIC := -Llib/

LDLIBRPATH := lib/

SHARED_LIB = lib/libctests.so

#Currently, the supported suites are Basic and Modern.
MY_SUITES := -DSUITE=Basic

all: $(SHARED_LIB) example

src/ctest_main.o: src/ctest_main.c

src/assertions.o: src/assertions.c

$(SHARED_LIB): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $@ $^

example:
	$(CC) $(MY_SUITES) $(CFLAGS) -Wl,-rpath=$(LDLIBRPATH) $(SRC) -o $@ $(LDYNAMIC) -lctests

clean:
	@echo "Cleaning..."
	@rm -rfv src/ctest_main.o src/assertions.o example lib/libctests.so
