TRASH = *.o *~ o.* *.a tmp*
GENERATES = prog prog-a prog-so *.so README

all: prog prog-a prog-so README

README: prog
	./$< 2> $@

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. $< -loutput -o $@

fun.o: outlib.h

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared $^ -o $@

test:
	./prog >tmp_prog_res 2>&1
	./prog-a 2>&1 | sed 's/prog-a/prog/g' >tmp_prog-a_res
	LD_LIBRARY_PATH=. ./prog-so 2>&1 | sed 's/prog-so/prog/g' >tmp_prog-so_res
	cmp tmp_prog_res tmp_prog-a_res
	cmp tmp_prog_res tmp_prog-so_res
	cmp tmp_prog-a_res tmp_prog-so_res
	./prog aa >tmp_prog_res 2>&1
	./prog-a aa >tmp_prog-a_res 2>&1
	LD_LIBRARY_PATH=. ./prog-so aa >tmp_prog-so_res 2>&1
	cmp tmp_prog_res tmp_prog-a_res
	cmp tmp_prog_res tmp_prog-so_res
	cmp tmp_prog-a_res tmp_prog-so_res
	./prog aa bb cc >tmp_prog_res 2>&1
	./prog-a aa bb cc >tmp_prog-a_res 2>&1
	LD_LIBRARY_PATH=. ./prog-so aa bb cc >tmp_prog-so_res 2>&1
	cmp tmp_prog_res tmp_prog-a_res
	cmp tmp_prog_res tmp_prog-so_res
	cmp tmp_prog-a_res tmp_prog-so_res
	rm tmp*

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
