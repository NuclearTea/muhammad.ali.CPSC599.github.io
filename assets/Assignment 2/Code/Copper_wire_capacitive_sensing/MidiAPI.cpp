#include "MidiAPI.h"
#include "utils.h"

///////////////////////////////
// Wrappers for Midi
void playNote(byte note, byte velocity) {
  noteOn(POT_CH, note, velocity);
  MidiUSB.flush();
}

void changeVolume(byte volume) {
  printToSerial("Volume: " + String(volume));
  controlChange(POT_CH, VOLUME_CONTROL, volume);  // control change 7 is for volume
  MidiUSB.flush();
}

void turnOffNote(byte note, byte velocity) {
  noteOff(POT_CH, note, velocity);
  MidiUSB.flush();
}

void changePan(byte pan) {
  printToSerial("Pan: " + String(pan));
  controlChange(POT_CH, PAN_CONTROL, pan);
  MidiUSB.flush();
}


/* Arduino (midi functions MIDIUSB Library) */
// all command bytes are left shifted by 4 (half-byte) and then | with the specified channel
// this describes the command and the channel the command should be sent to


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { NOTE_ON, (uint8_t)((NOTE_ON << 4) | channel), pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = { NOTE_OFF, (uint8_t)((NOTE_OFF << 4) | channel), pitch, velocity };
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = { CONTROL_CHANGE, (uint8_t)((CONTROL_CHANGE << 4) | channel), control, value };
  MidiUSB.sendMIDI(event);
}

// Example Pitch bend command

// void pitchBend(byte channel, int value) {
//   byte low_value = value & 0x7f;
//   byte high_value = value >> 7;
//   midiEventPacket_t pitch_bend = { 0x0E, 0xE0 | channel, low_value, high_value };
//   MidiUSB.sendMIDI(pitch_bend);
// }