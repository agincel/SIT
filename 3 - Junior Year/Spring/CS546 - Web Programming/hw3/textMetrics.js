let textMetrics = exports = module.exports;

textMetrics.simplify = (text) => {
	text = text.toLowerCase();
	parsedText = "";

	let alphanumeric = /^[a-z0-9]+$/i;
	for (var i = 0; i < text.length; i++) {
		if (alphanumeric.test(text[i])) {
			parsedText += text[i];
		} else if (text[i] == " " || text[i] == "\n" || text[i] == "\t") {
			parsedText += " ";
		}
	}

	return parsedText;
};

textMetrics.createMetrics = (text) => {

	wordArray = textMetrics.simplify(text).split(" "); //guarantees it's simplified

	let ret = {};


	ret.wordOccurences = {};
	for (var i = 0; i < wordArray.length; i++) {
		if (ret.wordOccurences[wordArray[i]] === undefined) {
			ret.wordOccurences[wordArray[i]] = 1;
		} else {
			ret.wordOccurences[wordArray[i]] += 1;
		}
	}

	ret.totalLetters = 0;
	ret.totalWords = 0;
	ret.uniqueWords = 0;
	ret.longWords = 0;
	ret.averageWordLength = 0;

	for (var key in ret.wordOccurences) { //go through dictionary, find some data
		ret.totalLetters += ret.wordOccurences[key] * key.length;
		ret.totalWords += ret.wordOccurences[key];
		ret.uniqueWords += 1;
		if (key.length >= 6)
			ret.longWords += 1;
	}

	ret.averageWordLength = ret.totalLetters / ret.totalWords;

	return ret;

};