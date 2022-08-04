#pragma once
#include "IComponent.h"

namespace engine::core {
	class MonoBehaviour : public IComponent {
	public:
		MonoBehaviour() {
			Start();
		}
		virtual ~MonoBehaviour() = default;
	public:
		virtual void Start() const = 0;
		virtual void Update() const = 0;
	};
}
