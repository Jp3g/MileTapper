#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

namespace MileTapper {

	template<typename RESOURCE, typename IDENTIFIER = int>
	class ResourceManager {
	public:
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		ResourceManager() = default;

		template<typename ... Args>
		RESOURCE& load(const IDENTIFIER& id, Args&& ... args);

		RESOURCE& get(const IDENTIFIER& id) const;

		template<typename ... Args>
		RESOURCE& getOrLoad(const IDENTIFIER& id, Args&& ... args);

		void clear();
	private:
		std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> _map;
	};

	template<typename RESOURCE, typename IDENTIFIER>
	template<typename ... Args>
	RESOURCE&ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args){
		std::unique_ptr<RESOURCE> ptr(new RESOURCE);
		if (! ptr->loadFromFile(std::forward<Args>(args)...))
			throw std::runtime_error("Impossible to load file");
		if (_map.emplace(id, std::move(ptr)).second == false)
			throw std::runtime_error("Impossible to emplace in map. Object already load?");
		return *_map[id];
	}

	template<typename RESOURCE, typename IDENTIFIER>
	RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id) const {
		return *_map.at(id);
	}

	template<typename RESOURCE, typename IDENTIFIER>
	template<typename ... Args>
	RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::getOrLoad(const IDENTIFIER& id, Args&& ... args)
	{
		if (_map.count(id) == 0)
			return load(id, args...);
		return get(id);
	}

	template<typename RESOURCE, typename IDENTIFIER>
	void ResourceManager<RESOURCE, IDENTIFIER>::clear() {
		_map.clear();
	}

	////Animation
	//template<typename IDENTIFIER>
	//class ResourceManager<Animation, IDENTIFIER>
	//{
	//public:
	//	ResourceManager(const ResourceManager&) = delete;
	//	ResourceManager& operator=(const ResourceManager&) = delete;

	//	ResourceManager() = default;

	//	template<typename ... Args>
	//	Animation& load(const IDENTIFIER& id, Args&& ... args);

	//	bool count(const IDENTIFIER& id)const;

	//	Animation& get(const IDENTIFIER& id)const;

	//	template<typename ... Args>
	//	Animation& getOrLoad(const IDENTIFIER& id, Args&& ... args);

	//	void clear();

	//private:
	//	std::unordered_map<IDENTIFIER, std::unique_ptr<Animation>> _map;
	//};

	//template<typename IDENTIFIER>
	//template<typename ... Args>
	//Animation& ResourceManager<Animation, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
	//{
	//	std::unique_ptr<Animation> ptr(new Animation(std::forward<Args>(args)...));
	//	if (_map.emplace(id, std::move(ptr)).second == false)
	//		throw std::runtime_error("Impossible to emplace in map. Object aleardy load?");
	//	return *_map[id];
	//};

	//template<typename IDENTIFIER>
	//bool ResourceManager<Animation, IDENTIFIER>::count(const IDENTIFIER& id)const
	//{
	//	return _map.count(id);
	//}

	//template<typename IDENTIFIER>
	//Animation& ResourceManager<Animation, IDENTIFIER>::get(const IDENTIFIER& id) const
	//{
	//	return *_map.at(id);
	//}

	//template<typename IDENTIFIER>
	//template<typename ... Args>
	//Animation& ResourceManager<Animation, IDENTIFIER>::getOrLoad(const IDENTIFIER& id, Args&& ... args)
	//{
	//	if (_map.count(id) == 0)
	//		return load(id, args...);
	//	return get(id);
	//}

	//template<typename IDENTIFIER>
	//void ResourceManager<Animation, IDENTIFIER>::clear()
	//{
	//	_map.clear();
	//}
}