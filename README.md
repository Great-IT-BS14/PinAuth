# PinAuth

Eigene Arduino-Bibliothek für die PIN-Eingabe eines einzelnen Benutzers.
Sie liegt direkt im Sketch und benötigt keine zusätzliche Installation.

Benutzer und PIN werden weiterhin direkt in der `.ino` festgelegt:

```cpp
#include "src/PinAuth/src/PinAuth.h"
#include <avr/pgmspace.h>

const char AUTH_USER[] = "Person01";
const char AUTH_PIN[] PROGMEM = "0001";
PinAuth auth(AUTH_USER, AUTH_PIN);
```

Der Benutzername liegt im RAM, die PIN muss als nullterminierter String im
Flash (`PROGMEM`) liegen. Beide müssen für die Lebensdauer von `auth` gültig
bleiben. Die konfigurierte PIN besteht aus einer bis sechs Ziffern;
führende Nullen gehören zur PIN.

`auth.handleKey(key)` verarbeitet bereits entprellte Tastendrücke:

- `0–9`: Ziffer hinzufügen, bis maximal sechs Ziffern eingegeben sind.
- `*`: Letzte Ziffer löschen.
- `D`: Gesamte Eingabe zurücksetzen.
- `#`: PIN prüfen; bei falscher PIN wird die Eingabe sofort geleert.
- Andere Tasten und `0` als fehlendes Tastenereignis: keine Änderung.

| Rückgabewert | Reaktion der Anwendung |
|---|---|
| `PinAuth::UNCHANGED` | Keine Anzeigeänderung nötig. |
| `PinAuth::CHANGED` | Maskierte Eingabe neu anzeigen. |
| `PinAuth::ACCEPTED` | Spiel sofort starten. |
| `PinAuth::REJECTED` | PIN-Fehler anzeigen; erneute Eingabe ist sofort möglich. |

`auth.user()` liefert den Benutzernamen, `auth.length()` die Anzahl der
anzuzeigenden PIN-Sterne. `auth.reset()` leert die Eingabe beim Neustart.
Nach erfolgreicher Prüfung wechselt die Anwendung selbst in den Spielzustand;
das Paket verarbeitet keine weiteren Spielzustände und steuert kein Display.

Es gibt keine Benutzerliste, Fehlversuchssperre oder Warteanzeige.
Die Implementierung verwendet einen festen Eingabepuffer ohne dynamische
Speicherreservierung. Die LCD-Anzeige übernimmt `DisplayMenu`.

Tests: [PIN- und Kommunikationstests](../../../tests/auth_communication/README.md).

Zum Wiederverwenden den gesamten Ordner `PinAuth` in den Arduino-
Bibliotheksordner kopieren und `#include <PinAuth.h>` verwenden.
