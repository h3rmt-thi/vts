## Aufgabe (threads in JAVA)

Im Folgenden soll ein typisches Schreiber/Leser-Problem realisiert werden. Verwenden Sie als Ausgangsbasis die jeweils angegebenen Module. Es soll eine Schachfigur auf der Hauptdiagonalen wahlfrei zufällig verschoben werden. Hierzu werden zwei Threads zum Schreiben und auch zum Lesen der Position realisiert. Verwenden Sie als Grundlage zum Erzeugen der Threads hierzu die Vorlesung, Kapitel II.3. Anmerkung: In den ersten Teilaufgaben erfolgt keine Synchronisation der Prozesse.

Gehen Sie hierbei wie folgt schrittweise vor.

- Verwenden Sie die vorgegebenen Klassen Figur, Schreiber, Leser und MachMal. Erweitern Sie die Klasse Figur indem Sie die Methoden setPosition und getPosition (gibt die Position an stdout aus) in einer getrennten Klasse implementieren. Verwenden Sie hierbei Vererbung. Beim Setzen der Position bauen Sie eine Verzögerung von einer Zehntelsekunde (MachMal.eineZehntelSekundeLangGarNichts()) zwischen dem Belegen des X-Wertes und des Y-Wertes ein. Damit die Effekte auch beobachtbar sind, ergänzen Sie auch die Methode getPosition mit einer Verzögerung von einer Sekunde. Erstellen Sie nun die Klasse FigurenThreads, in der jeweils der Leser und der Schreiber gestartet werden. Achten Sie darauf, dass die Lese- und auch die Schreib-Threads im Hintergrund laufen. Dies erreicht man durch setDaemon(true)
- Starten Sie das Programm und interpretieren Sie die Ausgaben. Was ist die Erklärung für dieses Verhalten?
- Synchronisieren Sie die Module.