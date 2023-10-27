#include <EndStop.h>

EndStop endStop(2);

void setup() {
  Serial.begin(9600);

  endStop.setDebounceTime(10);
}

void loop() {
  endStop.tick();

  if (endStop.wasPressed()) {
    Serial.println("End Stop was pressed.");
  }

  if (endStop.wasReleased()) {
    Serial.println("End Stop was released.");
  }
}
