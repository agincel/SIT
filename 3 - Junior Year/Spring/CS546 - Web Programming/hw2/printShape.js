/*
    Adam Gincel
    printShape.js
    This is a Node module with 3 methods: triangle, square, and rhombus.

    I pledge my honor that I have abided by the Stevens Honor System.
*/

module.exports = {
	triangle: 
		function(lines) {
			var ret = "";

			var temp = lines;

			if (typeof lines != "number") {
				throw "Type error. USAGE: triangle(number)";
			}

			if (lines <= 0) {
				throw "Please call triangle() with a number >= 1"
			}

			//print top
			var printingLine = "";
			for (var i = 0; i < lines - 1; i++)
				printingLine += " ";
			printingLine += "/\\";

			temp -= 1;
			ret += printingLine + "\n";

			while (temp > 1) { //draw middle
				printingLine = "";
				for (var i = 0; i < temp - 1; i++) {
					printingLine += " ";
				}
				printingLine += "/";
				for (var i = 0; i < ((lines - temp) * 2); i++) {
					printingLine += " ";
				}
				printingLine += "\\";

				ret += printingLine + "\n";

				temp -= 1;
			}

			if (temp > 0) {
				printingLine = "";
				printingLine += "/";
				for (var i = 0; i < ((lines - 1) * 2); i++) {
					printingLine += "-";
				}
				printingLine += "\\";

				ret += printingLine + "\n";
			}

			console.log(ret);
		},
	square: 
		function(lines) {
			var ret = "";
				var temp = lines;

				if (typeof lines != "number") {
					throw "Type error. USAGE: square(number)";
				}

				if (lines <= 1) {
					throw "Please call square() with a number >= 2";
				}

				//print top
				var printingLine = "|";
				for(var i = 0; i < lines; i++) {
					printingLine += "-";
				}
				printingLine += "|";
				ret += printingLine + "\n";
				temp -= 1;

				//print middle
				while (temp > 1) {
					printingLine = "|";
					for (var i = 0; i < lines; i++) {
						printingLine += " ";
					}
					printingLine += "|";
					ret += printingLine + "\n";
					temp -= 1;
				}

				//print bottom
				var printingLine = "|";
				for(var i = 0; i < lines; i++) {
					printingLine += "-";
				}
				printingLine += "|";
				ret += printingLine + "\n";
				
				console.log(ret);
		},
	rhombus:
		function(lines) {
				var ret = "";

				if (typeof lines != "number") {
					throw "Type error. USAGE: rhombus(number)";
				}

				if (lines <= 1 || lines % 2 != 0) {
					throw "Please call rhombus() with an even number >= 2";
				}

				tempA = 1;
				tempB = (lines / 2) - 1;

				//print top
				var printingLine = "";
				for(var i = 0; i < (lines / 2) - 1; i++) {
					printingLine += " ";
				}
				printingLine += "/-\\";
				ret += printingLine + "\n";

				//print top mid
				while (tempA < lines / 2) {
					printingLine = "";
					for (var i = 0; i < (lines / 2) - tempA - 1; i++) {
						printingLine += " ";
					}
					printingLine += "/";
					for (var i = 0; i < (tempA * 2) + 1; i++) {
						printingLine += " ";
					}
					printingLine += "\\";
					tempA += 1;
					ret += printingLine + "\n";
				}


				//print bottom mid
				while (tempB > 0) {
					printingLine = "";
					for (var i = 0; i < (lines / 2) - tempB - 1; i++) {
						printingLine += " ";
					}
					printingLine += "\\";
					for (var i = 0; i < (tempB * 2) + 1; i++) {
						printingLine += " ";
					}
					printingLine += "/";
					tempB -= 1;
					ret += printingLine + "\n";
				}

				//print bottom
				var printingLine = "";
				for(var i = 0; i < (lines / 2) - 1; i++) {
					printingLine += " ";
				}
				printingLine += "\\-/";
				ret += printingLine + "\n";

				console.log(ret);
		}
};


