#ifndef GDOPUS_CLASS_H
#define GDOPUS_CLASS_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/classes/audio_stream_wav.hpp>

using namespace godot;

class Opus : public Object {
	GDCLASS(Opus, Object);

protected:
	static void _bind_methods();

public:
	static Opus *_singleton;

	Error decode(const PackedByteArray &p_data, AudioStreamWAV *p_audio) const;
	PackedByteArray encode(AudioStreamWAV *p_audio) const;
};


#endif // GDOPUS_CLASS_H
