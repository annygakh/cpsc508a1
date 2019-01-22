large:
	gcc -g -Wall -o large large_file.c

small:
	gcc -g -Wall  -o small small_file.c

clean:
	-rm -f *.o
	-rm -f small
	-rm -f large