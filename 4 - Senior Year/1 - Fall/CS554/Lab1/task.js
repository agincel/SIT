/*
    Adam Gincel
    task.js
    Defines the taskItems mongoCollections

    I pledge my honor that I have abided by the Stevens Honor System.
*/ 


const mongoCollections = require("./mongoCollections");
const taskItems = mongoCollections.taskItems;
const uuidV4 = require("uuid/V4");

let exportedMethods = {
    getTask(id) {
        if (!id) 
            return Promise.reject("You must provide an id to search for");
        
        return taskItems().then((taskCollection) => {
            return taskCollection.findOne({_id: id});
        }).catch((error) => {
            return Promise.reject(error);  
        });
    },
    getAllTasks() {
        return taskItems().then((taskCollection) => {
            return taskCollection.find().toArray();
        });
    },
    createTask(title, description, hoursEstimated, completed) {
        if (!title) 
            return Promise.reject("You must provide a title for your task");
        
        if (!description) 
            return Promise.reject("You must provide a description for your task");

        if (!hoursEstimated) 
            return Promise.reject("You must provide an estimated time for your task");
        
        return taskItems().then((taskCollection) => {
            let newTask = {
                _id: uuidV4(),
                title: title,
                description: description,
                hoursEstimated: hoursEstimated,
                completed: completed,
                comments: []
            };
            
            return taskCollection
                .insertOne(newTask)
                .then((newInsertInformation) => {
                    return newInsertInformation.insertedId;
                })
                .then((newId) => {
                    return this.getTask(newId);
                });
        }).catch((error) => {
            console.log(error);
            return Promise.reject("Task was unable to be created");
        });
    },
    updateTask(id, title, description, hoursEstimated, completed) {
        return taskItems().then((taskCollection) => {
           return this.getTask(id).then((taskToUpdate) => {
                if (!title) {
                    title = taskToUpdate.title;
                }

                if (!description) {
                    description = taskToUpdate.description;
                }

                if (!hoursEstimated) {
                    hoursEstimated = taskToUpdate.hoursEstimated;
                }

                if (completed === -1) { //can't just say !completed as that would cause issues when trying to undo a task
                    completed = taskToUpdate.completed;
                }

                let updatedTask = {
                    _id: taskToUpdate._id,
                    title: title,
                    description: description,
                    hoursEstimated: hoursEstimated,
                    completed: completed,
                    comments: taskToUpdate.comments
                }

                return taskCollection.updateOne({_id: id}, updatedTask).then(() => {
                        return this.getTask(id);
                });
            });
        });
    },
    addComment(taskID, posterName, comment) {
        if (!taskID || !posterName || !comment) {
            return Promise.reject("You must provide a taskID, poster name, and comment.");
        }
        console.log("Adding comment, taskID " + taskID + " name " + posterName + " comment " + comment);
        return this.getTask(taskID).then((currentTask) => {
            console.log("Found task");
            let newComment = {
                _id: uuidV4(),
                name: posterName,
                comment: comment
            }

            return taskItems().then((taskCollection) => {
                console.log("Got full task list")
                let commentsList = currentTask.comments;
                commentsList.push(newComment);

                let newTask = {
                    _id: currentTask._id,
                    title: currentTask.title,
                    description: currentTask.description,
                    hoursEstimated: currentTask.hoursEstimated,
                    completed: currentTask.completed,
                    comments: commentsList
                };

                return taskCollection.updateOne({_id: taskID}, newTask).then(() => {
                    console.log("Updated task");
                    return newComment;
                });
            })
        })
    },
    updateComment(taskID, commentID, posterName, newComment) {
        if (!taskID || !commentID) {
            return Promise.reject("You must provide a taskID and a commentID");
        }

        return this.getTask(taskID).then((currentTask) => {
            console.log("Found task");
            return taskItems().then((taskCollection) => {
                console.log("Got full task list")
                let commentsList = currentTask.comments;
                let indexToSplice = -1;
                for(var i = 0; i < commentsList.length; i++) {
                    if (commentsList[i]._id == commentID) {
                        indexToSplice = i;
                        break;
                    }
                }

                let updatedComment = {
                    _id: commentID,
                    name: posterName,
                    comment: newComment
                }

                commentsList.splice(indexToSplice, 1, updatedComment);


                let newTask = {
                    _id: currentTask._id,
                    title: currentTask.title,
                    description: currentTask.description,
                    hoursEstimated: currentTask.hoursEstimated,
                    completed: currentTask.completed,
                    comments: commentsList
                };

                return taskCollection.updateOne({_id: taskID}, newTask).then(() => {
                    console.log("Updated task with updated comment");
                    return updatedComment;
                });
            });
        });
    },
    removeComment(taskID, commentID) {
        if (!taskID || !commentID) {
            return Promise.reject("You must provide a taskID and a commentID");
        }

        return this.getTask(taskID).then((currentTask) => {
            console.log("Found task");
            return taskItems().then((taskCollection) => {
                console.log("Got full task list")
                let commentsList = currentTask.comments;
                let indexToSplice = -1;
                for(var i = 0; i < commentsList.length; i++) {
                    if (commentsList[i]._id == commentID) {
                        indexToSplice = i;
                        break;
                    }
                }

                commentsList.splice(indexToSplice, 1);

                let newTask = {
                    _id: currentTask._id,
                    title: currentTask.title,
                    description: currentTask.description,
                    hoursEstimated: currentTask.hoursEstimated,
                    completed: currentTask.completed,
                    comments: commentsList
                };

                return taskCollection.updateOne({_id: taskID}, newTask).then(() => {
                    console.log("Updated task with removed comment");
                    return {message: "Deleted successfully."};
                });
            });
        });
    },
    removeTask(id) {
        if (!id) 
            return Promise.reject("You must provide an id to search for");
        
        return taskItems().then((taskCollection) => {
            return taskCollection
                .removeOne({_id: id})
                .then((deletionInfo) => {
                    if (deletionInfo.deletedCount === 0) {
                        throw(`Could not delete task with id of ${id}`)
                    }
                });
        });
    },
}

module.exports = exportedMethods;