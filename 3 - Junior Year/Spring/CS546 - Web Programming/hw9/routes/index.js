/*
    Adam Gincel
    Lab 9

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const path = require("path");
const router = require("express").Router();

const loginRoutes = require("./loginRoutes");

const constructorMethod = (app) => {
    app.use("/", loginRoutes);
};

module.exports = constructorMethod;