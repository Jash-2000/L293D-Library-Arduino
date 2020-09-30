In the Schematic provided in this Folder, the 2 Motor's control has been divided into 2 sections : Left and Right side of the BreadBoad.

**General Rules** : 
1) All black wires are GND and red wires are VCC.
2) All the Yellow wires are Enable PINs, to control the speed of the Motor and are thus, analog Inputs to the IC
3) All the Brown wires are Digital Input PINs for the IC, to control the motor's Rotation direction.
4) Purple Wires are Output High for the IC (Input VCC for the Motors).
5) Blue Wires are Output low for the IC (Input GND for the Motors).

**After making the exact shown connections, match them with API paramters:**
Row 2, Right side -> ENB34
Row 3, Left side -> ENB12

Row 1, Left side ->  Inp1
Row 2, Left side -> Inp2
Row 3, right side -> Inp3
Row 4, right side -> Inp4
