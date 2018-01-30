#pragma once

#include "define.hpp"

#include <memory>
#include <unordered_map>
#include <cassert>
#include <SFML/System.hpp>
namespace MileTapper {

		template<typename ENTITY> class EntityManager;
		template<typename ENTITY> class Entity;

		template<typename ENTITY>
		class VSystem
		{
		public:
			VSystem(const VSystem&) = delete;
			VSystem& operator=(const VSystem&) = delete;

			virtual ~VSystem();

			virtual void update(EntityManager<ENTITY>& entity_manager, const sf::Time& deltaTime) = 0;
		protected:
			VSystem();
			static Family _familyCounter;
		};

		template<typename COMPONENT, typename ENTITY>
		class System : public VSystem<ENTITY>
		{
		public:
			System(const System&) = delete;
			System& operator=(const System&) = delete;

			System();
			virtual ~System();

			static Family family();
		};

#define __ES_INIT_VSYSTEM__(ENTITY) template<> sfutils::es::Family sfutils::es::VSystem<ENTITY>::_familyCounter = 0;

		template<typename ENTITY>
		class SystemManager
		{
		public:
			SystemManager(const SystemManager&) = delete;
			SystemManager& operator=(const SystemManager&) = delete;

			SystemManager(EntityManager<ENTITY>& manager);
			~SystemManager();

			template<typename SYSTEM>
			bool add(std::shared_ptr<SYSTEM> ptr);

			template<typename SYSTEM, typename ... Args>
			bool add(Args&& ... args);

			template<typename SYSTEM>
			bool remove();

			template<typename SYSTEM>
			std::shared_ptr<SYSTEM> system();

			template<typename SYSTEM>
			void update(const sf::Time& deltaTime);

			void updateAll(const sf::Time& deltaTime);


		private:
			EntityManager<ENTITY>& _manager;
			std::unordered_map<Family, std::shared_ptr<VSystem<ENTITY>>> _systems;
		};

		///////////////// Virtual SYSTEM ///////////////
		//
		template<typename ENTITY>
		VSystem<ENTITY>::VSystem()
		{
		}

		template<typename ENTITY>
		VSystem<ENTITY>::~VSystem()
		{
		}
		///////////////// SYSTEM ///////////////
		template<typename COMPONENT, typename ENTITY>
		System<COMPONENT, ENTITY>::System()
		{
		}

		template<typename COMPONENT, typename ENTITY>
		System<COMPONENT, ENTITY>::~System()
		{
		}

		template<typename COMPONENT, typename ENTITY>
		Family System<COMPONENT, ENTITY>::family()
		{
			static Family family = VSystem<ENTITY>::_familyCounter++;
			assert(family < MAX_COMPONENTS);
			return family;
		}

		///////////////// SYSTEM MANAGER ///////////////
		template<typename ENTITY>
		SystemManager<ENTITY>::SystemManager(EntityManager<ENTITY>& manager) : _manager(manager)
		{
		}

		template<typename ENTITY>
		SystemManager<ENTITY>::~SystemManager()
		{
		}

		template<typename ENTITY>
		void SystemManager<ENTITY>::updateAll(const sf::Time& deltaTime)
		{
			for (auto& pair : _systems)
				pair.second->update(_manager, deltaTime);
		}

		template<typename ENTITY>
		template<typename SYSTEM>
		bool SystemManager<ENTITY>::add(std::shared_ptr<SYSTEM> ptr)
		{
			if (_systems.count(SYSTEM::family()) == 0)
			{
				_systems.insert(std::make_pair(SYSTEM::family(), ptr));
				return true;
			}
			return false;
		}

		template<typename ENTITY>
		template<typename SYSTEM, typename ... Args>
		bool SystemManager<ENTITY>::add(Args&& ... args)
		{
			if (_systems.count(SYSTEM::family()) == 0)
			{
				_systems.emplace(SYSTEM::family(), std::shared_ptr<SYSTEM>(new SYSTEM(std::forward<Args>(args)...)));
				return true;
			}
			return false;
		}

		template<typename ENTITY>
		template<typename SYSTEM>
		bool SystemManager<ENTITY>::remove()
		{
			if (_systems.count(SYSTEM::family()) == 0)
				return false;
			_systems.erase(SYSTEM::family());
			return true;
		}

		template<typename ENTITY>
		template<typename SYSTEM>
		inline std::shared_ptr<SYSTEM> SystemManager<ENTITY>::system()
		{
			return std::static_pointer_cast<SYSTEM>(_systems.at(SYSTEM::family()));
		}

		template<typename ENTITY>
		template<typename SYSTEM>
		inline void SystemManager<ENTITY>::update(const sf::Time& deltaTime)
		{
			system<SYSTEM>()->update(_manager, deltaTime);
		}

	}

