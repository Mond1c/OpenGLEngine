#pragma once
#include "GameObject.h"
#include <sstream>
#include <vector>
#include <memory>

namespace engine::parser {
	class GameObjectParser
	{
	public:
		GameObjectParser() = delete;
		GameObjectParser(const GameObjectParser&) = delete;
		GameObjectParser(GameObjectParser&&) = delete;
	public:
		GameObjectParser& operator=(const GameObjectParser&) = delete;
		GameObjectParser& operator=(GameObjectParser&&) = delete;
	public:
		static std::shared_ptr<core::GameObject> Parse(std::stringstream& stream);
		static std::vector<std::string> Split(const std::string& str);
	};
}

