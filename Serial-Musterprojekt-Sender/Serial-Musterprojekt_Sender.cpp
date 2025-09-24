/*
  SENDER (Transmitter)

  Voraussetzungen:
    - Ein virtuelles COM-Port-Paar (z. B. mit HHD Virtual Serial Port Tool).
      Beispiel: COM1 <-> COM2, wobei der SENDER auf COM1, der EMPFÄNGER auf COM2 liegt.

  Ablauf:
    1) SENDER öffnet seinen Port.
    2) SENDER wartet, bis EMPFÄNGER DTR=true setzt (als DSR sichtbar).
    3) SENDER sendet einzelne Zeichen, Strings und einen Puffer.

  Hinweise:
    - DSR wird per Polling abgefragt; das ist nicht blockierend.
    - Write-Aufrufe können kurz blockieren (Timeout z. B. 100 ms in unserer Serial.cpp).
*/

#include "Serial/Serial.h"  // Serial-Klasse liegt im Ordner Serial/Serial  (siehe VS-Projektordner)
#include <iostream>
using namespace std;

// Übertragungs-Steuerzeichen (für spätere Protokoll-Erweiterungen nützlich)
char ETX = 0x03; // End of Text (Ende eines Datenblocks)
char ACK = 0x06; // Acknowledge (fehlerfreie Übertragung)
char NAK = 0x15; // No Acknowledge (fehlerhafte Übertragung)
char SOH = 0x01; // Start of Heading (Start eines Blockes)
char EOT = 0x04; // End of Transmission (Ende der Übertragung)
char CAN = 0x18; // Cancel (Abbruch der Übertragung)

int main()
{
    // COM-Port-Nummer: hier zur Demo fest verdrahtet (statt cin >> port_nr)
    string portNr = "1";   // Beispiel: Empfänger auf COM1
    //cin >> portNr;
    cout << "COM Port Nummer (Empfaenger): " << portNr << endl;

    // "COM" + Nummer ergibt den Portnamen (z. B. "COM1")
    string port = "COM" + portNr;

    Serial com(port, 9600, 8, ONESTOPBIT, NOPARITY);

    if (com.open()) {
        cout << "Schnittstelle Sender geoeffnet" << endl;

        // Prüfen, ob der Empfänger bereit ist (DTR=true -> DSR=true).
        // Standleitungen sind nicht blockierend; daher "Warte"-Schleife:
        bool steuerleitung_DTR_to_DSR = false;
        do {
            steuerleitung_DTR_to_DSR = com.isDSR();
            cout << "DSR empfaengt (Empfaenger bereit?): " << steuerleitung_DTR_to_DSR << endl;
            Sleep(10);  // warten für 10 ms
        } while (!steuerleitung_DTR_to_DSR);

        // --- Sende-Beispiele -----------------------------------------------
        cout << "Sende ein 'A'" << endl;
        com.write('A'); // wird binär gesendet: 0b0100'0001

        cout << "Sende die Zeichenkette: Ball (2x, beim zweiten Mal mit Newline)" << endl;
        com.write("Ball");
        com.write("Ball\n"); // Viele Gegenstellen (und unser readLine) erwarten '\n' als Zeilenende.

        cout << "Sende Hallo" << endl;
        // Senden eines Puffers inkl. Nullbyte:
        char buffer[6] = "Hallo";  // 5 Zeichen + '\0'
        com.write(buffer, sizeof(buffer));
        // -------------------------------------------------------------------
    }

    com.close();
    return 0;
}
