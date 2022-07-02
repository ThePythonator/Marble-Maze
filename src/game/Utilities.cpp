#include "Utilities.hpp"

namespace MarbleMaze {
	namespace Utilities {
		bool within(const Circle& a, const Circle& b) {
			const Circle& larger = a.radius > b.radius ? a : b;
			const Circle& smaller = a.radius > b.radius ? b : a;

			float x_difference = a.x - b.x;
			float y_difference = a.y - b.y;

			float squared_distance = x_difference * x_difference + y_difference * y_difference;

			float radii_difference = larger.radius - smaller.radius;

			return squared_distance < radii_difference * radii_difference;
		}
	}
}