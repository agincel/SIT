/*
    Adam Gincel
    CS554 Lab 7
    index.js

    I pledge my honor that I have abided by the Stevens Honor System.
*/

var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

const redisConnection = require("./redis-connection");

app.get("/", function (req, res) {
    res.sendFile(__dirname + "/index.html");
});

io.on('connection', function(socket) {
    console.log("We have a new user!");

    socket.on('message', function(arg) {
        console.log(arg);
        var query = arg.query;
        while (query.indexOf(" ") != -1) {
            query.replace(" ", "+");
        }
        arg.query = query;
        redisConnection.emit('message', arg);
    });

    redisConnection.on('messageResult', function (ret, channel) {
        var body = JSON.parse(ret.results.body);
        var links = [];
        for (var i = 0; i < body.hits.length; i++) {
            links.push(body.hits[i].previewURL);
        }
        console.log("Emitting to sockets.");
        io.emit("images", {links: links, username: ret.username, message: ret.message});
    });

    socket.on('disconnect', function() {
        console.log("User disconnected.");
    });

});

http.listen(3000, function() {
    console.log("Listening on port 3000");
});