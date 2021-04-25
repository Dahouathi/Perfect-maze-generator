#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*-------------------------------------------------------------------*/
//gcc src/pingpongv2.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
/*-------------------------------------------------------------------*/



/*-------------------------------------------------------------------*/
            //things to define <3!
/*-------------------------------------------------------------------*/
const double PI = acos(-1.0) ;
#define V  5
#define UP  0
#define DOWN 1
#define X 4.8



/*-------------------------------------------------------------------*/
            //functions that we may need
/*-------------------------------------------------------------------*/
void PrintEror(char *mot);
SDL_bool ProcessEvents(const Uint8* keys, SDL_Event *event, SDL_Rect * racket1, SDL_Rect * racket2,
 int *state2,int *v2, int *largeur, int *hauteur);
void UpdateObjects(SDL_bool *game_lunch,SDL_Rect * racket1, SDL_Rect * racket2, int *state2, int *v2, SDL_Rect *ball,
int vb, double *teta, int *largeur, int *hauteur );
void Draw(SDL_Renderer *renderer, SDL_Rect * racket1, SDL_Rect * racket2,
SDL_Rect *ball, SDL_Texture *texture );


/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/






/*-------------------------------------------------------------------*/
                         // main progroram
/*-------------------------------------------------------------------*/


int main(int argc , char**argv)
{
  /*-------------------------------------------------------------------*/
                    //initialisation du SDL
  /*-------------------------------------------------------------------*/
  if (SDL_Init(SDL_INIT_EVERYTHING) !=0)
    PrintEror("can't initialise");
  double teta ;
  int vb=3; ///vbmax 25     tete appartien 0, 1.4
  do
     {
       srand(time(NULL)+getpid()); //generate new random everytime
       teta= ((double)rand() /RAND_MAX)*2*PI ;
     }
  while ((int)(vb*cos(teta)) == 0);
  //teta = 0.732306  ;
  teta =0;
  /*-------------------------------------------------------------------*/
                      //creation screan and renderer
  /*-------------------------------------------------------------------*/
  int largeur = 800;
  int hauteur = 600 ;
  SDL_Window *screen =NULL ;
  SDL_Renderer *renderer =NULL;
  screen =SDL_CreateWindow("PingPong Game", SDL_WINDOWPOS_CENTERED,
  SDL_WINDOWPOS_CENTERED, largeur, hauteur,SDL_WINDOW_RESIZABLE);
  if (screen == NULL)
    PrintEror("can't create window");
  renderer = SDL_CreateRenderer(screen, -1,
  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer==NULL)
    PrintEror("can't make renderer");
  //make screen black
  if(SDL_SetRenderDrawColor(renderer, 0,0,0,SDL_ALPHA_OPAQUE)!=0)
    PrintEror("can't change color");
  SDL_RenderClear(renderer);

  /*-------------------------------------------------------------------*/
                      //Create Racket1/2 initialiser au milieux
  /*-------------------------------------------------------------------*/
  SDL_Rect racket1;
  racket1.h=hauteur*2.5/10;
  racket1.w=largeur/100;
  racket1.x=0  ;
  racket1.y=((hauteur-racket1.h)/2);
/*-------------------------------------------------------------------------*/
  SDL_Rect racket2;
  racket2.h=hauteur*2.5/10;
  racket2.w=largeur/100;
  racket2.x= largeur - racket2.w ;
  racket2.y=((hauteur-racket2.h)/2);

  /*-------------------------------------------------------------------*/
                      //Create ball
  /*-------------------------------------------------------------------*/
   SDL_Surface *image =NULL;
   SDL_Texture *texture =NULL;
   SDL_Rect ball ;
   image=SDL_LoadBMP("src/me.bmp");
   if (image == NULL)
    PrintEror("can't load image");
  texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  if(texture == NULL)
    PrintEror("can't load texture");
  ball.x = largeur/2 ;
  ball.y = hauteur/2 ;
  /*-------------------------------------------------------------------*/
                      //Game loop
  /*-------------------------------------------------------------------*/

SDL_bool game_lunch =SDL_TRUE;
int v2 =V;
int state2;
double *k =&teta;
printf("%lf %lf , %lf \n",*k, cos(teta), sin(teta));
const Uint8 *keys= SDL_GetKeyboardState(NULL) ;
while(game_lunch)
{
  SDL_Event event;
  game_lunch = ProcessEvents(keys,&event, &racket1, &racket2, &state2, &v2, &largeur, &hauteur);
  Draw(renderer, &racket1, &racket2,&ball, texture );
  UpdateObjects(&game_lunch, &racket1, &racket2, &state2, &v2, &ball,vb, k ,&largeur,&hauteur );
//  Draw(renderer, &racket1, &racket2,&ball, texture );
  SDL_Delay(1000/60);
}







  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(screen);
  SDL_Quit();

  return 0;
}



/*-------------------------------------------------------------------*/
                //write core of function
/*-------------------------------------------------------------------*/
void PrintEror(char *mot)
{
  SDL_Log("ERREUR : %s >%s\n",mot ,SDL_GetError());
  exit(EXIT_FAILURE);
}


/*----------------------------------------------------------------------------*/

SDL_bool ProcessEvents(const Uint8* keys, SDL_Event *event, SDL_Rect * racket1,SDL_Rect * racket2,
 int *state2, int *v2, int *largeur, int *hauteur)
{
  SDL_bool program_lunch =SDL_TRUE ;
  *state2=1;
  while(SDL_PollEvent(event))
  {
    switch(event->type)
    {
      case SDL_QUIT :
        printf("Game is over\n");
        program_lunch=SDL_FALSE;
        break;

      case SDL_WINDOWEVENT :
        switch(event->window.event)
        {
          case SDL_WINDOWEVENT_SIZE_CHANGED:
            *largeur = event->window.data1;
            *hauteur = event->window.data2;
            break ;
          default : break ;
        }
    /*  case SDL_KEYDOWN :
        switch(event->key.keysym.sym)
        {
          case SDLK_z :
            if((*racket2).y < 0)
              break;
            *state2= 0 ; //UP
            racket2->y-=*v2;
            *v2++;
            break;
          case SDLK_s :
            if ((racket2->y) > *hauteur-racket2->h)
              break;
            *state2=1;
            printf("%s\n","you just did press s" );
            racket2->y+=*v2;
            *v2++;
            break ;
          default :
          {
           *v2=V;
           *state2=-1;
           printf("%s\n","you just didn't press s" );
           break;
          }
        }
      case SDL_KEYUP :
        switch (event->key.keysym.sym)
        {
          case (SDLK_s):
            *state2 = -1;
            printf("%s\n","you just stop press s" );
            break;
          default : break;
        }*/

      default : break ;
    }
  }
  if (keys[SDL_SCANCODE_W])
    {
    if((*racket2).y >= 0)
      {
         *state2= 0 ; //UP
          racket2->y-=*v2;
         *v2+=1;
       }

     }
  else
  {
    *state2=-1;
    if (keys[SDL_SCANCODE_S])
      {
        if ((racket2->y) <= *hauteur-racket2->h)
         {
           *state2=1;
            //printf("%s\n","you just did press s" );
            racket2->y+=*v2;
           *v2+=1;
         }
       }
    else
    {
      *state2=-1;
      *v2=V;
    }
  }
  //printf("%d\n",*state2);

  return program_lunch ;
}


/*----------------------------------------------------------------------------*/

void UpdateObjects(SDL_bool *game_lunch, SDL_Rect * racket1, SDL_Rect * racket2, int *state2, int *v2, SDL_Rect *ball,
int vb, double *teta, int *largeur, int *hauteur )
{

  if (*teta >= 2*acos(-1.0))
    *teta =*teta -2*acos(-1.0); //initialise teta entre 0 et pi
  if (*teta <= -2*acos(-1.0))
    *teta =*teta +2*acos(-1.0);
  int *starting_point ;
  int *standing_point ;
  double alpha ;
  starting_point=malloc(sizeof(int)*2);
  standing_point=malloc(sizeof(int)*2);
  /*---------------*/
    //  regler vitesse  du racket 2
  if ((racket2->y <=0) || (racket2->y+racket2->h >= *hauteur))
    *v2=V;
  /*--------*/
    // this one to update racket2 position if window get bigger !
  /*--------*/
  racket2->h=*hauteur*2.5/10;
  racket2->w=*largeur/100;
  racket2->x= *largeur - racket2->w ;
  //printf("%d\n",*state2 );
  /*--------*/
    // this one to update racket1 position if window get bigger !
  /*--------*/
  racket1->h=*hauteur*2.5/10;
  racket1->w=*largeur/100;


  starting_point[0]=ball->x;
  starting_point[1]=ball->y;
  double a= *teta;
/*  if((ball->y >=0) && (ball->y <= (*hauteur-ball->h)))
  {

    printf("%lf...\n",*teta );                   //ball in
    ball->x+= (int)(vb*cos(*teta));
    ball->y+=(int)(vb*sin(*teta));
  }*/

  if ((ball->x+ball->w +racket2->w <= *largeur) && (ball->x >=0)) //sala7 position racket1
  {
    if (((ball->y + ball->h) >= *hauteur) || (ball->y <= 0))
    {

      starting_point[0]=ball->x;
      starting_point[1]=ball->y;                  // ball out up/down
      *teta = -(*teta);
      printf("%lf normal reflexition\n",*teta );
      ball->x+= (int)(vb*cos(*teta));
      ball->y+=(int)(vb*sin(*teta));

    }
    else
    {
                        //ball in
      ball->x+= (int)(vb*cos(*teta));
      ball->y+=(int)(vb*sin(*teta));
      if ((ball->x+ball->w+racket2->w >= *largeur) && (ball->y+ball->h > racket2->y) //ballx et racketx maso b3a4hom
       && (ball->y < racket2->y+racket2->h))
       {
         //printf("%d\n",racket2->w );
         //printf("%d\n",ball->w);
         //printf("%d\n",ball->x );
         printf("%lf start reflecting\n",*teta );
         standing_point[0]=ball->x;
         standing_point[1]=ball->y;
      /*   alpha= fabs(atan((double)abs(standing_point[1]-starting_point[1])/(double)abs(standing_point[0]-starting_point[0])));
         //free(standing_point);
         //free(starting_point);
         *teta= -(*teta) + acos(-1.0) ;
         printf("%lf\n",*teta );
         if ((*state2)==0)
           *teta+=alpha;
         if ((*state2==1))
           *teta-=alpha;
         ball->x+= (int)(vb*cos(*teta));
         ball->y+=(int)(vb*sin(*teta));
         printf("%lf, %lf \n",*teta,alpha );*/
         if (((*state2)==0) &&(sin(teta>=0)))
            {
              printf("%s\n","1" );
              alpha = -fabs(atan((double)(abs(standing_point[1]-starting_point[1]+*v2))/(double)abs(standing_point[0]-starting_point[0])));
              alpha -=(*teta);
            }
         else
         {
           if ((*state2==1)&&(sin(teta<=0)))
           {
             printf("%s\n","2" );
             alpha = -fabs(atan((double)(abs(standing_point[1]-starting_point[1]+*v2))/(double)abs(standing_point[0]-starting_point[0])));
             alpha -=(*teta);
           }
           else
           {
             if (((*state2)==0) &&(sin(teta<=0)))
             {
               printf("%s\n","3" );
               alpha =fabs(atan((double)(abs(standing_point[1]-starting_point[1]+*v2))/(double)abs(standing_point[0]-starting_point[0])));
               alpha -=(*teta);
             }
             else
              {
                if ((*state2==1)&&(sin(teta>=0)))
                {
                  printf("%s\n","4" );
                  alpha = fabs(atan((double)(abs(standing_point[1]-starting_point[1]+*v2))/(double)abs(standing_point[0]-starting_point[0])));
                  alpha -=(*teta);
                }
                else alpha = 0;
              }

           }
         }

         printf("%lf alpha \n",alpha);
         alpha = (*teta) +X*alpha;
         if (((int)round(vb*cos(-alpha + acos(-1.0))) >= 1) || ((int)round(vb*cos(-alpha + acos(-1.0))) <= -1))
          {
            *teta= -alpha + acos(-1.0);
          }
         else
         {
           *teta= -(*teta) + acos(-1.0);
         }
         printf("%lf after \n",*teta );
         printf("%d\n",*v2 );
         //printf("%d\n",*state2 );
         ball->x+= (int)round(vb*cos(*teta));
         printf("%s\n","ball mchet" );
         ball->y+=(int)round(vb*sin(*teta));

       }
    }
  }
  else
  {
      if ((ball->x+ball->w +racket2->w > *largeur))
          printf("%s\n", "Player 1 Wins" );
      if (ball->x < 0) {
        printf("%s\n", "Player 1 Wins");
      }
      *game_lunch = SDL_FALSE;
    }




}






/*---------------------------------------------------------------------------*/

void Draw(SDL_Renderer *renderer, SDL_Rect * racket1, SDL_Rect * racket2,
SDL_Rect *ball, SDL_Texture *texture )
{
  if(SDL_SetRenderDrawColor(renderer, 0,0,0,255)!=0)
    PrintEror("can't change color");
  SDL_RenderClear(renderer);
  SDL_QueryTexture(texture, NULL, NULL, &ball->w, &ball->h);
  SDL_RenderCopy(renderer,texture,NULL,ball);
  if(SDL_SetRenderDrawColor(renderer, 255,255,255,255)!=0)
    PrintEror("can't change color");
  SDL_RenderFillRect(renderer,racket2);
  if(SDL_SetRenderDrawColor(renderer, 200,200,155,255)!=0)
    PrintEror("can't change color");
  SDL_RenderFillRect(renderer,racket1);
  SDL_RenderPresent(renderer);
}
