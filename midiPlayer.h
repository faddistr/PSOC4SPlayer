/** @file
 *  @brief Header file for MIDI sequencer
 */ 
#ifndef MIDI_PLAYER_H
#define MIDI_PLAYER_H
#include <stdbool.h>
/**
 * @defgroup MidiSequencer
 * 
 * Mixed up to 16 channels.
 * Only type 0 files with one track is supported.
 * Not all events are supported.
 * Is controlled through player module
 *
 * @{
 */  
/**
 * @brief Play MIDI file
 *
 * @param[in] fname full path to file on SD card
 *
 * @return false failed to play
 */
bool midiPlayer_Play(const char *fname);
/** @} */   
#endif /* MIDI_PLAYER_H */