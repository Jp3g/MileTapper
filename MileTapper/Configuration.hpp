#pragma once

#include "ActionMap.hpp"
#include "ResourceManager.hpp"
#include <SFML\Graphics.hpp>

namespace MileTapper {

	class Configuration
	{
	public:
		Configuration() = delete;
		Configuration(const Configuration&) = delete;
		Configuration& operator=(const Configuration&) = delete;

		//inputs enum for map events
		enum MapInputs {
			MoveUp,
			MoveDown,
			MoveLeft,
			MoveRight,
			ZoomIn,
			ZoomOut,
			MouseWheel,
			MouseLeftClick,
			MouseLeftReleased
		};

		enum Fonts : int {
			GUI
		};

		static ResourceManager<sf::Font, int> fonts;

		static ActionMap<int> defaultMapInputs;
		static ActionMap<int> gui_inputs;
	private:

		static void initEvents();
		static void initFonts();

		static void init();

		static struct __Initiatiser {
			__Initiatiser() {
				Configuration::init();
			};
		} __initiatiser__;
	};
}