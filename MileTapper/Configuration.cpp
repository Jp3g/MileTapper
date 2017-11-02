#include "Configuration.hpp"

namespace MileTapper {

	ResourceManager<sf::Font, int> Configuration::fonts;

	ActionMap<int> Configuration::gui_inputs;
	ActionMap<int> Configuration::defaultMapInputs;

	Configuration::__Initiatiser Configuration::__initiatiser__;

	void Configuration::initEvents()
	{
		defaultMapInputs.map(MapInputs::MoveUp, Action(sf::Keyboard::Up));
		defaultMapInputs.map(MapInputs::MoveDown, Action(sf::Keyboard::Down));
		defaultMapInputs.map(MapInputs::MoveLeft, Action(sf::Keyboard::Left));
		defaultMapInputs.map(MapInputs::MoveRight, Action(sf::Keyboard::Right));
		defaultMapInputs.map(MapInputs::ZoomIn, Action(sf::Keyboard::I));
		defaultMapInputs.map(MapInputs::ZoomOut, Action(sf::Keyboard::O));
		defaultMapInputs.map(MapInputs::MouseWheel, Action(sf::Mouse::VerticalWheel, Action::Type::Scrolled));
		defaultMapInputs.map(MapInputs::MouseLeftClick, Action(sf::Mouse::Left));
		defaultMapInputs.map(MapInputs::MouseLeftReleased, Action(sf::Mouse::Left, Action::Type::Released));
	}

	void Configuration::initFonts() {
		fonts.load(Fonts::GUI, "media/font/default.otf");
	}

	void Configuration::init()
	{
		initEvents();
		initFonts();
	}

}