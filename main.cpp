#include <iostream>
#include <sdl2/SDL_log.h>
#include <sdl2/SDL.h>

#include "Game.h"

int main(int argc, char *argv[])
{
    const std::unique_ptr<game> app(new game());
    if (app->init())
    {
        SDL_Log("Init OK");
    	app->run();
    }
    else
    {
	    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "FAILED TO CREATE APP.");
        return -1;
    }

    return 0;
}
