#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Fallen Forever");
	Game* mGame = new Game(&window);

	while (mGame->IsActive())
	{
		std::this_thread::yield();
	}

	delete(mGame);

	return 0;
}