/*
    Adam Gincel
    CS554 Lab 7
    redis-connection.js
*/

const NRP = require("node-redis-pubsub");
const config = {
  port: 6379, // Port of your locally running Redis server
  scope: "downloader" // Use a scope to prevent two NRPs from sharing messages
};

const nrp = new NRP(config); // This is the NRP client

module.exports = nrp;