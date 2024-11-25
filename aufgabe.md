## Aufgabe (RMI – Systemzeit-Server)

Es soll nun eine einfacher Systemzeit-Dienst erzeugt werden, der sich die Systemzeit eines Servers von diesem holt. Der Client und der Server sind auf verschiedenen Maschinen lokalisiert (beim ersten Versuch auf der gleichen Maschine localhost). Zudem soll noch die Zeit des Clients beim Start und am Ende ausgegeben werden.

Eine Ausgabe könnte z.B. sein:

```
C:\data\aktuelle_Vorlesungen\verteilte_systeme_ws1920\uebunge n_vss\blatt5\Aufgabe_1>java -cp bin DaytimeClient localhost Local starttime is 2019-08-19T18:31:44.888 Received time is 2019-08-19T18:31:45.387 Local endtime is 2019-08-19T18:31:45.388
```

**Gehen Sie ähnlich zum Beispiel zur Vorlesung Kapitel IV.4 vor.**

- Erstellen Sie die passenden Dateien: `Daytime.java DaytimeImpl.java DaytimeServer.java DaytimeClient.java`
- Kopieren Sie die Sicherheitsregeln (Datei policy.txt) in das Projekt-Verzeichnis.
- Unter LINUX rufen Sie rmiregistry direkt auf.
- Starten Sie den DaytimeServer Hinweis: Es kann nötig sein, dass sie den Classpath für zu implementierende Klasse durch eine VM-Konfiguration –Djava.rmi.server.codebase=“file:<pfad zu class files>“ oder die Option –cp bin angeben müssen.
- Starten Sie den DaytimeClient mit dem Argument localhost
- Lassen Sie dann den Client und den Server auf verschieden Rechnern laufen. Hinweis: Falls Sie Server und Client auf verschiedenen Rechnern installieren wollen, müssen Sie bei der Virtualbox die Option Netzwerkbrücke (networkbridge) aktivieren. Somit erhalten Sie eine von außen zugängliche Netzwerkadresse. Achtung: Bei einem Zugriff im Rechnerpool der THI per WLAN greifen Sicherheitsmechanismen und sie können nicht RMI zwischen mit WLAN verbundenen Rechnern starten.

Hinweis: Wenn Sie auf mehreren Rechnern das Beispiel ablaufen lassen, kann es erforderlich sein, dass Sie den Server mit java -Djava.rmi.server.hostname=<IP des Serverrechners> DaytimeServer starten. Also damit die IP-Adresse des eigenen rechners bekannt machen.