
libmymath.a:myadd.o mysub.o
	ar -rc $@ $^
myadd.o:myadd.c
	gcc -c $^ -o $@
mysub.o:mysub.c
	gcc -c $^ -o $@

.PHONY:clean
clean:
	rm -rf output *.o libmymath.a
.PHONY:output
output:
	mkdir -p ../mylib/lib 
	mkdir -p ../mylib/include
	cp *.h ../mylib/include 
	cp *.a ../mylib/lib 
