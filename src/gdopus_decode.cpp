#include "gdopus.h"

#include "opusfile.h"

using namespace godot;

// The libopusfile documentation recommends a 120ms buffer size for 48KHz data.
constexpr int samples_per_buffer = 120 * 48 * 2;

AudioStreamWAV *Opus::decode(const PackedByteArray &data) {
	OggOpusFile *file = op_open_memory(data.ptr(), data.size(), nullptr);
	if (!file) {
		// TODO: better error handling
		ERR_PRINT("Opus.decode encountered error");

		return nullptr;
	}

	// Since AudioStreamWAV only supports mono or stereo, we need to downmix to stereo if the stream has two or more channels.
	// However, we don't want to *up*mix to stereo if we have a mono audio stream.
	bool is_stereo = op_channel_count(file, -1) > 1;
	int channel_count = is_stereo ? 2 : 1;

	PackedByteArray pcm;
	PackedByteArray buf;
	buf.resize(samples_per_buffer * 2);

	while (int sample_count = is_stereo ?
			op_read_stereo(file, reinterpret_cast<opus_int16 *>(buf.ptrw()), samples_per_buffer) :
			op_read(file, reinterpret_cast<opus_int16 *>(buf.ptrw()), samples_per_buffer, nullptr)) {
		if (sample_count < 0) {
			// TODO: better error handling
			ERR_PRINT("Opus.decode encountered error");

			op_free(file);

			return nullptr;
		}

		pcm.append_array(buf.slice(0, sample_count * channel_count * 2));
	}

	op_free(file);

	AudioStreamWAV *stream = memnew(AudioStreamWAV);
	stream->set_data(pcm);
	stream->set_format(AudioStreamWAV::FORMAT_16_BITS);
	stream->set_mix_rate(48000);
	stream->set_stereo(is_stereo);

	return stream;
}
