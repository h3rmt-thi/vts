## Aufgabe (RPC)
Es soll eine Addition, Multiplikation und Quadrierung einer Zahl an einem anderen Rechner mit RPC implementiert werden.
- Verwenden Sie den folgenden Inhalt der Datei math.x zur Beschreibung der Basisdefinitionen (Datentyp, RPC-Identifikator, Versionsnummer):
    ```x
    struct intpair { int a; int b; };
    program MATHPROG {
        version MATHVERS {
            int ADD(intpair) = 1;
            int MULTIPLY(intpair) = 2;
            int CUBE(int) = 3;
        }= 1; /*version*/
    } = 0x2001000; /*id userdefined*/
    ```
    Erzeugen Sie mit dem Aufruf rpcgen math.x die Dateien: math.h math_svc.c math_clnt.c math_xdr.c.
- Erstellen Sie nun den Code für den Server. Binden Sie hierzu den lokalen Header math.h (include „math.h“) und den Systemheader rpc/rpc.h ein. Erzeugen Sie nun die dementsprechenden Serverprozeduren. Als Beispiel dient die Signatur der Prozedur zum Addieren:
  ```c
  int * add_1_svc (pair, rqstp) intpair * pair; struct svc_req *rqstp; /*not necessary in this example*/
  ```
  Die Erweiterung _1_svc wird von rpcgen generiert. Hierbei entspricht die 1 der Version. Den ersten Parameter a können Sie mit `pair->a` ansprechen. Das Binary erzeugen Sie mit folgender Anweisung: ``cc -o math_server math_svc.c math_xdr.c server.c -lnsl`` Hinweis: Es kann sein, dass das Packet tirpc an Ihrem Rechner installiert ist. In diesem Fall setzen sie beim Compilieren die Option -I/usr/include/tirpc und binden die entsprechende Bibliothek mit -ltirpc zusätzlich zu nsl ein.
- Erstellen Sie den Code für den Client. Binden Sie hierzu ebenfalls die in Aufgabe b) genannten Header ein. Interpretieren Sie die Argumente der Kommandozeile wie folgt: Das erste Argument ist der Name des Servers, das zweite und dritte Argument jeweils zwei ganze Zahlen, deren Summe berechnet werden soll. Den Zugriff auf den Server erzielen Sie durch die Verwendung eines Client-Handles cl (CLIENT * ), den Sie mit der Funktion clnt_create erzeugen: 
  ```c
  clnt_create (servername, MATHPROG, MATHVERS, "tcp");
  ```
  Die Prozedur add_1 auf dem Server rufen sie z.B. mit add_1 (&numbers, cl) auf. Hierbei ist numbers von der Sorte intpair. Das Binary erzeugen Sie mit folgender Anweisung:``cc -o remo_math math_clnt.c math_xdr.c client.c –lnsl`` Der Aufruf erfolgt dann z.B. mit:: remo_math localhost 3 4 Hinweis: Es kann sein, dass das Packet tirpc an Ihrem Rechner installiert ist. In diesem Fall setzen sie beim Compilieren die Option -I/usr/include/tirpc und binden die entsprechende Bibliothek mit -ltirpc zusätzlich zu nsl ein.
- Testen Sie das zuerst auf Ihrem Rechner, indem Sie als Server localhost verwenden. Anschließend testen Sie dann die Anwendung auf verschiedenen Rechnern. Hinweis: Vergessen Sie nicht den Server-Prozess zu starten. Es kann auch erforderlich sein, dass rpcbind zu installieren ist: ```paru -S rpcbind; sudo rpcbind```