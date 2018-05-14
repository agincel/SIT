const express = require("express");
const router = express.Router();

const users = require("../data").users;

const redis = require("redis");
const client = redis.createClient();

const bluebird = require("bluebird");

//these are so convenient, lol
bluebird.promisifyAll(redis.RedisClient.prototype);
bluebird.promisifyAll(redis.Multi.prototype);

router.get("/api/people/history", async (req, res) => {
    await client.lrange("recents", 0, 19, function (err, userResults) {
        let userList = [];
        for (var i = 0; i < userResults.length; i++) {
            userList.push(JSON.parse(userResults[i]));
            console.log(userResults[i]);
        }
        res.json(userList);
    });
});

router.get("/api/people/:id", async (req, res) => {
    var userID = req.params.id;
    var doesUserExist = await client.existsAsync(userID);
    console.log("User exists? " + doesUserExist);

    if (doesUserExist) {
        var user = await client.getAsync(userID);
        await client.lpush("recents", user);
        res.status(200).json(JSON.parse(user));
    } else {
        try {
            var result = await users.getById(userID);
            await client.setAsync(userID, JSON.stringify(result));
            await client.lpush("recents", JSON.stringify(result));
            res.json(result);
        } catch (e) {
            res.status(500).json({error: "Could not retrieve user"});
        }
    }
});

module.exports = router;