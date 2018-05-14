/*
    Adam Gincel
    Lab 1
    index.js

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const tasksRoute = require("./tasks");

let urlDict = {};

const constructorMethod = (app) => {

    //middleware moved to tasks.js due to req.route not populating until after route matching. Might change or revert later.
    /*app.use("*", (req, res, next) => {
        //console.log(req);
        console.log(req.body);
        console.log(req.originalUrl);
        next();
    });

    app.use(function(req, res, next) {
        /*if (urlDict[req.route.path]) {
            urlDict[req.route.path] += 1;
        } else {
            urlDict[req.route.path] = 1;
        }
        console.log(req.route.path + " has been accessed " + urlDict[req.route.path] + " times.");
        next();
    })*/

    app.use("/api/tasks", tasksRoute);
    app.use("*", (req, res) => {
        res.status(404).json({error: "Not Found"});
    });

};

module.exports = constructorMethod;