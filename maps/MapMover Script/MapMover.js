/*
 * Dies ist eine JavaScript-Umgebung.
 *
 * Geben Sie etwas JavaScript ein und führen Sie einen Rechtsklick aus oder wählen Sie aus dem Ausführen-Menü:
 * 1. Ausführen, um den ausgewählten Text zu evaluieren (Strg+R),
 * 2. Untersuchen, um den Objekt-Inspektor auf das Resultat anzuwenden (Strg+I), oder
 * 3. Anzeigen, um das Ergebnis in einem Kommentar hinter der Auswahl einzufügen. (Strg+L)
 */

var map = document.getElementById('content').innerHTML;
var coords = map.match(/(-)?\d+ (-)?\d+/gi);
alert(coords);
var move = [2250, 2000];
for (var i = 0; i < coords.length; i++) {
  if (coords[i] == "0 0") continue;
  var newCoords = [0, 0];
  curCoords = coords[i].split(' ');
  newCoords[0] = Number(curCoords[0]) - (move[0] * -1);
  newCoords[1] = Number(curCoords[1]) - (move[1] * -1);
  
  map = map.replace(coords[i], newCoords[0] + " " + newCoords[1]);
}

document.getElementById('content').innerHTML = map;