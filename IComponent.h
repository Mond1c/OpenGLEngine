#pragma once

namespace engine::core {
	class IComponent
	{
	public:
		IComponent() = default;
		virtual ~IComponent() = default;
	public:
		virtual void Update() = 0;
	};
}
