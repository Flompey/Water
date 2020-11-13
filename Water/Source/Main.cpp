#include "Game.h"
#include "CustomException.h"
#include <optional>

int main()
{
    // Using std::optional in order to defer the construction of game
    std::optional<Game> game;
    try
    {
        game.emplace();
    }
    catch (const CustomException& exception)
    {
        std::cerr << exception.what() << std::endl;
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl;
    }
    
    try
    {
        game->Loop();
    }
    catch (const CustomException& exception)
    {
        std::cerr << exception.what() << std::endl;
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception" << std::endl;
    }

    return 0;
}
