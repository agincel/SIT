/*
    Adam Gincel
    index.js
    This file imports printShape, the Node.js module, and tests its methods.

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const printShape = require("./printShape");

console.log("HW2 tests, by Adam Gincel.\n\n");

//print triangles
printShape.triangle(1);
printShape.triangle(2);
printShape.triangle(3);
printShape.triangle(4);
printShape.triangle(8);

//print squares
printShape.square(2);
printShape.square(3);
printShape.square(5);
printShape.square(8);

//print rhombuses
printShape.rhombus(2);
printShape.rhombus(4);
printShape.rhombus(6);
printShape.rhombus(8);
printShape.rhombus(10);

console.log("Errors:");
try {
    printShape.triangle("error");
} catch (e) {
    console.log(e);
}

try {
    printShape.triangle(-1);
} catch (e) {
    console.log(e);
}

try {
    printShape.square("error");
} catch (e) {
    console.log(e);
}

try {
    printShape.square(-1);
} catch (e) {
    console.log(e);
}

try {
    printShape.rhombus("error");
} catch (e) {
    console.log(e);
}

try {
    printShape.rhombus(3);
} catch (e) {
    console.log(e);
}