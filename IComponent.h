#pragma once

namespace engine {
	class IComponent
	{
	public:
		IComponent() = default;
		virtual ~IComponent() = default;
	public:
		virtual void Update() = 0;
	};
}
