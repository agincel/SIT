/*
    Adam Gincel
    Lab 6

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const express = require("express");
let app = express();
let configRoutes = require("./routes");

configRoutes(app);

app.listen(3000, () => {
    console.log("Server is up and running!");
    console.log("Check it out at http://localhost:3000");
});

