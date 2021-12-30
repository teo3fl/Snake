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
        Game::close();
        std::cout << e.what();
        std::cout << "\nForce closing. ";
        system("pause");
    }

    return 0;
}