#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int primeq(int i) {
  int j;
  int ret=1;
  for (j=2; j<i; j++) {
    if (i/j*j == i) {
      ret=0;
      break;
    }
  }
  return ret;
}

int next(int i) {
  int offset=0;
  if (i/3*3 == i) offset += -1;
  if (i/5*5 == i) offset += -8;
  if (i/7*7 == i) offset += -8;
  return i+offset >= 0 ? i+offset : i;
}

int finalnext(int i) {
  int j=next(i);
  while (j!=i) {
    i=j;
    j=next(i);
  }
  return j;
}

char *getarrow(int i, int j) {
  static char arrow[5];
  int narrow=0;
  int x,y,newx,newy;
  memset(arrow,0,sizeof(arrow));
  x=i%8;
  y=i/8;
  newx=j%8;
  newy=j/8;
  if (newx>x)   arrow[narrow++] = 'R';
  if (newx<x)   arrow[narrow++] = 'L';
  if (newy<y)   arrow[narrow++] = 'D';
  if (newy<y-1) arrow[narrow++] = 'D';
  return arrow;
}

int throwdie() {
  return rand()%6+1;
}

int getcost(int pos) {
  if (pos >= 113) return 5;
  if (pos >= 97) return 4;
  if (pos >= 65) return 3;
  if (pos >= 33) return 2;
  return 1;
}

typedef struct {
  int pos;
  int nmoves;
  int dollars;
  int thresh; /* threshold beyond which we pay */
  int debug;
  int id;
} game_t;
  
/* simulate 1 game */
void simulate(game_t *game) {
  while (game->pos < 128) {
    int roll=throwdie()+throwdie();
    int nextpos=0;
    int cost=0;
    int dopay=0;
    game->pos += roll;
    game->dollars += primeq(game->pos);
    game->nmoves++;
    nextpos=finalnext(game->pos);
    cost=getcost(game->pos);
    dopay = nextpos < game->pos && game->pos >= game->thresh && game->dollars >= cost;
    if (game->debug) {
      printf("game  id:%d  thresh:%d  roll:%d  pos:%d  nextpos:%d  dopay:%d  dollars:%d\n"
	     , game->id, game->thresh, roll, game->pos, nextpos, dopay, game->dollars);
    }
    if (game->pos<128) {
      if (dopay) {
	game->dollars -= cost;
      } else {
	game->pos=nextpos;
      }
    }
  } 
}

void analyze() {
  int i=0;
  int thresh=0;
  int gameid=0;
  for (thresh=1; thresh<128; thresh+=8) {
    game_t sum;
    memset(&sum,0,sizeof(sum));
    sum.thresh=thresh;
    int niter=0;
    for (i=0; i<1000; i++) {
      game_t game;
      memset(&game,0,sizeof(game));
      game.debug=thresh==57 && i==0;
      game.id=gameid++;
      game.thresh=thresh;
      simulate(&game);
      sum.nmoves+=game.nmoves;
      sum.dollars+=game.dollars;
      niter++;
    }
    printf("simulate  thresh:%d  nmoves:%d  money_at_end:%d\n",sum.thresh, sum.nmoves/niter, sum.dollars/niter);
  }
}

int main() {
  int i;
  for (i=1; i<=128; i++) {
    int prime=primeq(i);
    int j=next(i);
    char *arrow=getarrow(i,j);
    printf("%d  %s  ->%d  arrow:%s\n", i, (prime?"prime":"     "), finalnext(i), arrow);
  }
  analyze();
  return 0;
}
