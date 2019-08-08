CFLAGS := -Iinclude

example: example.c src/ctest_main.o src/assertions.o

src/ctest_main.o: src/ctest_main.c

src/assertions.o: src/assertions.c

clean:
	@echo "Cleaning..."
	@rm -rfv src/ctest_main.o src/assertions.o example
