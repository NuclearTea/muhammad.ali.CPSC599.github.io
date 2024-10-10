#ifndef MIDIAPI_H
#define MIDIAPI_H
#include <MIDIUSB.h>

/* Midi Constants */
#define POT_CH 0
#define NOTE_ON 0x09
#define NOTE_OFF 0x08
#define MIN_VELOCITY 0
#define MAX_VELOCITY 127
#define MIN_PITCH 21
#define MAX_PITCH 108


/* Channel Controls */
#define CONTROL_CHANGE 0x0B
#define VOLUME_CONTROL 0x07
#define STOP 123



/* https://midi.org/midi-1-0-control-change-messages */

// MIDI Control Change Definitions
// #define MODULATION_WHEEL 1       // Modulation Wheel
// #define CHANNEL_VOLUME 7         // Channel Volume
#define PAN_CONTROL 10              // Pan
// #define EXPRESSION 11            // Expression
// #define SUSTAIN_PEDAL 64         // Sustain Pedal
// #define RESONANCE 71             // Resonance (Filter)
// #define FREQUENCY_CUTOFF 74      // Frequency Cutoff (Filter)
#define REVERB 91                   // Effects 1 Depth (Reverb)
// #define CHORUS 93                // Effects 2 Depth (Chorus)
// #define PORTAMENTO_TIME 5        // Portamento Time


// Wrappers
void playNote(byte note, byte velocity);
void changeVolume(byte volume);
void turnOffNote(byte note, byte velocity);
void changePan(byte pan);

// Base Functions
void noteOn(byte channel, byte pitch, byte velocity);
void noteOff(byte channel, byte pitch, byte velocity);
void controlChange(byte channel, byte control, byte value);
// void pitchBend(byte channel, int value);


#endif  // MIDIAPI_h