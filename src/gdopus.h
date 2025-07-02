#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/classes/audio_stream_wav.hpp>

class Opus : public godot::Object {
	GDCLASS(Opus, godot::Object);

protected:
	static void _bind_methods();

public:
	static Opus *_singleton;

	godot::Error decode(const godot::PackedByteArray &p_data, const godot::Ref<godot::AudioStreamWAV> &p_audio) const;
	godot::PackedByteArray encode(const godot::Ref<godot::AudioStreamWAV> &p_audio) const;
};

void initialize_gdopus_module(godot::ModuleInitializationLevel p_level);
void uninitialize_gdopus_module(godot::ModuleInitializationLevel p_level);
