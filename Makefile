fx_example:
	gcc -o bin/fx_example -Wall -Wextra src/fx.c src/fx_example.c

nbs:
	gcc -o bin/nbs -Wall -Wextra src/nonblocking_server.c src/synth.c src/saw.c -llo

pasynth:
	gcc -o bin/pasynth -Wall -Wextra src/pasynth.c src/synth.c src/saw.c src/nonblocking_server.c -llo -lportaudio

saw:
	gcc -o bin/saw -Wall -Wextra src/saw.c -llo -lm
