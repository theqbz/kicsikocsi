/*
KICSIKOCSI T�VIR�NY�T�

 Name:		kicsikocsi.ino
 Created:	12/5/2020 6:14:38 PM
 Author:	qbz
*/

#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <MPU6050.h>

// Arduino Nano pin-kioszt�s
#define gomb 4
#define led 5
#define RfCS 7					// az nRF24L01 modul "Chip Set" l�ba
#define RfCE 8					// az nRF24L01 modul "Chip Enable" l�ba
#define MINT 10
#define MSDA A4
#define MSCL A5

// nRF24L01 r�di� �lland�i
RF24 radio(RfCE, RfCS);					// R�di�
const byte cim = 9654;					// a R�di� csatorn�j�nak c�me

// MPU6050 giroszk�p �lland�i
MPU6050 giroszkop;						// Giroszk�p
int16_t nyAx, nyAy, nyAz;				// nyers gyorsul�s adatok az adott tengelyen
int16_t nyGx, nyGy, nyGz;				// nyers elfordul�s adatok az adott tengelyen

// egy�b glob�lis v�ltoz�k
long uzenet = 0L;						// Be/Ki �s az ir�nyok egy 7 jegy� eg�sz sz�mban
int tomb[2];
int y = 0;								// oldalir�ny� elmozdul�s (0-90-ig: balra, 90-180-ig balra)

void setup() {
	//Serial.begin(9600);
	giroszkop.initialize();				// Giroszk�p ind�t�sa
	pinMode(gomb, INPUT);
	radio.begin();						// R�di� bekapcsol�sa
	radio.openWritingPipe(cim);			// csatorna megnyit�sa adatok k�ld�s�hez a k�zpontba
	radio.setPALevel(RF24_PA_MIN);		// R�di� t�rerej�nek minimumra �ll�t�sa
	GiroOffset();						// Giroszk�p null�z�sa
}


void loop() {
	radio.stopListening();							// ad�-m�dba kapcsolja a r�di�t

	giroszkop.getMotion6(&nyAx, &nyAy, &nyAz, &nyGx, &nyGy, &nyGz);		// ir�nyok kiolvas�sa
	y = map(nyAy, -16000, 16000, 0, 180);
	//GyroPrint();

	
//	if (digitalRead(gomb))
//	{
//		uzenet = 1L;
//		tomb[0] = 1;
//		tomb[1] = 12;
//		radio.write(tomb, sizeof(tomb));			// �tenet k�ld�se
////		Serial.println("megnyomva: BE");
//	}
//	else
//	{
//		uzenet = 0L;
//		tomb[0] = 2;
//		tomb[1] = 22;
//		radio.write(tomb, sizeof(tomb));			// �tenet k�ld�se
////		Serial.println("nincs megnyomva: KI");
//	}
	delay(5);
}


//void GyroPrint() {
//	//Serial.print("X=");
//	//Serial.print(nyAx);
//	Serial.print("\tnyY=");
//	Serial.print(nyAy);
//	//Serial.print("\tZ=");
//	//Serial.println(nyAz);
//	Serial.print("\tY=");
//	Serial.println(y); 
//}

void GiroOffset() {
	giroszkop.setXAccelOffset(-549);
	giroszkop.setYAccelOffset(-5894);
	giroszkop.setZAccelOffset(1684);
}


int ErtekKonverzio(int16_t nyX, int16_t nyY, int16_t nyZ) {

}