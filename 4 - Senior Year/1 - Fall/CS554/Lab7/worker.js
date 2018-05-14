/*
    Adam Gincel
    CS554 Lab 7
    worker.js

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const redisConnection = require("./redis-connection");
const request = require("async-request");
var peopleList = null;

const apiKey = "7030730-27d32fb652129e27f4fc935bf"; //leaving this in for submit even though it's bad practice, sorry
const pixUrl = "https://pixabay.com/api/?key=" + apiKey + "&q=";
async function getImage(query) {
    var results = await request(pixUrl + query);
    return results;
}



redisConnection.on(
  "message",
  async function(data, channel) {
        console.log(data);
        var q = await getImage(data.query);
        console.log("Got response, emitting to index.");
        redisConnection.emit('messageResult', {results: q, username: data.username, message: data.message});
  }
);
