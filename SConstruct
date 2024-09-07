#!/usr/bin/env python
import os

env = SConscript("godot-cpp/SConstruct")

libname = "gdopus"
projectdir = "demo"

env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

# alright, we're doing something sneaky here and using the Opus codec directly from its source code.
# not a static library, not a shared library, not some other kind of library.
# it's being compiled as part of this GDExtension directly.
# that means we don't have to set up OS-specific libraries and link to them.
env.Append(CPPPATH=["3rdparty/opusfile/include/", "3rdparty/libopusenc/include/", "3rdparty/opus/include/", "3rdparty/ogg/include/", "3rdparty/opus/celt/", "3rdparty/opus/silk/", "3rdparty/opus/silk/float/", "3rdparty/opus/silk/fixed/", "3rdparty/opus/dnn/"])
opus_sources = ["3rdparty/opusfile/src/info.c", "3rdparty/opusfile/src/internal.c", "3rdparty/opusfile/src/opusfile.c", "3rdparty/opusfile/src/stream.c"]
opus_sources += ["3rdparty/libopusenc/src/ogg_packer.c", "3rdparty/libopusenc/src/opus_header.c", "3rdparty/libopusenc/src/opusenc.c", "3rdparty/libopusenc/src/picture.c", "3rdparty/libopusenc/src/resample.c", "3rdparty/libopusenc/src/unicode_support.c"]
opus_sources += ["3rdparty/opus/src/opus.c", "3rdparty/opus/src/opus_decoder.c", "3rdparty/opus/src/opus_encoder.c", "3rdparty/opus/src/extensions.c", "3rdparty/opus/src/opus_multistream.c", "3rdparty/opus/src/opus_multistream_encoder.c", "3rdparty/opus/src/opus_multistream_decoder.c", "3rdparty/opus/src/repacketizer.c", "3rdparty/opus/src/opus_projection_encoder.c", "3rdparty/opus/src/opus_projection_decoder.c", "3rdparty/opus/src/mapping_matrix.c", "3rdparty/opus/src/analysis.c", "3rdparty/opus/src/mlp.c", "3rdparty/opus/src/mlp_data.c"]
opus_sources += ["3rdparty/ogg/src/bitwise.c", "3rdparty/ogg/src/framing.c"]
opus_sources += ["3rdparty/opus/celt/bands.c", "3rdparty/opus/celt/celt.c", "3rdparty/opus/celt/celt_encoder.c", "3rdparty/opus/celt/celt_decoder.c", "3rdparty/opus/celt/cwrs.c", "3rdparty/opus/celt/entcode.c", "3rdparty/opus/celt/entdec.c", "3rdparty/opus/celt/entenc.c", "3rdparty/opus/celt/kiss_fft.c", "3rdparty/opus/celt/laplace.c", "3rdparty/opus/celt/mathops.c", "3rdparty/opus/celt/mdct.c", "3rdparty/opus/celt/modes.c", "3rdparty/opus/celt/pitch.c", "3rdparty/opus/celt/celt_lpc.c", "3rdparty/opus/celt/quant_bands.c", "3rdparty/opus/celt/rate.c", "3rdparty/opus/celt/vq.c"]
opus_sources += ["3rdparty/opus/silk/CNG.c", "3rdparty/opus/silk/code_signs.c", "3rdparty/opus/silk/init_decoder.c", "3rdparty/opus/silk/decode_core.c", "3rdparty/opus/silk/decode_frame.c", "3rdparty/opus/silk/decode_parameters.c", "3rdparty/opus/silk/decode_indices.c", "3rdparty/opus/silk/decode_pulses.c", "3rdparty/opus/silk/decoder_set_fs.c", "3rdparty/opus/silk/dec_API.c", "3rdparty/opus/silk/enc_API.c", "3rdparty/opus/silk/encode_indices.c", "3rdparty/opus/silk/encode_pulses.c", "3rdparty/opus/silk/gain_quant.c", "3rdparty/opus/silk/interpolate.c", "3rdparty/opus/silk/LP_variable_cutoff.c", "3rdparty/opus/silk/NLSF_decode.c", "3rdparty/opus/silk/NSQ.c", "3rdparty/opus/silk/NSQ_del_dec.c", "3rdparty/opus/silk/PLC.c", "3rdparty/opus/silk/shell_coder.c", "3rdparty/opus/silk/tables_gain.c", "3rdparty/opus/silk/tables_LTP.c", "3rdparty/opus/silk/tables_NLSF_CB_NB_MB.c", "3rdparty/opus/silk/tables_NLSF_CB_WB.c", "3rdparty/opus/silk/tables_other.c", "3rdparty/opus/silk/tables_pitch_lag.c", "3rdparty/opus/silk/tables_pulses_per_block.c", "3rdparty/opus/silk/VAD.c", "3rdparty/opus/silk/control_audio_bandwidth.c", "3rdparty/opus/silk/quant_LTP_gains.c", "3rdparty/opus/silk/VQ_WMat_EC.c", "3rdparty/opus/silk/HP_variable_cutoff.c", "3rdparty/opus/silk/NLSF_encode.c", "3rdparty/opus/silk/NLSF_VQ.c", "3rdparty/opus/silk/NLSF_unpack.c", "3rdparty/opus/silk/NLSF_del_dec_quant.c", "3rdparty/opus/silk/process_NLSFs.c", "3rdparty/opus/silk/stereo_LR_to_MS.c", "3rdparty/opus/silk/stereo_MS_to_LR.c", "3rdparty/opus/silk/check_control_input.c", "3rdparty/opus/silk/control_SNR.c", "3rdparty/opus/silk/init_encoder.c", "3rdparty/opus/silk/control_codec.c", "3rdparty/opus/silk/A2NLSF.c", "3rdparty/opus/silk/ana_filt_bank_1.c", "3rdparty/opus/silk/biquad_alt.c", "3rdparty/opus/silk/bwexpander_32.c", "3rdparty/opus/silk/bwexpander.c", "3rdparty/opus/silk/debug.c", "3rdparty/opus/silk/decode_pitch.c", "3rdparty/opus/silk/inner_prod_aligned.c", "3rdparty/opus/silk/lin2log.c", "3rdparty/opus/silk/log2lin.c", "3rdparty/opus/silk/LPC_analysis_filter.c", "3rdparty/opus/silk/LPC_inv_pred_gain.c", "3rdparty/opus/silk/table_LSF_cos.c", "3rdparty/opus/silk/NLSF2A.c", "3rdparty/opus/silk/NLSF_stabilize.c", "3rdparty/opus/silk/NLSF_VQ_weights_laroia.c", "3rdparty/opus/silk/pitch_est_tables.c", "3rdparty/opus/silk/resampler.c", "3rdparty/opus/silk/resampler_down2_3.c", "3rdparty/opus/silk/resampler_down2.c", "3rdparty/opus/silk/resampler_private_AR2.c", "3rdparty/opus/silk/resampler_private_down_FIR.c", "3rdparty/opus/silk/resampler_private_IIR_FIR.c", "3rdparty/opus/silk/resampler_private_up2_HQ.c", "3rdparty/opus/silk/resampler_rom.c", "3rdparty/opus/silk/sigm_Q15.c", "3rdparty/opus/silk/sort.c", "3rdparty/opus/silk/sum_sqr_shift.c", "3rdparty/opus/silk/stereo_decode_pred.c", "3rdparty/opus/silk/stereo_encode_pred.c", "3rdparty/opus/silk/stereo_find_predictor.c", "3rdparty/opus/silk/stereo_quant_pred.c", "3rdparty/opus/silk/LPC_fit.c", "3rdparty/opus/silk/float/apply_sine_window_FLP.c", "3rdparty/opus/silk/float/corrMatrix_FLP.c", "3rdparty/opus/silk/float/encode_frame_FLP.c", "3rdparty/opus/silk/float/find_LPC_FLP.c", "3rdparty/opus/silk/float/find_LTP_FLP.c", "3rdparty/opus/silk/float/find_pitch_lags_FLP.c", "3rdparty/opus/silk/float/find_pred_coefs_FLP.c", "3rdparty/opus/silk/float/LPC_analysis_filter_FLP.c", "3rdparty/opus/silk/float/LTP_analysis_filter_FLP.c", "3rdparty/opus/silk/float/LTP_scale_ctrl_FLP.c", "3rdparty/opus/silk/float/noise_shape_analysis_FLP.c", "3rdparty/opus/silk/float/process_gains_FLP.c", "3rdparty/opus/silk/float/regularize_correlations_FLP.c", "3rdparty/opus/silk/float/residual_energy_FLP.c", "3rdparty/opus/silk/float/warped_autocorrelation_FLP.c", "3rdparty/opus/silk/float/wrappers_FLP.c", "3rdparty/opus/silk/float/autocorrelation_FLP.c", "3rdparty/opus/silk/float/burg_modified_FLP.c", "3rdparty/opus/silk/float/bwexpander_FLP.c", "3rdparty/opus/silk/float/energy_FLP.c", "3rdparty/opus/silk/float/inner_product_FLP.c", "3rdparty/opus/silk/float/k2a_FLP.c", "3rdparty/opus/silk/float/LPC_inv_pred_gain_FLP.c", "3rdparty/opus/silk/float/pitch_analysis_core_FLP.c", "3rdparty/opus/silk/float/scale_copy_vector_FLP.c", "3rdparty/opus/silk/float/scale_vector_FLP.c", "3rdparty/opus/silk/float/schur_FLP.c", "3rdparty/opus/silk/float/sort_FLP.c"]
# some defines to make Opus less upset that we're building it from source in a way it doesn't expect.
for f in opus_sources:
	env.SharedObject(f + '.o', source=f, CPPDEFINES=["OUTSIDE_SPEEX", "RANDOM_PREFIX=gdopus", "PACKAGE_NAME=\\\"\\\"", "PACKAGE_VERSION=\\\"\\\"", "OPUS_BUILD", "USE_ALLOCA", "HAVE_LRINT", "HAVE_LRINTF"])

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

file = "{}{}{}".format(libname, env["suffix"], env["SHLIBSUFFIX"])

if env["platform"] == "macos" or env["platform"] == "ios":
    platlibname = "{}.{}.{}".format(libname, env["platform"], env["target"])
    file = "{}.framework/{}".format(env["platform"], platlibname, platlibname)

libraryfile = "bin/{}/{}".format(env["platform"], file)
library = env.SharedLibrary(
    libraryfile,
    source=sources + [f + '.o' for f in opus_sources],
)

copy = env.InstallAs("{}/bin/{}/lib{}".format(projectdir, env["platform"], file), library)

Default(library, copy)
