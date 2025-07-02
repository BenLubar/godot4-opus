#include "gdopus.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Opus *Opus::_singleton = nullptr;

void Opus::_bind_methods() {
	ClassDB::bind_method(D_METHOD("decode", "data", "audio"), &Opus::decode);
	ClassDB::bind_method(D_METHOD("encode", "audio"), &Opus::encode);
}
