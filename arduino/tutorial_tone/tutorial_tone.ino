/*
 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8
 http://www.arduino.cc/en/Tutorial/Tone
 */
#include "pitches.h"
#include "array.hpp"
#include "pair.hpp"

static const int BuzzerPin = 8;

// to calculate the note duration, take one second divided by the note type.
enum NoteDuration : unsigned long {
  DoubleWhole = 1000 * 2,
  Whole = 1000 / 1,
  Half = 1000 / 2,
  Quarter = 1000 / 4,
  QuarterDot = 1000 / 8 * 3,
  Eighth = 1000 / 8,
  EighthDot = 1000 / 16 * 3,
  Sixteenth = 1000 / 16,
  ThirtySecond = 1000 / 32,
  SixtyFourth = 1000 / 64,
  /**/
  Breve = DoubleWhole,
  Semibreve = Whole,
  Minim = Half,
  Crotchet = Quarter,
  Quaver = Eighth,
  Semiquaver = Sixteenth,
  Demisemiquaver = ThirtySecond,
  Hemidemisemiquaver = SixtyFourth
};

using NoteFrequency = unsigned int;

struct Note {
  Note(NoteDuration d_ms, NoteFrequency f_hz) : duration_ms(d_ms), frequency_hz(f_hz) {}
  
  NoteDuration duration_ms; // milliseconds
  NoteFrequency frequency_hz;
};

#define CHOICE 1
// CDEFGAB

#if CHOICE == 0
std::array<Note, 8> notes = {
  Note{Quarter, NOTE_C4},
  Note{Eighth,  NOTE_G3},
  Note{Eighth,  NOTE_G3},
  Note{Quarter, NOTE_A3},
  Note{Quarter, NOTE_G3},
  Note{Quarter, 0},
  Note{Quarter, NOTE_B3},
  Note{Quarter, NOTE_C4}
};
#elif CHOICE == 1 // mazurek
std::array<Note, 16> notes = {
  Note{EighthDot, NOTE_A4},
  Note{Sixteenth,  NOTE_AS4}, // B4 bemol
  Note{Quarter,  NOTE_C5},
  Note{Quarter, NOTE_C5},
  //
  Note{EighthDot, NOTE_C5},
  Note{Sixteenth, NOTE_A4},
  Note{Eighth, NOTE_D5},
  Note{Eighth, NOTE_C5},
  Note{Eighth, NOTE_AS4},
  Note{Eighth, NOTE_A4},
  //
  Note{EighthDot, NOTE_G4},
  Note{Sixteenth, NOTE_G4},
  Note{QuarterDot, NOTE_C5},
  Note{Eighth, NOTE_AS4},
  //
  Note{Quarter, NOTE_AS4},
  Note{Quarter, NOTE_A4}
};
#else
#  error "Unknown choice!"
#endif

void setup() {
  // iterate over the notes of the melody:
  for (const Note & note : notes) {
    tone(BuzzerPin, note.frequency_hz, note.duration_ms);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = note.duration_ms * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BuzzerPin); // FIXME: unnecessary?
  }
}

void loop() {
  // no need to repeat the melody.
}
