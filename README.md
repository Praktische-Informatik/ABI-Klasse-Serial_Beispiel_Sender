# ABI-Klasse-Serial_Beispiel_Sender

Es wird benötigt:<br> 
- Gitprojekt: ABI-Klasse-Serial_Beispiel_Empfaenger<br>
- ein virtueles Port Tool. Zum Beispiel HHD Virtual Serial Port Tool.<br>

**Serielle Schnittstellen**
> Zur Kommunikation über serielle Schnittstellen werden vom
> Betriebssystem Funktionen bereitgestellt (Win-API). Diese werden in
> der Klasse Serial gekapselt. Die Klasse Serial stellt entsprechenden
> Methoden zur Ansteuerung der seriellen Schnittstelle zur Verfügung.
> (vgl. Klassen-Diagramm)

![grafik](https://user-images.githubusercontent.com/78038701/221399201-10c8095e-9b97-4f6f-94dc-dc90f0707711.png)

### Kurzbeschreibung der Klasse `Serial`

| Methode / Attribut        | Beschreibung |
|---------------------------|--------------|
| `Serial()`                | Konstruktor initialisiert und konfiguriert die serielle Schnittstelle, ohne sie zu öffnen. |
| `portName`                | Name des Ports, z. B. `"COM2"` |
| `baudrate`                | Baudrate, z. B. 2400 oder 9600 |
| `dataBits`                | Datenbitanzahl, 5 – 8 |
| `stopBits`                | Stopbitanzahl, 1 oder 2 |
| `parity`                  | [Parität](https://de.wikipedia.org/wiki/Parit%C3%A4tsbit), 0 = none, 1 = odd, 2 = even |
| `open(): boolean`         | Öffnet die serielle Schnittstelle; liefert `true`, wenn verwendbar, sonst `false`. |
| `close(): void`           | Schließt die serielle Schnittstelle; danach nicht mehr verwendbar, bis erneut geöffnet. |
| `dataAvailable(): int`    | Liefert die aktuelle Anzahl an Bytes, die ohne Blockieren gelesen werden können. |
| `read(): int`             | Liest **ein** Byte (0–255), liefert `-1`, wenn Port nicht geöffnet. Blockierend. |
| `read(b: byte[], len):int`| Liest **mehrere** Bytes in ein Array; liefert Anzahl gelesener Bytes oder `-1`, wenn keine verfügbar. Blockierend bis min. 1 Byte empfangen. |
| `readLine(): String`      | Liest eine Zeile bis `'\n'`; liefert `null`, wenn Port nicht geöffnet. Blockierend bis Zeilenende. |
| `write(value: int)`       | Schreibt ein Byte (0–255). Falls Port nicht geöffnet, passiert nichts. |
| `write(b: byte[], len)`   | Schreibt mehrere Bytes. Falls Port nicht geöffnet, passiert nichts. |
| `write(s: String)`        | Schreibt einen String; der **String muss mit `\n` enden**. Falls Port nicht geöffnet, passiert nichts. |
| `setRTS(arg: boolean)`    | Setzt RTS-Leitung (true = HIGH, false = LOW). |
| `setDTR(arg: boolean)`    | Setzt DTR-Leitung (true = HIGH, false = LOW). |
| `isCTS(): boolean`        | Liefert den Status von CTS (Clear To Send). |
| `isDSR(): boolean`        | Liefert den Status von DSR (Data Set Ready). |
