/*
    Adam Gincel
    Lab 6

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const recipesRoute = require("./recipes");
const commentsRoute = require("./comments");

const getRecipes = require("./recipes");

const constructorMethod = (app) => {
    app.use("/recipes", getRecipes);
    app.use("/comments", commentsRoute);


    app.use("*", (req, res) => {
        res.status(404).json({error: "Not Found"});
    });

};

module.exports = constructorMethod;