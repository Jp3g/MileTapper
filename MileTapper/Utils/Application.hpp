#pragma once
#include <SFML\Graphics.hpp>

namespace MileTapper {
		
		template<typename ENTITY>
		class Application {
		public:
			Application(const Application&) = delete;
			Application& operator=(const Application&) = delete;

			Application();

			void update(sf::Time deltaTime);

			//EntityManager<ENTITY> entities;
			//SystemManager<ENTITY> systems;
		};

		template<typename ENTITY>
		Application<ENTITY>::Application() /*: system(entities)*/ {

		}

		template<typename ENTITY>
		void Application<ENTITY>::update(sf::Time deltatime) {
			/*	systems.updateAll(deltaTime);
				entities.update();
				*/
		}
	
}