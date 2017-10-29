#include "Game.h"

int main()
{
	sf::RenderWindow WindowInstance(sf::VideoMode(1024, 768), "Fallen Forever");
	std::unique_ptr<Game> GameInstance = std::make_unique<Game>(&WindowInstance);

	// This is very slightly wasteful, move entry point of app into Game so we don't 
	// have an extra thread just spinning and yielding. -TODO-
	while (GameInstance->IsActive())
	{
		std::this_thread::yield();
	}

	return 0;
}