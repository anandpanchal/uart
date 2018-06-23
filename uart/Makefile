all: recv send

recv: recv.c
	arm-cortexa8-linux-gnueabihf-gcc recv.c -o recv
#	gcc recv.c -o recv

send: send.c
	arm-cortexa8-linux-gnueabihf-gcc send.c -o send
#	gcc send.c -o send

clean:
	rm -rf send recv
