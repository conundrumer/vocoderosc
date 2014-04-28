CMSIP Project 5
===============
Readme
------
For our project we created a system we call vocoderosc that combines human voice input with a polyphonic synthesizer. The vocoder system consists of two main components: the synthesizer and the vocoder process. The user has the option of running both components on 1 machine or on 2 separate machines (further explanation and directions are below).

#### Synthesizer ####
The synthesizer runs a server to listen for OSC messages from devices running TouchOSC and connected MIDI devices, such as a MIDI keyboard. The synthesizer derives key and octave from the OSC messages, and then uses these to control oscillators (saw waves) which output samples to the vocoder component through a PortAudio stream.
##### Relevant Files #####
- src/lo_server.c
- src/lo_synthserv.c
- src/lo_stream.c
- src/synth.c
- src/saw.c
- src/utils.c

#### Vocoder ####
The vocoder component combines input from the synthesizer with input from a connected microphone by first passing each through a multiband filter. The volume of each band of the microphone input is then used to modulate the corresponding band of synthesizer input. The result is outputted through a PortAudio stream.
##### Relevant Files #####
- src/vocoder.c
- src/vocodermodulator.c
- src/volumedetector.c 
- src/vocodercarrier.c
- src/attenuator.c
- src/bandpass.c
- src/fx.c
- src/fx_multiband.c
- src/synthserv.c
- src/stream.c
- src/utils.c

Usage
-----
### Running on 1 computer ###
To run both components of vocoderosc on 1 computer, follow these steps:

1.  If using a device running TouchOSC, change the IP address in the TouchOSC settings to your
    machine's IP address and set the port number to 7770.
2.  (a) If using a connected MIDI device such as a MIDI keyboard, change directories to `vocoderosc/vocoderosc_1/` and run `sendOSC.srp`.

    (b) You also have the option of using a MIDI device that is connected to a separate computer. In this case, on the computer connected to the MIDI device, modify lines 13-17 of the file `vocoderosc/vocoderosc_1/sendOSC.srp` to match the code snippet below, replacing the parameter `"IP ADDRESS"` on line 17 with the IP address of the machine running the vocoder:
    ```sh
    13 // osc client
    14 def startup():
    15     # addr = osc_create_address("", "8001", false) // local
    16     # another computer
    17     addr = osc_create_address("IP ADDRESS", "7770", false) 
    ```
    Then, on the computer connected to the MIDI device, change directories to `vocoder/vocoderosc_1/` and run `sendOSC.srp`.
3.  Change directories to `vocoderosc/vocoderosc_1/` and enter the following commands:
    
    ```sh
    $ make test
    $ bin/test
    ```

### Running on 2 computers ###
In case a machine has difficulties running both components, you have the option of separating the system.

To run the synthesizer component on a machine with libLO and PortAudio installed, follow steps 1 and 2 from above, modifying and running the file `vocoderosc/sendOSC.srp` instead of `vocoderosc/vocoderosc_1/sendOSC.srp`. Then enter the following commands from the `vocoderosc/` directory:
```sh
$ make lo_server
$ bin/lo_server
```

To run the vocoder component on a separate machine that has PortAudio installed, enter the following commands from the `vocoderosc/` directory:
```sh
$ make pa_stream
$ bin/pa_stream
```
