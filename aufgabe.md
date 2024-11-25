## Aufgabe (Synchronisation von Threads in JAVA)

Gegeben im Verzeichnis Vorlagen ist die Klasse UniqueId, mit folgenden Eigenschaften:

- Dem Konstruktor wird als Argument ein Dateiname übergeben.
- Die Methode init(<wert>), die den ihr übergebenen Wert als ganze Zahl in die mit dem Konstruktor angegebene Datei schreibt.
- Die Methode getNext(), die den aktuellen Wert aus der Datei liest und die Datei schließt um eine längere Verarbeitung zu simulieren. Anschließend wird der um eins erhöhte Wert in die erneut geöffnete Datei geschrieben und als Rückgabewert an die aufrufende Methode zurückgegeben.
- Zum Schreiben und Lesen werden die Methoden (readInt und writeInt) der Klassen DataOutputStream und DataInputStream verwendet

Erzeugen Sie nun eine Klasse Test, bei der:

- eine Datei id.dat erzeugt und mit einem Wert 10000 initialisiert wird
- jeweils 5 gleichartige Threads, also unterschiedliche Objekte, erzeugt werden.
- jeder dieser Threads 10-mal die ID mit der Methode getNext erhöht und seinen Namen, sowie den Rückgabewert ausgibt.

Testen Sie die unsynchronisierten Klassen ausreichend. Überprüfen Sie hierbei insbesondere die Programmausgaben.
Synchronisieren Sie nun die Methoden getNext(), da diese nebenläufig aufgerufen werden können.
Testen Sie die modifizierten Klassen ausreichend. Überprüfen Sie hierbei insbesondere die Programmausgaben.

Hinweis: Bitte beachten Sie dass der Scheduling-Algorithmus der JAVA-VM nicht näher spezifiziert ist. Insbesondere wird keine Fairness zugesichert.