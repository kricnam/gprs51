all:	gprs51.bin
	makebin -s 1024 < gprs51.ihx > gprs51.bin
gprs51.bin:	gprs51.ihx
	sdcc gprs51.c *.rel
*.rel:	*.c
	sdcc -c $@
	
