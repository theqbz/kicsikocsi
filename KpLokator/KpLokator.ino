/*
	KICSIKOCSI K�ZPONTI EGYS�G - LOK�TOR

 Name:		KpLokator.ino
 Created:	1/9/2021 11:06:05 PM
 Author:	qbz
*/

#include <Wire.h>
#include "Lokator.h"

// Arduino WiFi Rev2 pin kioszt�s
#define HC1Echo 4			// Els� HC-SR04-4P Echo
#define HC1Trig 5			// Els� HC-SR04-4P Triger
#define HC2Echo 6			// H�ts� HC-SR04 Echo
#define HC2Trig 7			// H�ts� HC-SR04 Triger

// egy�b �lland�k
#define LOKATOROK_SZAMA 2		// A kocsin m�k�d� lok�torok sz�ma
#define FOGADOTT_TOMB_MERET 3	// A m�sik arduinot�l fogadott adatok m�rete

byte kuldottAdatok[LOKATOROK_SZAMA];
byte fogadottAdatok[FOGADOTT_TOMB_MERET];
bool adatFogadasRendben = false;
Lokator elso(HC1Trig, HC1Echo);
Lokator hatso(HC2Trig, HC2Echo);

//// debug
//unsigned long actTime;
//unsigned long prevTime;
//int L;

void adatokFogadasa(int n) {
	if (n != FOGADOTT_TOMB_MERET) digitalWrite(LED_BUILTIN, HIGH);
	else {
		digitalWrite(LED_BUILTIN, LOW);
		int i = 0;
		while (i < FOGADOTT_TOMB_MERET && Wire.available()) {
			fogadottAdatok[i] = Wire.read();
			i++;
		}
	}
}

void adatokKuldese() {
	kuldottAdatok[0] = elso.getTavolsag();
	kuldottAdatok[1] = hatso.getTavolsag();
	Wire.write(kuldottAdatok, sizeof(kuldottAdatok));
}

void setup() {
	pinMode(HC1Trig, OUTPUT);
	pinMode(HC1Echo, INPUT);
	pinMode(HC2Trig, OUTPUT);
	pinMode(HC2Echo, INPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	Wire.begin(0x02);
	Wire.onReceive(adatokFogadasa);
	Wire.onRequest(adatokKuldese);
}

void loop() {}

