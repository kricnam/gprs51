all:	gprs51.ihx	
	makebin -p < gprs51.ihx > gprs51.bin
gprs51.ihx:	gprs51.c *.rel
	sdcc gprs51.c *.rel
*.rel:	*.c
	sdcc -c $@
	
