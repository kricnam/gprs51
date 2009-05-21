
MAIN = gprs51
SOURCE = $(filter-out  $(MAIN).%, $(wildcard *.c))
OBJS = $(patsubst %c,%rel,$(SOURCE))


all:	$(MAIN).ihx	
	makebin -p < $(MAIN).ihx > $(MAIN).bin
gprs51.ihx:	$(MAIN).c $(OBJS)
	sdcc  $^
%.rel:	%.c
	sdcc -c $<
clean:
	echo $(SOURCE)
	echo $(OBJS)
	rm *.rel
	rm *.sym
	rm *.map
	rm *.mem *.lnk *.lst *.rst *.asm
	rm $(MAIN).ihx $(MAIN).bin	
