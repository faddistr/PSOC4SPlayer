# PSOC4SPlayer
 
## INTRODUCTION

This is simple realisation of the music player for Cypress PSOC4S MCU
It contains also very simple and primitive MIDI sequencer. 
Files is played from SD card, maybe BLE support will be added in the future.
(Too many projects with BLE, sorry)
For audio generation PWM with 8-bit resolution is using.
For SD card Fatfs library was ported from other Cypress MCU with some little enhancments to get maximum speed.
Since there is only 32K memory available, CapSense was not used.
UART is uses for debuging messages output.
Supported formats: <BR>
PCM/WAV 8-bit, Mono, sample rate: 4K, 8K, 16K, 32K, 64K without compression and without tags,
which is enought to here voice and other sounds for most people<BR>
MIDI type 0 (one MTrk record), better conver MIDI to WAV <BR>

## Architecture and code style

Due to limit resources of the MCU it was decided not to use any RTOS. 
Therefore 1-thread superloop architecture with async callse was used.
Code style was decided to use closed to MISRA-2012 standard

### Layers of the architecture

The lowest layer of sound generation is located in audio.c module.
2 timers were used: 1 in PWM mode to generate required voltage level according to provided 
and 1 in compare mode which is dynamically reconfigured according to required sample rate. 
High levels modules just add their callbacks and uses audio_Play function for playing sepparated 8-bit samples.
Audio.c module provides also pseudo logarithmic attenuation volume adjustment of the input samples.

testPlayer.c and player.c modules uses audio module directly.
testPlayer is generator of various debug sounds, which were used for hardware debugging.
player.c is controller of the music play. It also manages 1K cicle buffer, 
which is fullfiled by callbacks from other addon-players. Buffer is located in module buffer.c
Other modules just expand functionality of this module.

Addon players are pcmPlayer(PCM and WAV) and midiPlayer(MIDI sequencer).
This two modules expand player.c
High level module filePlayer.c searches for music files in root directory of the
SD card and selects required addon-player according to extension of the file. (wrapper for sd card in card.c)
When previous was ended filePlayer searches for next one.
 
userControls.c module handles various events from button (only SW2 is available on CY8CKIT).
It determins duration of the button press. And provides event information to bussiness logic in main.c
Functions to measure time intervals are located in sysTickTimer (standart ARM`s SysTick is used).

Bussiness logic and debug console handling are located in main.c

Thanks Cypress Semiconductor Ukraine for the development kit
[video](https://drive.google.com/file/d/1AFBACRh2ApOItkp5jCkcnmtwX1QXsioC/view)
![foto](/images/foto.jpg)