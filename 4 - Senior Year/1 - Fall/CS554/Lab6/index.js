/*
    Adam Gincel
    CS554 Lab 6
    index.js
*/

const express = require("express");
const app = express();
const routes = require("./routes");

app.use("/", routes);

app.get("*", (req, res) => {
    res.json({error: "404 not found"});
})

app.listen(3000, () => {
    console.log("Server is running on http://localhost:3000");
});