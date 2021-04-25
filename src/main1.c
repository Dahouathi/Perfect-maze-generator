#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define largeur 800
#define hauteur 600

int main(int argc , char **argv)
{
/*
  SDL_version nb;
  SDL_VERSION(&nb);

  printf("hello %d %d %d !\n",nb.major, nb.minor, nb.patch);
*/
  SDL_Window *screen = NULL ;
  SDL_Renderer *renderer = NULL ;
  if (SDL_Init(SDL_INIT_VIDEO)!=0)
  {
    SDL_Log("ERREUR : Initiamisation >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }
  // Execution du prog . . .

/*
  screen =SDL_CreateWindow("new window num°1S",SDL_WINDOWPOS_CENTERED,
  SDL_WINDOWPOS_CENTERED,800,600,0);
  if (screen ==NULL)
  {
    SDL_Log("ERREUR : creation window >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  renderer=SDL_CreateRenderer(screen,-1,SDL_RENDERER_SOFTWARE);
  if (renderer ==NULL)
  {
    SDL_Log("ERREUR : creation renderer >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }
*/
// creation window et SDL_Renderer
/*------------------------------------------*/

  if(SDL_CreateWindowAndRenderer(800,600,0,&screen,&renderer)!=0)
  {
    SDL_Log("ERREUR : can't make window nd renderer >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /*------------------------------------------*/

  if (SDL_SetRenderDrawColor( renderer ,112,164,200,SDL_ALPHA_OPAQUE)!=0)
  {
    SDL_Log("ERREUR : color fucked >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /*------------------------------------------*/

  if (SDL_RenderDrawPoint(renderer,200,300)!= 0)
  {
    SDL_Log("ERREUR : impo draw point >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /*------------------------------------------*/

  if(SDL_RenderDrawLine(renderer,200,300,200,500)!=0)
  {
    SDL_Log("ERREUR : line eror >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /*------------------------------------------*/

  SDL_Rect rectangle ;
  rectangle.x=10;
  rectangle.y=10;
  rectangle.w=100;
  rectangle.h=200;
  if(SDL_RenderFillRect(renderer, &rectangle)!=0)
  {
    SDL_Log("ERREUR : draw rect bad so bad >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /*------------------------------------------*/

SDL_Surface *image =NULL;
SDL_Texture *texture =NULL;

image = SDL_LoadBMP("src/img.bmp");
if(image==NULL)
{
  SDL_Log("ERREUR : can't load image >%s\n",SDL_GetError());
  exit(EXIT_FAILURE);
}

texture=SDL_CreateTextureFromSurface(renderer,image);
SDL_FreeSurface(image); // madech nst7a9o image donc najmo nfar8oha mel memo <3
if (texture == NULL)
{
  SDL_Log("ERREUR : fail load texture >%s\n",SDL_GetError());
  exit(EXIT_FAILURE);
}

SDL_Rect rect ;

if (SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h)!=0)
{
  printf("mafamch affichage mte3 image00");
}

rect.x=(800-rect.w)/2;
rect.y=(600-rect.h)/2;


if (SDL_RenderCopy(renderer,texture,NULL,&rect)!=0)
{
  printf("yekhaw ad matjmm taml chy");
}

SDL_Rect racket1;
racket1.h=hauteur/10;
racket1.w=largeur/1000;
racket1.x=racket1.h / 2;
racket1.y=(racket1.w +hauteur)/2;
if(SDL_SetRenderDrawColor(renderer, 255,0,0,SDL_ALPHA_OPAQUE)!=0)
  //PrintEror("can't change color");
  printf("kk00");
if(SDL_RenderFillRect(renderer, &racket1) != 0)
    printf("kk00");

  /*------------------------------------------*/

  SDL_RenderPresent(renderer); // mettre a jour le renderer x))


/*------------------------------------------*/



  if (SDL_RenderClear(renderer) != 0)
  {
    SDL_Log("ERREUR : clear renderer >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_Delay(2000); // delay l'apparition du window

  /*------------------------------------------*/

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  SDL_Quit();

  return EXIT_SUCCESS; //0 ;
}


//gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
