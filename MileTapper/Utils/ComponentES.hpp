#pragma once

#include <cstdint>
#include <cassert>
namespace MileTapper {

		template<typename ENTITY> class EntityManager;
		template<typename COMPONENT, typename ENTITY> class Component;

		template<typename COMPONENT, typename ENTITY>
		class ComponentHandle
		{
		public:
			ComponentHandle(const ComponentHandle&) = default;
			ComponentHandle& operator=(const ComponentHandle&) = default;

			ComponentHandle();

			bool isValid()const;

			COMPONENT* get();
			const COMPONENT* get()const;

			COMPONENT* operator->();
			const COMPONENT* operator->()const;

		private:
			friend class EntityManager<ENTITY>;

			ComponentHandle(const EntityManager<ENTITY>* manager, std::uint32_t entity_id);

			const EntityManager<ENTITY>* _manager;
			std::uint32_t _entityId;
		};


		template<typename ENTITY>
		class VComponent
		{
		public:
			virtual ~VComponent();

			std::uint32_t ownerId()const;

		protected:
			friend class EntityManager<ENTITY>;

			VComponent();

			EntityManager<ENTITY>* _manager;
			std::uint32_t _ownerId;

			static Family _familyCounter;
		};

		#define __ES_INIT_VCOMPONENT__(ENTITY) template<> sfutils::es::Family sfutils::es::VComponent<ENTITY>::_familyCounter = 0;

		template<typename COMPONENT, typename ENTITY>
		class Component : public VComponent<ENTITY>
		{
		public:
			Component(const Component&) = delete;
			Component& operator=(const Component&) = delete;

			Component();
			virtual ~Component();

			void remove();
			static Family family();

			typedef ComponentHandle<COMPONENT, ENTITY> Handle;
		};



		//////////////// COMPONENT HANDLE ///////////////

		template<typename COMPONENT, typename ENTITY>
		inline bool ComponentHandle<COMPONENT, ENTITY>::isValid()const
		{
			return _manager and _manager->isValid(_entityId) and _manager->template hasComponent<COMPONENT>(_entityId);
		}

		template<typename COMPONENT, typename ENTITY>
		ComponentHandle<COMPONENT, ENTITY>::ComponentHandle() : _manager(nullptr), _entityId(-1)
		{
		}

		template<typename COMPONENT, typename ENTITY>
		ComponentHandle<COMPONENT, ENTITY>::ComponentHandle(const EntityManager<ENTITY>* manager, std::uint32_t entity_id) : _manager(manager), _entityId(entity_id)
		{
		}

		template<typename COMPONENT, typename ENTITY>
		inline COMPONENT* ComponentHandle<COMPONENT, ENTITY>::get()
		{
			assert(isValid());
			return _manager->template getComponentPtr<COMPONENT>(_entityId);
		}

		template<typename COMPONENT, typename ENTITY>
		inline const COMPONENT* ComponentHandle<COMPONENT, ENTITY>::get()const
		{
			assert(isValid());
			return _manager->template getComponentPtr<COMPONENT>(_entityId);
		}

		template<typename COMPONENT, typename ENTITY>
		inline COMPONENT* ComponentHandle<COMPONENT, ENTITY>::operator->()
		{
			assert(isValid());
			return _manager->template getComponentPtr<COMPONENT>(_entityId);
		}

		template<typename COMPONENT, typename ENTITY>
		inline const COMPONENT* ComponentHandle<COMPONENT, ENTITY>::operator->()const
		{
			assert(isValid());
			return _manager->template getComponentPtr<COMPONENT>(_entityId);
		}

		////////////////// COMPONENT //////////////////

		template<typename ENTITY>
		VComponent<ENTITY>::VComponent() : _manager(nullptr), _ownerId(-1)
		{
		}

		template<typename ENTITY>
		VComponent<ENTITY>::~VComponent()
		{
		}

		template<typename ENTITY>
		std::uint32_t VComponent<ENTITY>::ownerId()const
		{
			return _ownerId;
		}


		////////////////// COMPONENT //////////////////
		template<typename COMPONENT, typename ENTITY>
		Component<COMPONENT, ENTITY>::Component()
		{
		}

		template<typename COMPONENT, typename ENTITY>
		Component<COMPONENT, ENTITY>::~Component()
		{
		}

		template<typename COMPONENT, typename ENTITY>
		inline void Component<COMPONENT, ENTITY>::remove()
		{
			VComponent<ENTITY>::_manager->template removeComponent<COMPONENT>(VComponent<ENTITY>::_ownerId);
		}


		template<typename COMPONENT, typename ENTITY>
		Family Component<COMPONENT, ENTITY>::family()
		{
			static Family family = VComponent<ENTITY>::_familyCounter++;
			assert(family < MAX_COMPONENTS);
			return family;
	}
}


