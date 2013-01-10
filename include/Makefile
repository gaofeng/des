libDES.a : DES.o 2DES.o 3DES.o DESCBC.o 2DESCBC.o 3DESCBC.o
	ar -r ../lib/libDES.a DES.o 2DES.o 3DES.o DESCBC.o 2DESCBC.o 3DESCBC.o
	ranlib ../lib/libDES.a

3DESCBC.o : 3DESCBC.c 3DESCBC.h DESCBC.c DESCBC.h 3DES.c 3DES.h DES.c DES.h
	gcc -c 3DESCBC.c

2DESCBC.o : 2DESCBC.c 2DESCBC.h DESCBC.c DESCBC.h 2DES.c 2DES.h DES.c DES.h
	gcc -c 2DESCBC.c

DESCBC.o : DESCBC.c DESCBC.h DES.c DES.h
	gcc -c DESCBC.c

3DES.o : 3DES.c 3DES.h DES.c DES.h
	gcc -c 3DES.c

2DES.o : 2DES.c 2DES.h DES.c DES.h
	gcc -c 2DES.c

DES.o : DES.c DES.h
	gcc -c DES.c

