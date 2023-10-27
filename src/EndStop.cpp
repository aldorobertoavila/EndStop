#include <EndStop.h>

EndStop::EndStop(uint8_t swPin) {
  this->_swPin = swPin;
  this->_currentState = digitalRead(swPin);
  this->_previousState = digitalRead(swPin);
  this->_wasPressedAlready = HIGH;
  this->_wasReleasedAlready = HIGH;

  pinMode(_swPin, INPUT);
}

bool EndStop::isPressed() {
  return (_previousState && !_currentState) || (!_previousState && !_currentState);
}

void EndStop::tick() {
  unsigned long currentTime = millis();

  if (currentTime - _lastDebounceTime > _debounceTimeInterval) {
    _previousState = _currentState;
    _currentState = digitalRead(_swPin);
    _lastDebounceTime = currentTime;
  }
}

bool EndStop::wasPressed() {
  bool wasPressed = LOW;

  if (!_currentState && !_wasPressedAlready) {
    wasPressed = HIGH;
  }

  _wasPressedAlready = !_currentState;

  return wasPressed;
}

bool EndStop::wasReleased() {
  bool wasReleased = LOW;

  if (_currentState && !_wasReleasedAlready) {
    wasReleased = HIGH;
  }

  _wasReleasedAlready = _currentState;

  return wasReleased;
}

void EndStop::setDebounceTime(unsigned long debounceTime) {
  _debounceTimeInterval = debounceTime;
}