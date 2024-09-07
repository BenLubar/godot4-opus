#include "gdopus.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Opus::_bind_methods() {
	// Methods.
	ClassDB::bind_static_method("Opus", D_METHOD("decode", "data", "audio"), &Opus::decode);
	ClassDB::bind_static_method("Opus", D_METHOD("encode", "audio"), &Opus::encode);
}
