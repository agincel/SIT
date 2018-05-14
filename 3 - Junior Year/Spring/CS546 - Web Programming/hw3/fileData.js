const fs = require('fs');

let fileData = exports = module.exports;

fileData.getFileAsString = (path) => {
	return new Promise((fulfill, reject) => {
		if (!path) 
			throw "No file path provided.";

		fs.readFile(path, "utf-8", (error, data) => {
			if (error) { //reject the promise and cease execution if there was an error reading
				reject(error);
				return;
			}

			//we are reading the utf-8 string in with no parsing
			//if we made it here, we have what we need
			fulfill(data);
		});
	})
};

fileData.getFileAsJSON = (path) => {
	return new Promise((fulfill, reject) => {
		if (!path)
			throw "No file path provided.";

		fs.readFile(path, "utf-8", (error, data) => {
			if (error) {
				reject(error);
				return;
			}

			try {
				let parsedJson = JSON.parse(data);
				fulfill(parsedJson);
			} catch (parsingError) {
				reject(parsingError);
			}
		});
	})
};

fileData.saveStringToFile = (path, text) => {
	return new Promise ((fulfill, reject) => {
		if (!path || !text)
			throw "Missing path or text.";

		fs.writeFile(path, text, "utf-8", (error) => {
			if (error) {
				reject(error);
				return;
			}

			fulfill(true);
		});
	})
};

fileData.saveJSONToFile = (path, obj) => {
	return new Promise ((fulfill, reject) => {
		if (!path || !obj)
			throw "Missing path or object.";

		fs.writeFile(path, JSON.stringify(obj), "utf-8", (error) => {
			if (error) {
				reject(error);
				return;
			}

			fulfill(true);
		});
	})
};

