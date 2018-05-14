/*
    Adam Gincel
    Lab 6

    I pledge my honor that I have abided by the Stevens Honor System.
*/

//mongo stuff
const recipeItems = require("./recipe");
const connection = require("./mongoConnection");



//express stuff
const express = require("express");
const bodyParser = require("body-parser");
let app = express();
let configRoutes = require("./routes");


app.use(bodyParser.json());
configRoutes(app);

app.listen(3000, () => {
    console.log("Server is up and running!");
    console.log("Check it out at http://localhost:3000");
});

