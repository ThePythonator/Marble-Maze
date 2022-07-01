#pragma once

#include "32blit.hpp"

#include "PhysicsEngine.hpp"

#include "Constants.hpp"

namespace MarbleMaze {
	class Level {
	public:
		Level();
		Level(blit::TMX level_data);

		void update(float dt);
		void render(blit::Surface* screen);

	private:
		PhysicsEngine::PhysicsManager physics;
		PhysicsEngine::PhysicsData physics_data;

		PhysicsEngine::RigidBody* ball_ptr = nullptr;
	};
}