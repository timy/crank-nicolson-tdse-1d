all:
	g++ cn_tdse.cc -O3 -o app
#	g++ cn_tdse.cc -O3 -fPIC -c -o libcntdse.o
#	g++ libcntdse.o -O3 -shared -o libcntdse.so
#	g++ main.cc -O3 -c -o main.o
#	g++ main.o -O3 -L. -lcntdse -o test

clean:
	rm -f *.o *.so
