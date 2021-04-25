#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*-------------------------------------------------------------------*/
//gcc src/pingpong.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
/*-------------------------------------------------------------------*/
void PrintEror(char *string);



int main(int argc , char**argv)
{
/* initialisation du program */
if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    PrintEror("initialisation");
/* creation window nd rendere */

int largeur = 800;
int hauteur = 600 ;

SDL_Window *screen = NULL ;
SDL_Renderer *renderer =NULL ;

screen =SDL_CreateWindow("PingPong Game", SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED, largeur, hauteur,SDL_WINDOW_RESIZABLE);
if (screen == NULL)
  PrintEror("can't create window");
renderer = SDL_CreateRenderer(screen, -1,
SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
if (renderer==NULL)
  PrintEror("can't make renderer");
/*-------------------------------------------------------------------*/
// make black screen
  if(SDL_SetRenderDrawColor(renderer, 0,0,0,SDL_ALPHA_OPAQUE)!=0)
    PrintEror("can't change color");
  SDL_RenderClear(renderer);
/*-------------------------------------------------------------------*/
//draw racket 1
  SDL_Rect racket1;
  racket1.h=hauteur*2.5/10;
  racket1.w=largeur/100;
  racket1.x=0  ;
  racket1.y=((hauteur-racket1.h)/2);
  if(SDL_SetRenderDrawColor(renderer, 255,0,0,255)!=0)
    PrintEror("can't change color");
  if(SDL_RenderFillRect(renderer, &racket1) != 0)
    PrintEror("cahnt draw racket1");
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
//draw racket 2
  SDL_Rect racket2;
  racket2.h=hauteur*2.5/10;
  racket2.w=largeur/100;
  racket2.x= largeur - racket2.w ;
  racket2.y=((hauteur-racket2.h)/2);
  if(SDL_SetRenderDrawColor(renderer, 255,255,255,255)!=0)
    PrintEror("can't change color");
  if(SDL_RenderFillRect(renderer, &racket2) != 0)
    PrintEror("cahnt draw racket1");
  SDL_RenderPresent(renderer); // mettre a jour le renderer x))

    /*-------------------------------------------------------------------*/
    /*-------------------------------------------------------------------*/
void mouveracket(SDL_Renderer *renderer,SDL_Rect *rect, int r, int g, int b, int v);
/*---------------------------------*/
void SDL_FillCirecle(SDL_Renderer *renderer,int ox,int oy, int R, int r, int g , int b);
/*---------------------------------*/
void MouveBall(SDL_Renderer *renderer, int *largeur , int *hauteur, int v, int r, int g, int b);
/*---------------------------------*/
void mouvepoint(SDL_Renderer *renderer , int largeur, int hauteur, int v , int r, int g, int b);
/*---------------------------------*/
void drawcircle(SDL_Renderer *renderer);
  /*-------------------------------------------------------------------*/
  /*-------------------------------------------------------------------*/
SDL_bool program_lunch = SDL_TRUE;
//mouvepoint(renderer, largeur, hauteur,1, 255,0,0);
drawcircle(renderer);
while (program_lunch)
{


/*-------------------------------------------------------------------*/
// traitement des evenement
  SDL_Event event ;
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT :
        printf("Game is over\n");
        program_lunch=SDL_FALSE;
        break;
      case SDL_WINDOWEVENT :
        switch(event.window.event)
        {
          case SDL_WINDOWEVENT_SIZE_CHANGED:
            largeur = event.window.data1;
            hauteur = event.window.data2;
            break ;
          default : break ;
        }
      case SDL_KEYDOWN :
          switch(event.key.keysym.sym)
          {
            case SDLK_z :
              if (racket2.y <= 0)
                break;
              mouveracket(renderer,&racket2,255,255,255,-10);
              continue ;
            case SDLK_s :
              if (racket2.y >= hauteur-racket2.h)
                break;
              mouveracket(renderer,&racket2,255,255,255,10);
              continue ;
            default : continue;
          }
      default :break;
    }
/*-------------------------------------------------------------------*/

  }
/*-------------------------------------------------------------------*/
  //SDL_RenderPresent(renderer); // mettre a jour le renderer x))
/*-------------------------------------------------------------------*/

}



/*-------------------------------------------------------------------*/










if (SDL_RenderClear(renderer) != 0)
{
  SDL_Log("ERREUR : clear renderer >%s\n",SDL_GetError());
  exit(EXIT_FAILURE);
}

/*------------------------------------------*/

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(screen);
SDL_Quit();


  return 0 ;
}


/*------------------------------------------*/
/*------------------------------------------*/

void PrintEror(char *string)
{
  SDL_Log("ERREUR : %s >%s\n",string ,SDL_GetError());
  exit(EXIT_FAILURE);
}
/*------------------------------------------*/
/*------------------------------------------*/

void mouveracket(SDL_Renderer *renderer,SDL_Rect *racket2, int r, int g, int b, int v)
{
  if(SDL_SetRenderDrawColor(renderer, 0,0,0,255)!=0)
    PrintEror("can't change color");
  if(SDL_RenderFillRect(renderer, racket2) != 0)
    PrintEror("cahnt draw racket1");
  racket2->y+=v;
  if(SDL_SetRenderDrawColor(renderer, r,g,b,255)!=0)
    PrintEror("can't change color");
  if(SDL_RenderFillRect(renderer, racket2) != 0)
    PrintEror("cahnt draw racket1");
  SDL_RenderPresent(renderer); // mettre a jour le renderer x))
}

/*------------------------------------------*/
/*------------------------------------------*/

void SDL_FillCirecle(SDL_Renderer *renderer, int ox,int oy, int R, int r, int g , int b)
{
  if(SDL_SetRenderDrawColor(renderer, r,g,b,255)!=0)
    PrintEror("can't change color");
  int x =0;
  int y =R;
  int h ;
  SDL_RenderDrawPoint(renderer, x , y);
  h=1-R;
  while(x<y)
  {
    if (h>0)
    {
      y--;
      h=h + 5 +2*(x-y);
    }
    else
      h=h+2*x+3;
    x++;
    SDL_RenderDrawLine(renderer,ox-x , oy+y, ox+x,oy+y );
    SDL_RenderDrawLine(renderer,ox-(int)round(0.7*(x+y)) , oy+(int)round(0.7*(y-x)),ox+(int)round(0.7*(x+y)),oy+(int)round(0.7*(y-x)));
    SDL_RenderDrawLine(renderer,ox-(int)round(0.7*(x+y)) , oy-(int)round(0.7*(y-x)),
     ox+(int)round(0.7*(x+y)) , oy-(int)round(0.7*(y-x)) );
    SDL_RenderDrawLine(renderer,ox-x , oy-y, ox+x , oy-y );

    SDL_RenderDrawLine(renderer,ox-x , oy+y, ox-x , oy-y );
    SDL_RenderDrawLine(renderer,ox+x , oy+y, ox+x , oy-y );
    SDL_RenderDrawLine(renderer,ox-(int)round(0.7*(x+y)) , oy+(int)round(0.7*(y-x)),ox-(int)round(0.7*(x+y)),oy-(int)round(0.7*(y-x)));
    SDL_RenderDrawLine(renderer,ox+(int)round(0.7*(x+y)) , oy+(int)round(0.7*(y-x)),ox+(int)round(0.7*(x+y)),oy-(int)round(0.7*(y-x)));

    SDL_RenderPresent(renderer); // mettre a jour le renderer x))
  }
}

/*------------------------------------------*/
/*------------------------------------------*/







void mouvepoint(SDL_Renderer *renderer , int largeur, int hauteur, int v , int r, int g, int b)
{
  int R =5 ;
  int x=0;
  int y=0;
  SDL_Rect ball ;
  ball.x=x-15;
  ball.y=y-15;
  ball.w=15;
  ball.h=15;
  SDL_RenderDrawPoint(renderer , x, y );
  SDL_RenderDrawRect(renderer, &ball);
  //SDL_FillCirecle(renderer, x, y, R, r, g,b);
  while((x< largeur) && (y <  hauteur) && (x >=0) && (y >= 0))
  {
    if(SDL_SetRenderDrawColor(renderer, 0,0,0,255)!=0)
      PrintEror("can't change color");
    SDL_RenderDrawPoint(renderer , x, y );
    //SDL_FillCirecle(renderer, x, y, R, 0, 0,0);
    SDL_RenderDrawRect(renderer, &ball);


    x=x+v;
    y=y+v;
    ball.x=x;
    ball.y=y;
    if(SDL_SetRenderDrawColor(renderer, r,g,b,255)!=0)
      PrintEror("can't change color");
    SDL_RenderDrawPoint(renderer , x, y );
    //SDL_FillCirecle(renderer, x, y, R, r, g,b);
    SDL_RenderDrawRect(renderer, &ball);

    SDL_RenderPresent(renderer);
  }
}



void drawcircle(SDL_Renderer *renderer)
{
  SDL_Surface *image =NULL;
  SDL_Texture *texture =NULL;

  image = SDL_LoadBMP("src/me.bmp");
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

  rect.x=0;
  rect.y=0;


  if (SDL_RenderCopy(renderer,texture,NULL,&rect)!=0)
  {
    printf("yekhaw ad matjmm taml chy");
  }
  rect.x=100;
  rect.y=100;
  SDL_RenderPresent(renderer);
}
