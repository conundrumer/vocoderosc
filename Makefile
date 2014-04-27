test:
	gcc -o bin/test -Wall -Wextra src/* -llo -lportaudio

pa_stream:
	gcc -o bin/pa_stream -Wall -Wextra src/synthserv.c src/vocoder.c src/vocodermodulator.c src/fx.c src/fx_multiband.c src/bandpass.c src/attenuator.c src/volumedetector.c src/stream.c src/vocodercarrier.c src/utils.c -lportaudio -lm

lo_server:
	gcc -o bin/lo_server -Wall -Wextra src/synth.c src/lo_server.c src/saw.c src/utils.c -llo

test-win32:
	gcc -o bin/test -Wall -Wextra src/* -llo -lportaudio -lws2_32

at_test:
	gcc -o bin/at_test -Wall -Wextra tests/at_test.c src/attenuator.c -lm

bp_test:
	gcc -o bin/bp_test -Wall -Wextra tests/bp_test.c src/fx.c src/bandpass.c src/utils.c -lm

fx_example:
	gcc -o bin/fx_example -Wall -Wextra src/fx.c tests/fx_example.cs

mb_test:
	gcc -o bin/mb_test -Wall -Wextra tests/mb_test.c src/fx.c src/fx_multiband.c src/bandpass.c src/utils.c -lm

nbs_test:
	gcc -o bin/nbs_test -Wall -Wextra tests/nbs_test.c src/nonblocking_server.c src/synth.c src/saw.c src/utils.c -llo

bp_ir:
	gcc -o bin/bp_ir -Wall -Wextra src/fx.c src/bandpass.c src/utils.c tests/bp_ir.c

mb_test1:
	gcc -o bin/mb_test1 -Wall -Wextra src/fx.c src/mb_test1.c src/bandpass.c src/utils.c src/fx_multiband.c

mb_ir:
	gcc -o bin/mb_ir -Wall -Wextra src/fx.c src/bandpass.c src/utils.c src/fx_multiband.c tests/mb_ir.c

vcc:
	gcc -o bin/vcc -Wall -Wextra src/vocodercarrier.c src/attenuator.c src/fx_multiband.c src/fx.c src/bandpass.c src/utils.c -lm

vd_test:
	gcc -o bin/vd_test -Wall -Wextra tests/vd_test.c src/volumedetector.c

vcc_test:
	gcc -o bin/vcc_test -Wall -Wextra tests/vcc_test.c src/vocodercarrier.c src/attenuator.c src/fx_multiband.c src/fx.c src/bandpass.c src/utils.c -lm

vcm_test:
	gcc -o bin/vcm_test -Wall tests/vcm_test.c src/fx.c src/bandpass.c src/volumedetector.c src/utils.c src/fx_multiband.c src/vocodermodulator.c -lm

vc_test:
	gcc -o bin/vc_test -Wall -Wextra tests/vc_test.c src/vocoder.c src/vocodercarrier.c src/attenuator.c src/fx_multiband.c src/bandpass.c src/utils.c src/fx.c src/volumedetector.c src/vocodermodulator.c
