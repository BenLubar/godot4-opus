#include "register_types.h"

#include <gdextension_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "gdopus.h"

using namespace godot;

static const StringName opus_stringname = "Opus";
static Opus *opus_singleton = nullptr;

void initialize_gdopus_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(Opus);
	ClassDB::register_class<Opus>();
	opus_singleton = memnew(Opus);
	Engine::get_singleton()->register_singleton(opus_stringname, opus_singleton);
}

void uninitialize_gdopus_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	Engine::get_singleton()->unregister_singleton(opus_stringname);
	memdelete(opus_singleton);
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT gdopus_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_gdopus_module);
	init_obj.register_terminator(uninitialize_gdopus_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
