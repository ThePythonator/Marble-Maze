#include "Level.hpp"

namespace MarbleMaze {
	Level::Level() {

	}

	Level::Level(blit::TMX level_data) {
		//PhysicsEngine::Material* material_ptr = new PhysicsEngine::Material(static_friction, dynamic_friction, restitution, density);
		PhysicsEngine::Material* material_ptr = new PhysicsEngine::Material(0.5f, 0.5f, 0.5f, 1.0f);
		physics_data.materials.push_back(material_ptr);

		// Create ball
		PhysicsEngine::phyvec ball_centre; // get from tiled map

		PhysicsEngine::Circle* ball_shape_ptr = new PhysicsEngine::Circle(Constants::SPRITE_SIZE / 2);
		physics_data.shapes.push_back(ball_shape_ptr);
		ball_ptr = new PhysicsEngine::RigidBody(ball_shape_ptr, material_ptr, ball_centre);

		physics.add_body(ball_ptr);

		// TODO
	}

	void Level::update(float dt) {
		PhysicsEngine::phyvec force(blit::tilt.x, blit::tilt.y); // there's also tilt.z - not sure what to use?

		force *= Constants::TILT_FORCE;

		ball_ptr->apply_force(force);

		physics.update(dt);
	}

	void Level::render(blit::Surface* screen) {

	}
}