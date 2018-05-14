/*
	Adam Gincel
	app.js - Checks chapters 1 - 3 and performs async read/write operations on them

	I pledge my honor that I have abided by the Stevens Honor System.
*/

const textMetrics = require("./textMetrics");
const fileData = require("./fileData");



//Chapter 1 tests
fileData.getFileAsJSON('./chapter1.result.json').then((json) => {
	console.log("Chapter 1:");
	//result already calculated
	console.log("Loading from disc:");
	console.log(json);
}).catch((error) => {
	//file didn't exist or was corrupted
	//time to read chapter 1

	let chapter = fileData.getFileAsString('./chapter1.txt');
	chapter.then((text) => {
		let simplifiedText = textMetrics.simplify(text);

		fileData.saveStringToFile('./chapter1.debug.txt', simplifiedText).catch ((error) => {
			console.log(error);
		})

		let metrics = textMetrics.createMetrics(simplifiedText);
		
		fileData.saveJSONToFile('./chapter1.result.json', metrics).catch((error) => {
			console.log(error);
		})
		console.log("Chapter 1:");
		console.log(metrics);
	})
});



//Chapter 2 tests
fileData.getFileAsJSON('./chapter2.result.json').then((json) => {
	//result already calculated
	console.log("Chapter 2:");
	console.log("Loading from disc:");
	console.log(json);
}).catch((error) => {
	//file didn't exist or was corrupted
	//time to read chapter 1

	let chapter = fileData.getFileAsString('./chapter2.txt');
	chapter.then((text) => {
		let simplifiedText = textMetrics.simplify(text);

		fileData.saveStringToFile('./chapter2.debug.txt', simplifiedText).catch ((error) => {
			console.log(error);
		})

		let metrics = textMetrics.createMetrics(simplifiedText);
		
		fileData.saveJSONToFile('./chapter2.result.json', metrics).catch((error) => {
			console.log(error);
		})
		console.log("Chapter 2:");
		console.log(metrics);
	})
});



//Chapter 3 tests
fileData.getFileAsJSON('./chapter3.result.json').then((json) => {
	//result already calculated
	console.log("Chapter 3:");
	console.log("Loading from disc:");
	console.log(json);
}).catch((error) => {
	//file didn't exist or was corrupted
	//time to read chapter 1

	let chapter = fileData.getFileAsString('./chapter3.txt');
	chapter.then((text) => {
		let simplifiedText = textMetrics.simplify(text);

		fileData.saveStringToFile('./chapter3.debug.txt', simplifiedText).catch ((error) => {
			console.log(error);
		})

		let metrics = textMetrics.createMetrics(simplifiedText);
		
		fileData.saveJSONToFile('./chapter3.result.json', metrics).catch((error) => {
			console.log(error);
		})
		console.log("Chapter 3:");
		console.log(metrics);
	})
});
