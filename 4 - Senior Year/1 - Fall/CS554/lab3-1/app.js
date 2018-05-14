const express = require("express");
const bodyParser = require("body-parser");
const path = require('path');

const app = express();
const static = express.static(__dirname + "/public");

app.use("/public", static); //define what server directory applies to the /public folder

app.use("/", (req, res) => {
    res.sendFile(path.join(__dirname+'/public/index.html'));
});
app.use("*", (req, res) => {
	res.status(404);
});
app.listen(3000, () => {
    console.log("Server is up and running at http://localhost:3000");
});