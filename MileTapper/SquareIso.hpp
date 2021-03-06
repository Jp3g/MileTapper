#pragma once

#include <SFML\Graphics.hpp>

namespace MileTapper {

		struct SquareIso {
		public:
			static const sf::ConvexShape& getShape();
			static const sf::ConvexShape& getBox();
			static sf::Vector2f mapCoordsToPixel(int x, int y, float scale);
			static sf::Vector2i mapPixelToCoords(float x, float y, float scale);
			static sf::IntRect getTextureRect(int x, int y, float scale);
			static sf::Vector2i round(float x, float y);
			static int distance(int x1, int y1, int x2, int y2);

		private:
			static sf::ConvexShape _box;
			static sf::ConvexShape _shape;
			static void init();

			static struct __Initiatiser {
				__Initiatiser() {
					SquareIso::init();
				}; 
			} __initiatiser__;
		};
}