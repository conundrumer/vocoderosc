test:
	gcc -o bin/test -Wall -Wextra src/synthserv.c src/synth.c src/stream.c src/nonblocking_server.c src/utils.c src/saw.c src/vocoder.c src/fx_multiband.c src/fx.c src/volumedetector.c src/vocodercarrier.c src/attenuator.c src/bandpass.c -llo -lportaudio

at_test:
	gcc -o bin/at_test -Wall -Wextra tests/at_test.c src/attenuator.c -lm

bp_test:
	gcc -o bin/bp_test1 -Wall -Wextra tests/bp_test.c src/fx.c src/bandpass.c src/utils.c -lm

fx_example:
	gcc -o bin/fx_example_test -Wall -Wextra src/fx.c tests/fx_example.c

mb_test:
	gcc -o bin/mb_test -Wall -Wextra src/fx.c tests/mb_test.c src/bandpass.c src/utils.c src/fx_multiband.c -lm

nbs_test:
	gcc -o bin/nbs_test -Wall -Wextra src/nonblocking_server.c tests/nbs_test.c src/synth.c src/saw.c src/utils.c -llo

vd_test:
	gcc -o bin/vd_test src/volumedetector.c tests/vd_test.c -Wall -Wextra	

vcc_test:
	gcc -o bin/vcc_test -Wall -Wextra tests/vcc_test.c src/vocodercarrier.c src/attenuator.c src/fx_multiband.c src/fx.c src/bandpass.c src/utils.c -lm

vcm_test:
	gcc -o bin/vcm_test -Wall src/fx.c src/bandpass.c src/volumedetector.c src/utils.c src/fx_multiband.c src/vocodermodulator.c tests/vcm_test.c -lm
