
#include <unistd.h>
#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_FLAKES 500

// 1/10 second in microseconds
#define TICK 100000
typedef struct pos {
  int x;
  int y;
  char* type;
} pos;

static char* flake1 = "\xe2\x9d\x84";
static char* flake2 = "\xe2\x9d\x85";
static char* flake3 = "\xe2\x9d\x86";



int main(int argc, const char * argv[]) {
    // http://stackoverflow.com/questions/9922528/how-to-make-ncurses-display-utf-8-chars-correctly-in-c
  setlocale(LC_CTYPE, "");

  char *flakeCodes[] = {flake1,flake2,flake3};

  initscr();
  noecho();
  curs_set(FALSE);

  int wx;
  int wy;
  getmaxyx(stdscr, wy, wx);

  // TODO calculate max flakes from screen height.
  pos flakes[MAX_FLAKES];
  int nflakes = 0;


  int ticks = 0;
  while (1) {
    // generate a snow flake every second
    if(ticks % 2 == 0) {
      int x = random() % wx;
      pos newFlake;
      newFlake.x = x;
      newFlake.y = 0;
      int flakeType = random() % 3;
      newFlake.type = flakeCodes[flakeType];
      // newFlake.type = flake2;
      int i = nflakes % MAX_FLAKES;
      flakes[i] = newFlake;
      nflakes++;
    }

    clear();
    for (int i = 0; i < nflakes; ++i) {
      pos *flake = &flakes[i];
      int driftx = (random() % 3);
      int driftdir = (random() % 2) - 1 ? 1 : -1;
      flake->x += driftx * driftdir;
      flake->y += 1;
      /* code */
      mvprintw(flake->y, flake->x, flake->type);
    }
    // mvprintw(y, 10, flake1);
    refresh();
    // y++;
    ticks++;
    usleep(TICK);
  }
  // E2 9D 86


//    refresh();
  getch();
  endwin();
  return 0;
}