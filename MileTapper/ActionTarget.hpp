#pragma once

#include <SFML\Graphics.hpp>
#include <functional>
#include <utility>
#include <list>
#include "ActionMap.hpp"
#include "Action.hpp"

namespace MileTapper {

	template<typename T = int>
	class ActionTarget {
	public:
		ActionTarget(const ActionTarget<T>&) = delete;
		ActionTarget& operator=(const ActionTarget<T>&) = delete;

		using FuncType = std::function<void(const sf::Event&)>;
		ActionTarget(const ActionMap<T>& map);

		bool processEvent(const sf::Event& event) const;
		void processEvents() const;

		void bind(const T& key, const FuncType& callback);
		void bind(const Action& action, const FuncType& callback);
		void bind(Action&& action, const FuncType& callback);
		void unbind(const T& action);

	private:
		std::list<std::pair<T, FuncType>> _eventsRealTime;
		std::list<std::pair<Action, FuncType>> _eventsRealTimeAction; 
		std::list<std::pair<T, FuncType>> _eventsPoll;
		std::list<std::pair<Action, FuncType>> _eventsPollAction;

		const ActionMap<T>& _actionMap;
	};

	template<typename T>
	ActionTarget<T>::ActionTarget(const ActionMap<T>& map) : _actionMap(map)
	{
	}

	template<typename T>
	bool ActionTarget<T>::processEvent(const sf::Event& event)const
	{
		for (auto& pair : _eventsPollAction)
		{
			if (pair.first == event)
			{
				pair.second(event);
				return true;
			}
		}

		for (auto& pair : _eventsPoll)
		{
			if (_actionMap.get(pair.first) == event)
			{
				pair.second(event);
				return true;
			}
		}
		return false;
	}

	template<typename T>
	void ActionTarget<T>::processEvents()const
	{
		for (auto& pair : _eventsRealTimeAction)
		{
			if (pair.first.test())
				pair.second(pair.first._event);
		}

		for (auto& pair : _eventsRealTime)
		{
			const Action& action = _actionMap.get(pair.first);
			if (action.test())
				pair.second(action._event);
		}
	}

	template<typename T>
	void ActionTarget<T>::bind(const T& key, const FuncType& callback)
	{
		const Action& action = _actionMap.get(key);
		bind(_actionMap.get(key), callback);
		if (action._type & Action::Type::RealTime)
			_eventsRealTime.emplace_back(key, callback);
		else
			_eventsPoll.emplace_back(key, callback);
	}

	template<typename T>
	void ActionTarget<T>::bind(const Action& action, const FuncType& callback)
	{
		if (action._type & Action::Type::RealTime)
			_eventsRealTimeAction.emplace_back(action, callback);
		else
			_eventsPollAction.emplace_back(action, callback);
	}

	template<typename T>
	void ActionTarget<T>::bind(Action&& action, const FuncType& callback)
	{
		if (action._type & Action::Type::RealTime)
			_eventsRealTimeAction.emplace_back(std::move(action), callback);
		else
			_eventsPollAction.emplace_back(std::move(action), callback);
	}

	template<typename T>
	void ActionTarget<T>::unbind(const T& key)
	{
		auto remove_func = [&key](const std::pair<T, FuncType>& pair) -> bool
		{
			return pair.first == key;
		};

		const Action& action = _actionMap.get(key);
		if (action._type & Action::Type::RealTime)
			_eventsRealTime.remove_if(remove_func);
		else
			_eventsPoll.remove_if(remove_func);
	}

}