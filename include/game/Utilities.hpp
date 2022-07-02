#pragma once

#include <vector>
#include <algorithm>

namespace MarbleMaze {
	namespace Utilities {
		template<typename T>
		bool contains(const std::vector<T>& v, T& item) {
			return std::count(v.begin(), v.end(), item);
		}

		struct Circle {
			float x, y;
			float radius;
		};

		// Returns true if the larger circle is within the smaller
		bool within(const Circle& a, const Circle& b);
	}
}