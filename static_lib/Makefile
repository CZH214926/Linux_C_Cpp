path = $(shell pwd)
test_static:test.c
	gcc -o $@ $^ -static -I $(path)/mylib/include -L $(path)/mylib/lib -l mymath 
.PHONY:clean
clean:
	rm -f test_static
