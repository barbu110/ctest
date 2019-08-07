CFLAGS := -Iinclude

example: example.c src/ctest_main.o

src/ctest_main.o: src/ctest_main.c

clean:
	@echo "Cleaning..."
	@rm -rfv src/ctest_main.o example
