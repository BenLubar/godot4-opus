#include "gdopus.h"

#include "opusenc.h"

using namespace godot;

static int write_opus(void *user_data, const unsigned char *ptr, opus_int32 len) {
	PackedByteArray *buf = static_cast<PackedByteArray *>(user_data);

	int64_t current_length = buf->size();
	buf->resize(current_length + len);

	memcpy(buf->ptrw() + current_length, ptr, len);

	return 0;
}
static int close_opus(void *user_data) {
	return 0;
}

const static OpusEncCallbacks callbacks = {
	&write_opus,
	&close_opus,
};

PackedByteArray Opus::encode(AudioStreamWAV *audio) {
	ERR_FAIL_NULL_V(audio, PackedByteArray());
	ERR_FAIL_COND_V_MSG(audio->get_format() != AudioStreamWAV::FORMAT_8_BITS && audio->get_format() != AudioStreamWAV::FORMAT_16_BITS, PackedByteArray(), "Opus.encode can only handle FORMAT_8_BITS and FORMAT_16_BITS.");

	PackedByteArray input = audio->get_data();
	PackedByteArray auxiliary;
	PackedByteArray *pinput;

	// opus wants 16-bit signed PCM ([-32768,32767] range, channels interleaved)
	// we only support two of Godot's formats: signed 8 and signed 16.
	if (audio->get_format() == AudioStreamWAV::FORMAT_8_BITS) {
		auxiliary.resize(input.size() * 2);
		// easy way to rescale 8 to 16 bit: just repeat every byte.
		for (int64_t i = 0; i < input.size(); i++) {
			auxiliary[i * 2] = input[i];
			auxiliary[i * 2 + 1] = input[i];
		}
		pinput = &auxiliary;
	} else {
		pinput = &input;
	}

	PackedByteArray buf;
	OggOpusComments *comment = ope_comments_create();
	OggOpusEnc *encoder = ope_encoder_create_callbacks(&callbacks, &buf, comment, audio->get_mix_rate(), audio->is_stereo() ? 2 : 1, 0, nullptr);
	ERR_FAIL_COND_V_MSG(!encoder, PackedByteArray(), "Failed to create Opus encoder.");
	ope_encoder_write(encoder, reinterpret_cast<const opus_int16 *>(pinput->ptr()), pinput->size() / (audio->is_stereo() ? 4 : 2));
	ope_encoder_drain(encoder);
	ope_encoder_destroy(encoder);
	ope_comments_destroy(comment);

	return buf;
}
