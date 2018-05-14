/*
    Adam Gincel
    CS554 Lab 6
    routes/index.js
*/

const express = require("express");

const bodyParser = require("body-parser");
const redisConnection = require("../redis-connection");
var app = express();

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());

app.get("/api/people/:id", async (req, res) => {
    var personID = req.params.id;
    redisConnection.emit("getPerson", {id: personID});
    redisConnection.on("getPersonResults", (data, channel) => {
        console.log(data);
        if (data.error)
            res.status(500).json(data);
        else
            res.status(200).json(data);
    });
});

app.post("/api/people", async (req, res) => {
    if (req.body && req.body.first_name && req.body.last_name && req.body.email && req.body.gender && req.body.ip_address) {
        redisConnection.emit("postPerson", req.body);
        redisConnection.on("postPersonResults", (data, channel) => {
            console.log(data);
            res.status(200).json(data);
        });
    } else {
        res.json({error: "Please post a JSON object with fields first_name, last_name, email, gender, and ip_address"});
    }
});

app.delete("/api/people/:id", async (req, res) => {
    var personID = req.params.id;
    redisConnection.emit("deletePerson", {id: personID});
    redisConnection.on("deletePersonResults", (data, channel) => {
        console.log(data);
        if (data.error)
            res.status(500).json(data);
        else
            res.status(200).json(data);
    })
});

app.put("/api/people/:id", async (req, res) => {
    var personID = req.params.id;
    if (req.body && (req.body.first_name || req.body.last_name || req.body.email || req.body.gender || req.body.ip_address)) {
        redisConnection.emit("putPerson", {id: personID, body: req.body});
        redisConnection.on("putPersonResults", (data, channel) => {
            console.log(data);
            if (data.error) {
                res.status(500).json(data);
            } else {
                res.status(200).json(data);
            }
        })
    } else {
        res.status(500).json({error: "Please PUT with first_name, last_name, email, gender, and/or ip_address"});
    }
})

module.exports = app;