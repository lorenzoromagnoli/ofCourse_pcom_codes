#include <MIDI.h>

// Simple tutorial on how to send MIDI messages to hairless MIDI Seria bridge. 
// the code demonsrate the use of MIDI_CREATE_CUSTOM_INSTANCE to set 
// the MIDI object baudrate to 115200

struct midiSettings : public midi::DefaultSettings {
  static const long BaudRate = 115200;
};

// Create a 'MIDI' object using MySettings bound to Serial2.
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, midiSettings);


void setup()
{
  MIDI.begin(1);                      // Launch MIDI and listen to channel 4
}

void loop()
{

  MIDI.sendNoteOn(42, 127, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
  delay(1000);		            // Wait for a second
  MIDI.sendNoteOff(42, 0, 1);     // Stop the note
  delay(1000);
}
