#include "Editor.hpp"
#include "VLayout.hpp"
#include "HLayout.hpp"
#include "TextButton.hpp"

namespace MileTapper {

	Editor::Editor(sf::RenderWindow& window) :
		_map(MileTapper::VMap::createMapFromFile("media/map.json")),
		_viewer(window, *_map /*Configuration::mapInputs*/), 
		_menuBar(window){
		_viewer.setPosition(0, 0);
		initGui();
	}

	Editor::~Editor(){
		delete _map;
	}

	void Editor::update(sf::Time deltaTime) {
		_viewer.update(deltaTime);

		//sf::Listener::setPosition(pos.x, pos.x, _viewer.getZoom());	<-- ?
	}

	void Editor::processEvents() {
		_viewer.processEvents();
		_menuBar.processEvents();
	}

	bool Editor::processEvent(sf::Event& event) {
		bool res = _viewer.processEvent(event);

		if(!res)
			res =_menuBar.processEvent(event);
		/*
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i coord = _viewer.mapScreenToCoords(event.mouseMove.x, event.mouseMove.y);
				sf::Vector2f pos = _viewer.mapCoordsToPixel(coord.x, coord.y);
				_mouse_light->setPosition(pos);
			}
		*/
		return res;
	}

	void Editor::draw(sf::RenderWindow& window) { //Les objet peuvent prendre leur propre _window
		_viewer.draw();
		_menuBar.draw();
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
		_menuBar.addButton(button2);
		_menuBar.addButton(button3);
		
	}
}