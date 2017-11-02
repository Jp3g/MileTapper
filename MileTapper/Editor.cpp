#include "Editor.hpp"
#include "VLayout.hpp"
#include "HLayout.hpp"
#include "TextButton.hpp"

namespace MileTapper {

	Editor::Editor(int X, int Y) : _window(sf::VideoMode(X, Y), "MileTapper"), _viewer(_window, *_map),
		_menu(_window, sf::Vector2f(200,500)), _menuBar(_window){
		_viewer.setPosition(0, 0);
		initGui();
	}

	Editor::~Editor(){

	}

	void Editor::initGui() {

		VLayout* layout = new VLayout;
		//HLayout* layout = new HLayout;
		layout->setSpace(0);

		//layout->setPosition(0, 0);

		TextButton* button = new TextButton("File");
		button->onClick = [this](const sf::Event&, Button& button) {

		};

		TextButton* button2 = new TextButton("Edit");
		button2->onClick = [this](const sf::Event&, Button& button) {
			//_viewer.setPosition(0, 0);
		};

		TextButton* button3 = new TextButton("Window");
		button3->onClick = [this](const sf::Event&, Button& button) {
			//_viewer.setPosition(0, 0);
		};

		TextButton* button4 = new TextButton("Is it too much long ?");
		button4->onClick = [this](const sf::Event&, Button& button) {
			/*_viewer.setPosition(0, 0);*/
		};

		//layout->add(button);
		//layout->add(button2);
		//layout->add(button3);
		//layout->add(button4);

		//_menu.setPosition(100, 100);
		//_menu.setLayout(layout);

		_menuBar.addButton(button);
		//_menuBar.addButton(button2);
		//_menuBar.addButton(button3);
		
	}

	void Editor::run(int frame_per_second) {
		sf::Clock clock;
		sf::Time timeSinceLastUpdate;
		sf::Time TimePerFrame = sf::seconds(1.f / frame_per_second);

		//_window.resetGLStates();

		while (_window.isOpen()) {

			bool repaint = false;

			sf::Time delta = clock.restart();
			timeSinceLastUpdate += delta;

			if (timeSinceLastUpdate > TimePerFrame) {
				processEvents();
				timeSinceLastUpdate -= TimePerFrame;
				repaint = true;

				update(TimePerFrame);
			}

			if (repaint)
				render();

		}
	}

	void Editor::processEvents() {
		sf::Event event;

		while (_window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				_window.close();
			}

			_viewer.processEvent(event);
			//_menu.processEvent(event);
			_menuBar.processEvent(event);
		}

		_viewer.processEvents();
		//_menu.processEvents();
		_menuBar.processEvents();
	}

	void Editor::update(sf::Time deltaTime) {

		_viewer.update(deltaTime);

	}

	void Editor::render() {

		_window.clear();

		_viewer.draw();
		//_menu.draw();
		_menuBar.draw();

		_window.display();
	}

}