cc = gcc 
target = proc 
file_list = main.o proc.o

$(target):$(file_list)
	$(cc) $^ -o $@
%.o:%.c
	$(cc) -c $<

.PHONY:clean
clean:
	rm -f $(file_list) $(target)

