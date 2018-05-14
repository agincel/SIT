/*
    Adam Gincel
    mongoConnection.js

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const MongoClient = require("mongodb").MongoClient;;

const settings = {
    mongoConfig: {
        serverUrl: "mongodb://localhost:27017/",
        database: "Gincel-Adam-CS554-Lab1"
    }
};

let fullMongoUrl = settings.mongoConfig.serverUrl + settings.mongoConfig.database;
let _connection = undefined

let connectDb = () => {
    if (!_connection) {
        _connection = MongoClient.connect(fullMongoUrl)
            .then((db) => {
                return db;
            });
    }

    return _connection;
};

module.exports = connectDb;