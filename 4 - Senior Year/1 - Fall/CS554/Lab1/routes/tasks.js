/*
    Adam Gincel
    Lab 1
    tasks.js

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const taskData = require("../task");

const express = require("express");
const router = express.Router();

let urlDict = {};
function logInfo(body, route) {
    let actualPath = "/api/tasks" + route.path;
    console.log("\n\n----------------------- New request!");
    console.log("Body:");
    console.log(body);
    console.log("Route: " + actualPath);
    console.log("HTTP verb: " + route.stack[0].method.toUpperCase());
    
    if (urlDict[actualPath]) {
        urlDict[actualPath] += 1;
    } else {
        urlDict[actualPath] = 1;
    }
    console.log(actualPath + " has been accessed " + urlDict[actualPath] + " times.");
}

router.get('/', function(req, res) { //route: GET /api/tasks
    /*
        Shows a list of tasks. By default, it will show the first 20 tasks in the collection. 
        If a querystring variable ?skip=n is provided, you will skip the first n tasks. 
        If a querystring variable ?take=y is provided, it will show y number of results. 
        By default, the route will show up to 20 tasks; at most, it will show 100 tasks.
    */
    logInfo(req.body, req.route);
    taskData.getAllTasks().then((taskList) => {
        let returnedTasks = [];
        let skip = 0;
        let numTasks = 20;

        if (req.query && req.query.skip) {
            skip = req.query.skip;
            if (skip < 0)
                skip = 0;
        }
        if (req.query && req.query.take) {
            numTasks = req.query.take;
            if (numTasks > 100)
                numTasks = 100;
            if (numTasks <= 0)
                numTasks = 20; //just return default if they give weird input
        }

        for (let i = skip; i < skip + numTasks && i < taskList.length; i++) {
            returnedTasks.push(taskList[i]);
        }
        res.json(returnedTasks);
    }, () => {
        res.sendStatus(500).json({error: "lol"}); //something went wrong server-side
    });
});

router.post('/', function(req, res) { //route: POST /api/tasks
    let postedData = req.body;
    logInfo(req.body, req.route);
    taskData.createTask(postedData.title, postedData.description, postedData.hoursEstimated, postedData.completed).then((newTask) => {
        res.json(newTask);
    }, () => {
        res.sendStatus(500);
    });
});

router.get('/:id', function(req, res) { //route: GET /api/tasks/:id
    logInfo(req.body, req.route);
    taskData.getTask(req.params.id).then((foundTask) => {
        if (foundTask)
            res.json(foundTask);
        else   
            res.status(404).json({error: "Task not found"});
    }, () => {
        res.status(404).json({error: "Task not found"});
    });
});

router.put('/:id', function(req, res) { //route: PUT /api/tasks/:id | update ID, require all details
    let postedData = req.body;
    logInfo(req.body, req.route);
    if (postedData.title && postedData.description && postedData.hoursEstimated && (postedData.completed === false || postedData.completed === true)) {
        taskData.updateTask(req.params.id, postedData.title, postedData.description, postedData.hoursEstimated, postedData.completed).then((updatedTask) => {
            res.json(updatedTask);
        }, () => {
            res.sendStatus(500);
        });
    } else {
        res.sendStatus(500);
    }
});

router.patch('/:id', function(req, res) { //route: PATCH /api/tasks/:id | update ID, only return what was changed
    let postedData = req.body;
    logInfo(req.body, req.route);
    if (postedData.title || postedData.description || postedData.hoursEstimated || (postedData.completed === false || postedData.completed === true)) { //at least one should exist
        taskData.updateTask(req.params.id, postedData.title, postedData.description, postedData.hoursEstimated, postedData.completed).then((updatedTask) => {
            let returnedObject = {};
            if (postedData.title) //conditionally populate the object
                returnedObject.title = updatedTask.title;
            if (postedData.description)
                returnedObject.description = updatedTask.description;
            if (postedData.hoursEstimated)
                returnedObject.hoursEstimated = updatedTask.hoursEstimated;
            if (postedData.completed === false || postedData.completed === true)
                returnedObject.completed = updatedTask.completed;
            
            res.json(returnedObject);
        }, () => {
            res.sendStatus(500);
        });
    } else {
        res.sendStatus(500);
    }
});

router.delete('/:id', function(req, res) {
    logInfo(req.body, req.route);
    taskData.removeTask(req.params.id).then(() => {
        res.json({message: "Task deleted successfully"});
    }, () => {
        res.sendStatus(500);
    });
});

router.post("/:id/comments", function(req, res) {
    logInfo(req.body, req.route);
    taskData.addComment(req.params.id, req.body.name, req.body.comment).then((newComment) => {
        res.json(newComment);
    }, () => {
        res.sendStatus(500);
    });

});

router.delete('/:taskId/:commentId', function(req, res) {
    logInfo(req.body, req.route);
    taskData.getTask(req.params.taskId).then((task) => {
        let hasFoundComment = false;
        for(var i = 0; i < task.comments.length && !hasFoundComment; i++) {
            if (task.comments[i]._id == req.params.commentId) {
                hasFoundComment = true;
                break;
            }
        }
        if (!hasFoundComment) {
            res.status(404).json({error: "Could not find comment with that ID"});
        } else {
            taskData.removeComment(req.params.taskId, req.params.commentId).then((message) => {
                console.log("success");
                res.json({message: "Comment removed successfully."});
            }, () => {
                res.sendStatus(500);
            })
        }
    });
});




module.exports = router;