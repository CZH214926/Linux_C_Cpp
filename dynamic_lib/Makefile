path = $(shell pwd)
test_dynamic:test.c
	gcc -o $@ $^ -I $(path)/mylib/include -L $(path)/mylib/lib -l mymath #-static

.PHONY:clean
clean:
	rm -f test_dynamic

