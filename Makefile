LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm
CFLAGS = -Wall -std=c11 -Wextra -g -O0

COMPONENTS = components/drawc.o components/positionc.o
COMPONENTS += components/basic_collidec.o components/team_collidec.o components/teamc.o

OBJS = topdown.o entity.o player.o sprite.o
OBJS += bullet.o event.o component.o direction.o wall.o $(COMPONENTS)

topdown: $(OBJS)

clean:
	find . -name "*.o" -exec rm {} \;
	find . -name "*~" -exec rm {} \;
	find . -name "\#*\#" -exec rm {} \;
	find . -name ".\#*" -exec rm {} \;
	find . -name topdown -exec rm {} \;

