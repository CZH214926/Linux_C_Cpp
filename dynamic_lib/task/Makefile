#依赖关系列表及执行语句
libmymath.so:myadd.o mysub.o
	gcc -shared -o $@ $^
myadd.o:myadd.c
	gcc -fPIC -c $<
mysub.o:mysub.c
	gcc -fPIC -c $<

#清理项目
.PHONY:clean
clean:
	rm -rf output *.so *.o

#形成最后的交付项目
.PHONY:output 
output:
	mkdir -p ../mylib/lib 
	mkdir -p ../mylib/include
	cp ./*.so ../mylib/lib 
	cp ./*.h  ../mylib/include 

