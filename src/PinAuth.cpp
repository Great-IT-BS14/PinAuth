#include "PinAuth.h"

#include <avr/pgmspace.h>
#include <string.h>

// PinAuth()
// Stores one user name in RAM and the address of that user's PIN in flash memory.
PinAuth::PinAuth(const char *user, const char *pinInFlash)
    : user_(user), pinInFlash_(pinInFlash) {}

// reset()
// Clears the entered PIN so a new attempt can begin immediately.
void PinAuth::reset() {
  memset(entry_, 0, sizeof(entry_));
  length_ = 0;
}

// handleKey()
// Edits up to six digits, confirms with #, deletes with *, and clears with D without retry delays.
PinAuth::Result PinAuth::handleKey(char key) {
  if (key >= '0' && key <= '9') {
    if (length_ >= sizeof(entry_) - 1) return UNCHANGED;
    entry_[length_++] = key;
    entry_[length_] = '\0';
  } else if (key == '*') {
    if (length_ == 0) return UNCHANGED;
    entry_[--length_] = '\0';
  } else if (key == '#') {
    if (strcmp_P(entry_, pinInFlash_) == 0) return ACCEPTED;
    reset();
    return REJECTED;
  } else if (key == 'D') {
    reset();
  } else {
    return UNCHANGED;
  }
  return CHANGED;
}

// user()
// Returns the configured user name for the login display.
const char *PinAuth::user() const {
  return user_;
}

// length()
// Returns the number of entered digits so the display can mask them without reading the PIN.
uint8_t PinAuth::length() const {
  return length_;
}
