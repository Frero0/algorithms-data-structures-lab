.PHONY: all clean demo test

all:
	$(MAKE) -C ex1 all
	$(MAKE) -C ex2 all
	$(MAKE) -C ex3-4 all

test:
	$(MAKE) -C ex1 test
	$(MAKE) -C ex2 test
	$(MAKE) -C ex3-4 test

demo:
	$(MAKE) -C ex1 demo
	$(MAKE) -C ex2 demo
	$(MAKE) -C ex3-4 demo

clean:
	$(MAKE) -C ex1 clean
	$(MAKE) -C ex2 clean
	$(MAKE) -C ex3-4 clean
