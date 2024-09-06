extends Control

var _opus_bytes := FileAccess.get_file_as_bytes("res://wb_male.ogg")
var _wav_stream := preload("res://wb_male.wav")

func _on_play_opus_button_pressed() -> void:
	var player: AudioStreamPlayer = %AudioStreamPlayer
	player.stream = Opus.decode(_opus_bytes)
	player.play()

func _on_play_wav_button_button_pressed() -> void:
	var player: AudioStreamPlayer = %AudioStreamPlayer
	player.stream = _wav_stream
	player.play()

func _on_convert_from_opus_button_pressed() -> void:
	var wav := Opus.decode(_opus_bytes)
	wav.save_to_wav("user://converted_from_opus.wav")
	OS.shell_show_in_file_manager("user://converted_from_opus.wav")

func _on_convert_to_opus_button_pressed() -> void:
	var buf := Opus.encode(_wav_stream)
	var file := FileAccess.open("user://converted_to_opus.ogg", FileAccess.WRITE)
	file.store_buffer(buf)
	file.close()
	OS.shell_show_in_file_manager("user://converted_to_opus.ogg")
