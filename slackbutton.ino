// an internet button

// This one will post a snarky message on our Slack #test channel

const int button = D0;
const int onboardLed = D7;

// Long press and Debounce
boolean buttonUp = TRUE;
long buttonPressedAt = millis();
const int debounceTime = 50;

// Heartbeat
#define ONE_MINUTE_MILLIS (60 * 1000)
unsigned long lastHeartbeat = millis();

// Daily clock synch
#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
unsigned long lastSync = millis();

void setup() {
  pinMode(button,INPUT_PULLDOWN);
  pinMode(onboardLed,OUTPUT);

  Particle.subscribe("hook-response/slackbutton", gotData, MY_DEVICES);

  for( int i=0; i<5; i++) {
    digitalWrite(onboardLed,HIGH);
    delay(100);
    digitalWrite(onboardLed,LOW);
    delay(100);
  }
}

void gotData(const char *name, const char *data) {
  String str = String(data);
  if( str == "ok") {
    digitalWrite(onboardLed,HIGH);
    delay(100);
    digitalWrite(onboardLed,LOW);
    delay(100);
    }
}

void loop() {
  // react to a button down, regardless how long
  if(buttonUp && digitalRead(button) == HIGH) {

    // handle debounce
    buttonPressedAt = millis();
    while( digitalRead(button) == HIGH && millis() - buttonPressedAt < debounceTime) {
      Particle.process(); // essentially, do nothing
    }
    buttonUp = FALSE;
    Particle.publish("slackbutton", "I am a button bot!", 60, PRIVATE);
    digitalWrite(onboardLed,HIGH);
    delay(500);
    digitalWrite(onboardLed,LOW);
  }
  if(digitalRead(button) == LOW) {
    buttonUp = TRUE;
  }

  // Call home each minute
  if (millis() - lastHeartbeat > ONE_MINUTE_MILLIS) {
    Particle.publish("particle/device/name");
    lastHeartbeat = millis();
  }
  // Synchronize the clock Daily
  if (millis() - lastSync > ONE_DAY_MILLIS) {
    Particle.syncTime();
    lastSync = millis();
  }
}
