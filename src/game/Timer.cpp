#include "Timer.hpp"

namespace MarbleMaze {
	namespace Utilities {
		Timer::Timer() {

		}

		Timer::Timer(float loop_time) {
			_loop_time = loop_time;
		}

		void Timer::update(float dt) {
			if (_running) _time += dt;

			while (_time >= _loop_time) _time -= _loop_time;
		}

		float Timer::time() {
			return _time;
		}

		bool Timer::running() {
			return _running;
		}

		void Timer::start() {
			_running = true;
		}

		void Timer::stop() {
			_running = false;
		}

		void Timer::reset() {
			_time = 0.0f;
		}
	}
}