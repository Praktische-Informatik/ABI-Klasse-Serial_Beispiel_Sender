// Version 09.2025 – überarbeitet mit erklärenden Kommentaren
#pragma once

#include <iostream>
#include <string>
#include <list>
#include <Windows.h>

using namespace std;

/**
 * @brief Einfache Wrapper-Klasse für eine serielle Schnittstelle unter Windows.
 *
 * Bietet Methoden zum Öffnen/Schließen, Senden/Empfangen von Daten
 * sowie zur Steuerung von Handshake-Signalen (RTS/DTR/CTS/DSR).
 *
 * Beispiel:
 *   Serial ser("COM3", 9600, 8, ONESTOPBIT, NOPARITY);
 *   if (ser.open()) {
 *       ser.write("Hello World\n");
 *       string line = ser.readLine();
 *       ser.close();
 *   }
 */
class Serial
{
private:
	string portName;  ///< COM-Port-Name, z. B. "COM3"
	int baudrate;     ///< Baudrate (z. B. 9600, 115200)
	int dataBits;     ///< Anzahl Datenbits (5–8)
	int stopBits;     ///< ONESTOPBIT, ONE5STOPBITS oder TWOSTOPBITS
	int parity;       ///< NOPARITY, ODDPARITY, EVENPARITY, ...
	HANDLE handle;    ///< Handle auf den COM-Port (INVALID_HANDLE_VALUE, wenn geschlossen)

public:
	// -------- Konstruktoren / Destruktor --------

	/**
	 * @brief Konstruktor: Parameter setzen, aber Port noch nicht öffnen.
	 */
	Serial(string portName, int baudrate, int dataBits, int stopBits, int parity);

	/**
	 * @brief Destruktor: schließt die Schnittstelle automatisch, falls noch offen.
	 */
	~Serial();

	// -------- Basisoperationen --------

	/**
	 * @brief Öffnet die serielle Schnittstelle und setzt Parameter.
	 * @return true, wenn erfolgreich geöffnet; false sonst.
	 */
	bool open();

	/**
	 * @brief Schließt die Schnittstelle (falls offen).
	 */
	void close();

	/**
	 * @brief Anzahl Bytes, die aktuell im Eingabepuffer verfügbar sind.
	 * @return >=0; bei Fehler 0.
	 */
	int dataAvailable();

	// -------- Leseoperationen --------

	/**
	 * @brief Liest ein einzelnes Byte.
	 * @return Wert 0–255; -1 wenn nichts verfügbar oder Port nicht offen.
	 * @note Dank gesetzter Timeouts blockiert der Aufruf nicht.
	 */
	int read();

	/**
	 * @brief Liest bis zu bufSize Bytes in den Puffer.
	 * @return Anzahl tatsächlich gelesener Bytes (0..bufSize).
	 */
	int read(char* buffer, int bufSize);

	/**
	 * @brief Liest Text bis zum Linefeed ('\n').
	 * @return Empfangene Zeichenkette (ohne '\n').
	 * @note Gibt zurück, was bisher gelesen wurde, falls noch kein LF empfangen.
	 */
	string readLine();

	// -------- Schreiboperationen --------

	/**
	 * @brief Schreibt ein einzelnes Byte.
	 */
	void write(int value);

	/**
	 * @brief Schreibt einen Datenpuffer.
	 */
	void write(const char* buffer, int bytesToWrite);

	/**
	 * @brief Schreibt einen String (ohne automatisches Newline).
	 */
	void write(string s);

	// -------- Modem-/Handshake-Signale --------

	void setRTS(bool arg);  ///< Setzt RTS-Leitung (true=aktiv)
	void setDTR(bool arg);  ///< Setzt DTR-Leitung (true=aktiv)
	bool isCTS();           ///< Liest CTS-Leitung (true=aktiv)
	bool isDSR();           ///< Liest DSR-Leitung (true=aktiv)
};
