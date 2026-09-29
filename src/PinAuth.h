#pragma once

#include <Arduino.h>

class PinAuth {
 public:
  enum Result : uint8_t { UNCHANGED, CHANGED, ACCEPTED, REJECTED };

  PinAuth(const char *user, const char *pinInFlash);
  void reset();
  Result handleKey(char key);
  const char *user() const;
  uint8_t length() const;

 private:
  const char *user_;
  const char *pinInFlash_;
  char entry_[7] = "";
  uint8_t length_ = 0;
};
