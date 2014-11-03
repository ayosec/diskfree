all: diskfree

diskfree: diskfree.c
	gcc -Wall -O2 -o $@ $<

clean:
	rm diskfree

.PHONY: clean
