#pragma once

#include "runtime/HStackframe.hxx"
#include <cstdint>
#include <vector>

namespace Hyve::Runtime {
	class HStacktrace {
	public:
		using iterator = std::vector<HStackframe>::iterator;
		using const_iterator = std::vector<HStackframe>::const_iterator;

		HStacktrace();
		iterator begin() { return _frames.begin(); }
		iterator end() { return _frames.end(); }
		const_iterator begin() const { return _frames.begin(); }
		const_iterator end() const { return _frames.end(); }

	private:
		std::vector<HStackframe> _frames;
	};
}