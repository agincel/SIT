/*
    Adam Gincel
    CS554 Lab 6
    worker.js
*/

const redisConnection = require("./redis-connection");
const request = require("async-request");
var peopleList = null;

redisConnection.on(
  "showResults",
  (data, channel) => {
    const sendResults = () => {
      if (computedResults === null) {
        setTimeout(sendResults, 5000);
      } else {
        redisConnection.emit("results-completed", { results: computedResults });
      }
    };

    sendResults();
  }
);

redisConnection.on("getPerson", (data, channel) => {
    console.log(data);
    if (peopleList == null) {
        redisConnection.emit("getPersonResults", {error: "Worker did not have a peopleList defined."});
    } else {
        data.id = data.id < 0 ? data.id * -1 : data.id; //if id is negative, just made ID positive
        var foundID = false;
        for (var i = 0; i < peopleList.length; i++) {
            if (peopleList[i].id == data.id) {
                foundID = true;
                break;
            }
        }
        if (!foundID) {
            redisConnection.emit("getPersonResults", {error: "Worker could not find a Person with that ID."});
        } else {
            let person = null;
            for(var i = 0; i < peopleList.length; i++) {
                if (peopleList[i].id == data.id) 
                    person = peopleList[i];
            }
            console.log("Found person: ");
            console.log(person);
            redisConnection.emit("getPersonResults", person);
        }
    }
});

redisConnection.on("postPerson", (data, channel) => {
    if (peopleList == null)
        redisConnection.emit("postPersonResults", {error: "Worker did not have a peopleList defined."});
    else {
        console.log(data);
        var person = {};
        person.id = peopleList.length + 1;
        person.first_name = data.first_name;
        person.last_name = data.last_name;
        person.email = data.email;
        person.gender = data.gender;
        person.ip_address = data.ip_address;
        peopleList.push(person);
        redisConnection.emit("postPersonResults", person);
    }
});

redisConnection.on("deletePerson", (data, channel) => {
    if (peopleList == null)
        redisConnection.emit("deletePersonResults", {error: "Worker did not have a peopleList defined."});
    else {
        data.id = data.id < 0 ? data.id * -1 : data.id; //if id is negative, just made ID positive
        var foundID = false;
        for (var i = 0; i < peopleList.length; i++) {
            if (peopleList[i].id == data.id) {
                foundID = true;
                break;
            }
        }
        if (!foundID) {
            redisConnection.emit("deletePersonResults", {error: "Worker could not find a Person with that ID."});
        } else {
            var deleted = null;
            for (var i = 0; i < peopleList.length; i++) {
                if (peopleList[i].id == data.id) {
                    deleted = peopleList[i];
                    peopleList.splice(i, 1);
                }
            }
            redisConnection.emit("deletePersonResults", {message: "Worker has successfully removed " + deleted.first_name + " " + deleted.last_name + " (ID: " + data.id + ")"});
        }
    }
});

redisConnection.on("putPerson", (data, channel) => {
    if (peopleList == null)
        redisConnection.emit("putPersonResults", {error: "Worker did not have a peopleList defined."});
    else {
        data.id = data.id < 0 ? data.id * -1 : data.id; //if id is negative, just made ID positive
        var foundID = false;
        for (var i = 0; i < peopleList.length; i++) {
            if (peopleList[i].id == data.id) {
                foundID = true;
                break;
            }
        }

        if (!foundID) {
            redisConnection.emit("putPersonResults", {error: "Worker could not find a Person with that ID."});
        } else {
            var person = null;
            for (var i = 0; i < peopleList.length; i++) {
                if (peopleList[i].id == data.id) {
                    if (data.body.first_name) 
                        peopleList[i].first_name = data.body.first_name;
                    if (data.body.last_name)
                        peopleList[i].last_name = data.body.last_name;
                    if (data.body.email)
                        peopleList[i].email = data.body.email;
                    if (data.body.gender)
                        peopleList[i].gender = data.body.gender;
                    if (data.body.ip_address)
                        peopleList[i].ip_address = data.body.ip_address;
                    person = peopleList[i];
                    break;
                }
            }

            redisConnection.emit("putPersonResults", person);
        }
    }
});

//Loat peopleList on init
const gistUrl = "https://gist.githubusercontent.com/philbarresi/5cf15393d245b38a2d86ce8207d5076c/raw/d529fb474c1af347702ca4d7b992256237fa2819/lab5.json";
async function loadInfo() {
    var res = await request(gistUrl);
    peopleList = JSON.parse(res.body);

    console.log("Worker: Successfully loaded " + peopleList.length + " people.");
}
loadInfo();