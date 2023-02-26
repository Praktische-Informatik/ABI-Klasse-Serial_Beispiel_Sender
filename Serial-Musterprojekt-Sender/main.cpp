#include "Serial/Serial.h" // Beachte! Die Klasse Serial.h ist im Ordner Serial/Serial -> Siehe VS Projekt Ordner.
#include <iostream>
using namespace std;

// Übertragungs-Steuerzeichen
char ETX = 0x03; // End of Text (Ende eines Datenblocks);
char ACK = 0x06; // Acknowledge (fehlerfreie Übertragung);
char NAK = 0x15; // No Acknowledge (fehlerhafte Übertragung);
char SOH = 0x01; // Start of Heading (Start eines Blockes)
char EOT = 0x04;  // End of Transmission (Ende der Übertragung);
char CAN = 0x18;  //Cancel (Abbruch der Übertragung);Medium


int main()
{

	string port_nr = "";
	cout << "COM Port Nummer: ";

	//cin >> port_nr;
	port_nr = "2";

	string serieller_port("COM");
	serieller_port += port_nr;
	Serial* com2 = new Serial((string)serieller_port, 9600, 8, NOPARITY, ONESTOPBIT);

	if (com2->open()) {
		cout << "Schnittstelle Sender geoeffnet" << endl;

		// Ist der Empfaenger gestartet? 
		// Um das sicherzustellen, wird eine Schleife benötigt, die auf der Steuerleitung horcht, ob ein true gesendet wird. 
		bool steuerleitung_DTR_to_DSR = true;
		do {
			steuerleitung_DTR_to_DSR = com2->isDSR(); // Stuerleitungen sind nicht blockierend, d.h. eine if-Anweisung wie bei read() geht hier nicht.
			cout << "DSR empfaengt: " << steuerleitung_DTR_to_DSR << endl;
		} while (!steuerleitung_DTR_to_DSR);


		cout << "Sende ein 'A'" << endl;
		com2->write('A'); // wird binar gesendet >> 0100 0001

		cout << "Die Zeichenkette: Ball wird 2x gesendet." << endl;
		com2->write("Ball");
		com2->write("Ball\n"); // Ohne Zeilenumbruch funktioniert es nicht.

		char buffer[6] = "Hallo";
		com2->write(buffer, sizeof(buffer));
	}

		com2->close();
	return 0;
}