LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = -Wall -std=c11 -Wextra

OBJS = topdown.o player.o sprite.o bullet.o

topdown: $(OBJS)

clean:
	find . -name "*~" -or -name "*.o" -or -name "topdown" -exec rm {} \;
