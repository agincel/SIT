// Adam Gincel
// lab1.js
// Implementing various JavaScript functions.
// I pledge my honor that I have abided by the Stevens Honor System.


//returns the sum of the squares of 3 numbers
function sumOfSquares(num1, num2, num3) {
	if (typeof num1 == "number" && typeof num2 == "number" && typeof num3 == "number")
		return (num1 * num1) + (num2 * num2) + (num3 * num3);
	else {
		throw "Type error. Usage: sumOfSquares(number, number, number)";
	}
}

//says hello to a given person, with optional last name and title parameters
function sayHelloTo(firstName, lastName = "", title = "") {
	if (firstName == undefined) {
		throw "No arguments defined. Usage: sayHelloTo(string[, string, string])";
	}
	else if (typeof firstName != "string" || typeof lastName != "string" || typeof title != "string") {
		throw "Type error. Usage: sayHelloTo(string[, string, string])";
	}
	else {
		if (lastName == "" && title == "") {
			//only first name
			console.log("Hello, " + firstName + "!");
		} else if (title == "") {
			//first and last name
			console.log("Hello, " + firstName + " " + lastName + ". I hope you are having a good day!");
		} else {
			console.log("Hello, " + title + " " + firstName + " " + lastName + "! Have a good evening!");
		}
	}
}

//prints the lyrics to the song "99 Cups of Coffee on the Desk" starting at the given integer
function cupsOfCoffee(howManyCups) {
	if (typeof howManyCups != "number") {
		throw "Type error. Usage: cupsOfCoffee(number)";
	} else if (howManyCups <= 0) {
		throw "Out of range error. Please call with an integer >= 1.";
	}

	for (var i = howManyCups; i > 0; i--) {
		if (i == 2) {
			console.log("" + i + " cups of coffee on the desk! " + i + " cups of coffee!");
			console.log("Pick one up, drink the cup, " + (i - 1) + " cup of coffee on the desk!\n");
		} else if (i == 1) {
			console.log("" + i + " cup of coffee on the desk! " + i + " cup of coffee!");
			console.log("Pick it up, drink the cup, no more coffee left on the desk!");
		} else {
			console.log("" + i + " cups of coffee on the desk! " + i + " cups of coffee!");
			console.log("Pick one up, drink the cup, " + (i - 1) + " cups of coffee on the desk!\n");
		}
	}
}

//returns the number of times a substring appears in a string, accounting for overlap
function occurrencesOfSubstring(fullString, substring) {
	if (typeof fullString != "string" || typeof substring != "string") {
		throw "Type error. Usage: occurrencesOfSubstring(string, string)";
	}

	let searchingString = fullString;
	let count = 0;
	while(searchingString.search(substring) != -1) {
		count += 1;
		searchingString = searchingString.slice(searchingString.search(substring) + 1);
	}

	return count;
}


//helper function that shuffles an array
function shuffle (arr) {
	var i = 0, j = 0, temp = 0;

	for (i = arr.length - 1; i > 0; i -= 1) {
		j = Math.floor(Math.random() * (i + 1));
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	} 

	return arr; //technically redundant, as this shuffles the array in place
}

function randomizeSentences(paragraph) {
	if (typeof paragraph != "string") {
		throw "Type error. Usage: randomizeSentences(string)";
	}

	var sentences = paragraph.match(/[^\.!\?]+[\.!\?]+/g); //splits into array preserving punctuation
	var ret = "";
	sentences = shuffle(sentences); //randomize the sentences



	for (var i = 0; i < sentences.length; i++) {
		if (sentences[i].substr(0, 1) == " ") { //ignore first space 
			ret += sentences[i].substr(1) + " ";
		} else {
			ret += sentences[i] + " ";
		}
	}

	console.log(ret);
}






//--------------------------------------------------------------------------------------------------method tests

console.log("\nLab 1, by Adam Gincel:\n\n---------------------------------------------")


console.log("sumOfSquares tests:");
console.log(sumOfSquares(10, 5, 3));
console.log(sumOfSquares(1, 2, 3));
console.log("Calling sumOfSquares(\"hello\", 2, 3), should throw an error");
try {
	console.log(sumOfSquares("hello", 2, 3));
} catch (e) {
	console.log(e);
}

console.log("---------------------------------------------\nsayHelloTo tests:")
sayHelloTo("Adam");
sayHelloTo("Adam", "Gincel");
sayHelloTo("Adam", "Gincel", "Mr.");
console.log("Throwing errors:")
try {
	sayHelloTo(1, "2"); //should throw error
} catch(e) {
	console.log(e);
}

try {
	sayHelloTo(); //should throw error
} catch(e) {
	console.log(e);
}

console.log("---------------------------------------------\ncupsOfCoffee test:\ncall with string:");
try {
	cupsOfCoffee("hi");
} catch(e) {
	console.log(e);
}

console.log("Call with -1");
try {
	cupsOfCoffee(-1);
} catch(e) {
	console.log(e);
}

console.log("Call with 10:");
cupsOfCoffee(10);

console.log("---------------------------------------------\noccurencesInSubstring tests:\nShould print 2:");
console.log(occurrencesOfSubstring("hello world", "o")) //should print 2

console.log("Should print 6:");
console.log(occurrencesOfSubstring("Helllllllo, class!", "ll")); //should print 6

console.log("Should print 0:");

console.log("Should be a type error:");
try {
	occurrencesOfSubstring(1, 1); //not strings
} catch (e) {
	console.log(e);
}

var paragraph = "Hello, world! I am a paragraph. You can tell that I am a paragraph because there are multiple sentences that are split up by punctuation marks. Grammar can be funny, so I will only put in paragraphs with periods, exclamation marks, and question marks -- no quotations.";
console.log("---------------------------------------------\nrandomizeSentences tests:");
randomizeSentences(paragraph);

console.log("Next line should be a type error:");
try {
	randomizeSentences(1);
} catch(e) {
	console.log(e);
}

console.log("\n");

var paragraphTwo = "That is the end of this assignment. This was a good refresher into the world of JavaScript. Thank you!";
randomizeSentences(paragraphTwo);


console.log("---------------------------------------------\n\nAll done!\n");
