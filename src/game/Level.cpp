#include "Level.hpp"

namespace MarbleMaze {
	Level::Level() {

	}

	Level::Level(const uint8_t level_data[]) {
		//PhysicsEngine::Material* material_ptr = new PhysicsEngine::Material(static_friction, dynamic_friction, restitution, density);
		PhysicsEngine::Material* material_ptr = new PhysicsEngine::Material(0.5f, 0.5f, 0.5f, 1.0f);

		PhysicsEngine::phyvec ball_centre, finish_centre;

		PhysicsEngine::Circle* ball_shape_ptr = new PhysicsEngine::Circle(Constants::SPRITE_SIZE / 2);
		PhysicsEngine::Circle* finish_shape_ptr = new PhysicsEngine::Circle(Constants::SPRITE_SIZE);
		PhysicsEngine::Polygon* wall_rect_ptr = PhysicsEngine::create_rect(PhysicsEngine::phyvec(Constants::SPRITE_SIZE));

		blit::TMX* tmx_data = (blit::TMX*)(level_data);

		for (uint8_t y = 0; y < tmx_data->height; y++) {
			for (uint8_t x = 0; x < tmx_data->width; x++) {
				uint8_t tile_id = tmx_data->data[y * tmx_data->width + x];

				if (tile_id != tmx_data->empty_tile) {

					if (Utilities::contains(Constants::Tiles::Start::ALL, tile_id)) {
						// Handle positioning the ball
						if (tile_id == Constants::Tiles::Start::BOTTOM_RIGHT) {
							ball_centre.x = x * Constants::SPRITE_SIZE;
							ball_centre.y = y * Constants::SPRITE_SIZE;
						}
					}
					else if (Utilities::contains(Constants::Tiles::Finish::ALL, tile_id)) {
						// Handle positioning the centre
						if (tile_id == Constants::Tiles::Finish::BOTTOM_RIGHT) {
							finish_centre.x = x * Constants::SPRITE_SIZE;
							finish_centre.y = y * Constants::SPRITE_SIZE;
						}
					}
					else if (Utilities::contains(Constants::Tiles::Walls::ALL, tile_id)) {
						PhysicsEngine::RigidBody* wall_ptr = new PhysicsEngine::RigidBody(wall_rect_ptr, material_ptr, (PhysicsEngine::phyvec(x , y) + 0.5f) * Constants::SPRITE_SIZE, 0.0f, true);
						wall_ptr->ids.push_back(tile_id);
						physics.add_body(wall_ptr);
					}
				}
			}
		}


		// Create ball
		ball_ptr = new PhysicsEngine::RigidBody(ball_shape_ptr, material_ptr, ball_centre);
		ball_ptr->ids.push_back(Constants::Tiles::BALL);
		physics.add_body(ball_ptr);

		// Create finish - note that all the material stuff isn't necessary, and we don't add it to the engine
		finish_ptr = new PhysicsEngine::RigidBody(finish_shape_ptr, material_ptr, finish_centre);
	}

	void Level::update(float dt) {
		//PhysicsEngine::phyvec force(blit::tilt.x, blit::tilt.y); // there's also tilt.z - not sure what to use?
		PhysicsEngine::phyvec force(blit::joystick.x, blit::joystick.y); // there's also tilt.z - not sure what to use?

		force *= Constants::TILT_FORCE;

		force += -ball_ptr->velocity * Constants::DRAG_SCALE;

		ball_ptr->apply_force(force);

		physics.update(dt);
	}

	void Level::render(blit::Surface* screen) {
		// Render finish
		for (uint8_t y = 0; y < 2; y++) {
			for (uint8_t x = 0; x < 2; x++) {
				uint8_t tile_id = Constants::Tiles::Finish::ALL[y * 2 + x];

				screen->sprite(tile_id, blit::Point(finish_ptr->centre.x + (x - 1) * Constants::SPRITE_SIZE, finish_ptr->centre.y + (y - 1) * Constants::SPRITE_SIZE));
			}
		}

		// Render everything else
		for (PhysicsEngine::RigidBody* body_ptr : physics.get_bodies()) {
			screen->sprite(body_ptr->ids[0], blit::Point(body_ptr->centre.x - Constants::SPRITE_SIZE / 2, body_ptr->centre.y - Constants::SPRITE_SIZE / 2));
		}
	}

	bool Level::complete() {
		Utilities::Circle ball, finish;

		ball.radius = Constants::SPRITE_SIZE / 2;
		finish.radius = Constants::SPRITE_SIZE;

		ball.x = ball_ptr->centre.x;
		ball.y = ball_ptr->centre.y;

		finish.x = finish_ptr->centre.x;
		finish.y = finish_ptr->centre.y;

		return Utilities::within(ball, finish);
	}
}