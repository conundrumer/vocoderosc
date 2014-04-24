test:
	gcc -o bin/test -Wall -Wextra src/* -llo -lportaudio

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

vd_test:
	gcc -o bin/vd_test -Wall -Wextra tests/vd_test.c src/volumedetector.c

vcc_test:
	gcc -o bin/vcc_test -Wall -Wextra tests/vcc_test.c src/vocodercarrier.c src/attenuator.c src/fx_multiband.c src/fx.c src/bandpass.c src/utils.c -lm

vcm_test:
	gcc -o bin/vcm_test -Wall tests/vcm_test.c src/fx.c src/bandpass.c src/volumedetector.c src/utils.c src/fx_multiband.c src/vocodermodulator.c -lm
