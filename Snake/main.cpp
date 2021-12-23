#include "stdafx.h"
#include "Game.h"

int main()
{
    try
    {
        Game::start();
    }
    catch(std::runtime_error e)
    {
        std::cout << e.what();
    }

    return 0;
}