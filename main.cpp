#include <iostream>
#include <sdl2/SDL_log.h>
#include <sdl2/SDL.h>

#include "game.h"

int main(int argc, char *argv[])
{
    const std::unique_ptr<game> app(new game());
    if (app->init())
    {
        SDL_Log("Init OK");
        if (app->start())
        {
            SDL_Log("Start OK");
        	app->run();
        }
    }
    else
    {
	    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "FAILED TO START APP.");
        return -1;
    }

    return 0;
}
