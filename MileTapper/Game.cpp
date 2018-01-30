#include "Game.hpp"
/**/

namespace MileTapper {

	Game::Game(int X, int Y) : 
		_window(sf::VideoMode(X, Y), "MileTapper"), 
		_editor(nullptr) {

	}

	Game::~Game() {
		delete _editor;
	};

	bool Game::load() {
		bool res = false;

		_editor = new Editor(_window);
		if (_editor)
			res = true;

		return res;
	}

	void Game::run(int frame_per_seconds) {
		sf::Clock clock;
		sf::Time timeSinceLastUpdate;
		sf::Time TimePerFrame = sf::seconds(1.f / frame_per_seconds);

		while (_window.isOpen())
		{

			bool repaint = false;

			//fix time delta between frames
			sf::Time delta = clock.restart();
			timeSinceLastUpdate += delta;
			if (timeSinceLastUpdate > TimePerFrame)
			{
				processEvents();
				timeSinceLastUpdate -= TimePerFrame;
				repaint = true;
				update(TimePerFrame);
			}

			if (repaint)
				render();
		}

	}

	void Game::processEvents() {
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
				_window.close();
			/*processEvents
				-Cursor
			*/

			_editor->processEvent(event);
		}
		/*processEvents
			-Cursor
		*/

		_editor->processEvents();
	}

	void Game::update(sf::Time deltaTime) {
		/*Update
			-Cursor
		*/
		_editor->update(deltaTime);
	}

	void Game::render() {
		_window.clear();
		/*Draw
			-Cursor
		*/
		_editor->draw(_window);
		_window.display();
	}
}

