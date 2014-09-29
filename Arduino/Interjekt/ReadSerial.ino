int posit = 0;   // for incoming serial data

void setupread() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loopread() {

        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                posit = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(posit, DEC);
        }
}
