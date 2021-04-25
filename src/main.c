#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>


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


/*------------------------------------------*/

  if(SDL_CreateWindowAndRenderer(800,600,0,&screen,&renderer)!=0)
  {
    SDL_Log("ERREUR : can't make window nd renderer >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }
  /*------------------------------------------*/
  /*------------------------------------------*/




  /*------------------------------------------*/

  SDL_bool program_lunch=SDL_TRUE ;

  while (program_lunch ==SDL_TRUE)
  {
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_KEYDOWN :
          switch(event.key.keysym.sym)
          {
            case SDLK_KP_ENTER:

                printf("yeah baby we clicking Enter\n ");
                continue;

            case SDLK_0:
                printf("yeah baby we clicking 0\n ");
                continue;
            default :
              continue;
          }

        case (SDL_QUIT):
            {program_lunch =SDL_FALSE;
            break;}

        default : break;
      }
    }
  }












  /*------------------------------------------*/

  /*------------------------------------------*/

  /*------------------------------------------*/

  /*------------------------------------------*/

  SDL_RenderPresent(renderer); // mettre a jour le renderer x))


/*------------------------------------------*/



  if (SDL_RenderClear(renderer) != 0)
  {
    SDL_Log("ERREUR : clear renderer >%s\n",SDL_GetError());
    exit(EXIT_FAILURE);
  }

  /*------------------------------------------*/

  //SDL_DestroyRenderer(renderer);
  //SDL_DestroyWindow(screen);
  //SDL_Quit();

  return 0 ; //0 ;
}


//gcc src/pingpong.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
