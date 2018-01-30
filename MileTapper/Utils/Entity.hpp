#include "define.hpp"

#include "EntityManager.hpp"
#include "System.hpp"
#include "Component.hpp"

#include <cstdint>
#include <tuple>
namespace MileTapper {



		template<typename ENTITY> class EntityManager;
		template<typename COMPONENT, typename ENTITY> class Component;
		template<typename COMPONENT, typename ENTITY> class ComponentHandle;

		template<typename ENTITY>
		class Entity
		{
		public:
			Entity(Entity&&) = default;
			Entity& operator=(Entity&&) = default;

			Entity(EntityManager<ENTITY>* manager, std::uint32_t id);
			~Entity();

			std::uint32_t id()const;
			EntityManager<ENTITY>& getManager();

			bool operator==(const Entity& other)const;
			bool operator!=(const Entity& other)const;

			void remove();

			template<typename COMPONENT, typename ... Args>
			void add(Args&& ... args);

			template<typename COMPONENT>
			void remove();

			template<typename COMPONENT>
			bool has()const;

			template<typename COMPONENT>
			ComponentHandle<COMPONENT, ENTITY> component()const;

			template<typename ... COMPONENT>
			std::tuple<ComponentHandle<COMPONENT, ENTITY>...> components()const;


		private:
			std::uint32_t _id;
			EntityManager<ENTITY>* _manager;
		};

#define ES_INIT_ENTITY(ENTITY) __ES_INIT_VCOMPONENT__(ENTITY);__ES_INIT_VSYSTEM__(ENTITY);

		class DefaultEntity : public Entity<DefaultEntity>
		{
		public:
			using Entity<DefaultEntity>::Entity;

		};


		template<typename ENTITY>
		Entity<ENTITY>::Entity(EntityManager<ENTITY>* manager, std::uint32_t id) : _id(id), _manager(manager)
		{
		}

		template<typename ENTITY>
		Entity<ENTITY>::~Entity()
		{
		}

		template<typename ENTITY>
		inline std::uint32_t Entity<ENTITY>::id()const
		{
			return _id;
		}

		template<typename ENTITY>
		inline EntityManager<ENTITY>& Entity<ENTITY>::getManager()
		{
			return *_manager;
		}

		template<typename ENTITY>
		bool Entity<ENTITY>::operator==(const Entity<ENTITY>& other)const
		{
			return _id == other._id and _manager == other._manager;
		}

		template<typename ENTITY>
		bool Entity<ENTITY>::operator!=(const Entity<ENTITY>& other)const
		{
			return _id != other._id or _manager != other._manager;
		}

		template<typename ENTITY>
		inline void Entity<ENTITY>::remove()
		{
			_manager->remove(_id);
		}

		template<typename ENTITY>
		template<typename COMPONENT, typename ... Args>
		inline void Entity<ENTITY>::add(Args&& ... args)
		{
			_manager->template addComponent<COMPONENT>(_id, std::forward<Args>(args)...);
		}

		template<typename ENTITY>
		template<typename COMPONENT>
		inline void Entity<ENTITY>::remove()
		{
			_manager->template removeComponent<COMPONENT>(_id);
		}

		template<typename ENTITY>
		template<typename COMPONENT>
		inline bool Entity<ENTITY>::has()const
		{
			return _manager->template hasComponent<COMPONENT>(_id);
		}

		template<typename ENTITY>
		template<typename COMPONENT>
		inline ComponentHandle<COMPONENT, ENTITY> Entity<ENTITY>::component()const
		{
			return _manager->template getComponent<COMPONENT>(_id);
		}

		template<typename ENTITY>
		template<typename ... COMPONENT>
		inline std::tuple<ComponentHandle<COMPONENT, ENTITY>...> Entity<ENTITY>::components()const
		{
			return _manager->template getComponents<COMPONENT ...>(_id);
		}

	}

