#include "Game.h"
#include "Message.h"
#include "Messenger.h"

int main()
{
	// Create window instance
	sf::RenderWindow WindowInstance(sf::VideoMode(1024, 768), "Fallen Forever");

	// Set the window inactive so another thread can pick it up.
	WindowInstance.setActive(false);

	// Create an instance of the game here.
	std::unique_ptr<Game> GameInstance = std::make_unique<Game>(&WindowInstance);

	// Create an event holder here for our event polling.
	sf::Event WindowEvent;

	while (GameInstance->IsActive())
	{
		while (WindowInstance.pollEvent(WindowEvent))
		{
			switch (WindowEvent.type)
			{
				case sf::Event::Closed:
					GameInstance->EndGame();
					break;
				case sf::Event::KeyPressed:
					GameInstance->GetMessenger("KeyEvents").get()->ReceiveMessage(std::make_shared<Message>(MESSAGE_TYPE_INPUT, WindowEvent.key.code));
					break;
				case sf::Event::Resized:
					WindowInstance.setSize(sf::Vector2u(WindowEvent.size.width, WindowEvent.size.height));
					break;
			}
		}

		std::this_thread::yield();
	}

	return 0;
}