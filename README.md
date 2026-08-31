Bauen und ausführen im JupyterHub:

1. Im Terminal in den Ordner wie auch immer unser Ordern heißt navigieren
2. Nur beim ersten Mal: mit den Befehlen `make getSFML` und `make getGTest` die nötigen Ressourcen herunterladen
3. Das Spiel und die Tests bauen: `make game` und `make tests`
4. Das Speil und/oder die Tests ausführen  (in der Konsole, nicht in VSCode oder dem Terminal!!!!)

Steuerung:
Die Spielfigur wird mit `d` nach rechts und `a` nach links gesteuert. Mit `w` springt man und mit `c` klettert man Leitern nach oben sofern man mit mindesten der Hälfte des Körpers über der Leiter steht.

Spielablauf:

Zu Beginn des Spiels muss man mit 1-3 einen Spielmodi auswählen. Startet das Spiel muss man versuchen mit der Spielfigur die Plattform am oberen Ende auf der eine Fahne steht zu erreichen. Erreicht man die Plattform beginnt das Spiel von vorne und die Fässer spawnen etwas schneller. Leitern können nur nach oben geklettert werden und man kann die Plattformen auch nur über die Leitern wechseln. Sollte man auf dem Weg nache oben von einem Gegner oder Fass getroffen werden ist da Spiel sofort beendet. Man hat jetzt die Wahl im gleichen Modus das Spiel fortzuführen und von vorne anzufangen oder den Modus zu wechseln; Startet das Spiel neu wird die Spwangeschwindigkeit wieder auf den ursprünglichen Wert zurückgesetzt.
