/*
    Adam Gincel
    Lab 6

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const aboutRoute = require("./about");
const storyRoute = require("./story");
const educationRoute = require("./education");

const constructorMethod = (app) => {
    app.use("/about", aboutRoute);
    app.use("/story", storyRoute);
    app.use("/education", educationRoute);

    app.use("*", (req, res) => {
        res.status(404).json({error: "Not Found"});
    });

};

module.exports = constructorMethod;