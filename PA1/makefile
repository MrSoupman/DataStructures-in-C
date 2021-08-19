BigTest: BigTest.o BigInteger.o
	gcc BigTest.o BigInteger.o -o BigTest
debug: BigTest.o BigInteger.o
	gcc -g BigTest.o BigInteger.o -o BigTest
BigTest.o: BigTest.c BigInteger.h
	gcc -g -c BigTest.c
BigInteger.o: BigInteger.c BigInteger.h
	gcc -g -c BigInteger.c
clean: 
	rm -f BigTest *.o
