#include "gdopus.h"

#include "opusfile.h"

using namespace godot;

// The libopusfile documentation recommends a 120ms buffer size for 48KHz data.
constexpr int samples_per_buffer = 120 * 48 * 2;

Error Opus::decode(const PackedByteArray &data, AudioStreamWAV *audio) {
	ERR_FAIL_NULL_V(audio, ERR_INVALID_PARAMETER);

	int opus_error = 0;
	OggOpusFile *file = op_open_memory(data.ptr(), data.size(), &opus_error);
	ERR_FAIL_COND_V_MSG(!file, ERR_FILE_CORRUPT, vformat("Cannot parse Opus data. (op_open_memory returned error %d)", opus_error));

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
			op_free(file);

			ERR_FAIL_V_MSG(ERR_FILE_CORRUPT, vformat("Cannot parse Opus data. (%s returned error %d)", is_stereo ? "op_read_stereo" : "op_read", sample_count));
		}

		pcm.append_array(buf.slice(0, sample_count * channel_count * 2));
	}

	op_free(file);

	audio->set_data(pcm);
	audio->set_format(AudioStreamWAV::FORMAT_16_BITS);
	audio->set_loop_begin(0);
	audio->set_loop_end(0);
	audio->set_loop_mode(AudioStreamWAV::LOOP_DISABLED);
	audio->set_mix_rate(48000);
	audio->set_stereo(is_stereo);

	return OK;
}
