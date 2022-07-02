#pragma once

#include "32blit.hpp"

#include "PhysicsEngine.hpp"

#include "Utilities.hpp"

#include "Constants.hpp"

namespace MarbleMaze {
	class Level {
	public:
		Level();
		Level(const uint8_t level_data[]);

		void update(float dt);
		void render(blit::Surface* screen);

		bool complete();

	private:
		PhysicsEngine::PhysicsManager physics;
		PhysicsEngine::PhysicsData physics_data;

		PhysicsEngine::RigidBody* ball_ptr = nullptr;

		PhysicsEngine::RigidBody* finish_ptr = nullptr;
	};
}