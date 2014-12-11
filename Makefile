snow-now: snow
	./snow

snow: snow.c
	cc -Wall -lncurses snow.c -o snow

.PHONY: snow-now