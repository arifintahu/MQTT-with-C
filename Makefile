all: pub1.c sub1.c pub2.c sub2.c
	gcc -g -Wall -o pub1 pub1.c mqtt.c
	gcc -g -Wall -o sub1 sub1.c mqtt.c
	gcc -g -Wall -o pub2 pub2.c mqtt.c
	gcc -g -Wall -o sub2 sub2.c mqtt.c

clean:
	$(RM) pub1 sub1 pub2 sub2
