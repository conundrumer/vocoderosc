test:
	gcc -o bin/test -Wall -Wextra ../src/attenuator.c ../src/bandpass.c ../src/fx.c ../src/fx_multiband.c ../src/lo_server.c ../src/saw.c ../src/synth.c ../src/utils.c ../src/vocoder.c ../src/vocodercarrier.c ../src/vocodermodulator.c ../src/volumedetector.c src/stream.c src/synthserv.c -llo -lportaudio

test-win32:
	gcc -o bin/test -Wall -Wextra src/* -llo -lportaudio -lws2_32

at_test:
	gcc -o bin/at_test -Wall -Wextra tests/at_test.c ../src/attenuator.c -lm

bp_test:
	gcc -o bin/bp_test -Wall -Wextra tests/bp_test.c ../src/fx.c ../src/bandpass.c ../src/utils.c -lm

fx_example:
	gcc -o bin/fx_example -Wall -Wextra ../src/fx.c tests/fx_example.c

mb_test:
	gcc -o bin/mb_test -Wall -Wextra tests/mb_test.c ../src/fx.c ../src/fx_multiband.c ../src/bandpass.c ../src/utils.c -lm

nbs_test:
	gcc -o bin/nbs_test -Wall -Wextra tests/nbs_test.c ../src/lo_server.c ../src/synth.c ../src/saw.c ../src/utils.c -llo

bp_ir:
	gcc -o bin/bp_ir -Wall -Wextra ../src/fx.c ../src/bandpass.c ../src/utils.c tests/bp_ir.c -lm

mb_ir:
	gcc -o bin/mb_ir -Wall -Wextra ../src/fx.c ../src/bandpass.c ../src/utils.c ../src/fx_multiband.c tests/mb_ir.c -lm

vd_test:
	gcc -o bin/vd_test -Wall -Wextra tests/vd_test.c ../src/volumedetector.c

vcc_test:
	gcc -o bin/vcc_test -Wall -Wextra tests/vcc_test.c ../src/vocodercarrier.c ../src/attenuator.c ../src/fx_multiband.c ../src/fx.c ../src/bandpass.c ../src/utils.c -lm

vcm_test:
	gcc -o bin/vcm_test -Wall tests/vcm_test.c ../src/fx.c ../src/bandpass.c ../src/volumedetector.c ../src/utils.c ../src/fx_multiband.c ../src/vocodermodulator.c -lm

vc_test:
	gcc -o bin/vc_test -Wall -Wextra tests/vc_test.c ../src/vocoder.c ../src/vocodercarrier.c ../src/attenuator.c ../src/fx_multiband.c ../src/bandpass.c ../src/utils.c ../src/fx.c ../src/volumedetector.c ../src/vocodermodulator.c -lm
