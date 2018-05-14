/*
    Adam Gincel
    todo.js
    Defines the todoItems mongoCollections

    I pledge my honor that I have abided by the Stevens Honor System.
*/ 


const mongoCollections = require("./mongoCollections");
const todoItems = mongoCollections.todoItems;
const uuidV4 = require("uuid/V4");

let exportedMethods = {
    // This is a fun new syntax that was brought forth in ES6, where we can define
    // methods on an object with this shorthand!
    getTask(id) {
        if (!id) 
            return Promise.reject("You must provide an id to search for");
        
        return todoItems().then((taskCollection) => {
            return taskCollection.findOne({_id: id});
        }).catch((error) => {
            return Promise.reject(error);  
        });
    },
    getAllTasks() {
        return todoItems().then((taskCollection) => {
            return taskCollection.find().toArray();
            //return ["get", "All", "Tasks", "Isn't", "Working", "For", "Me", "Yet"];
        });
    },
    createTask(title, description) {
        if (!title) 
            return Promise.reject("You must provide a title for your task");
        
        if (!description) 
            return Promise.reject("You must provide a description for your task");
        
        return todoItems().then((taskCollection) => {
            let newTask = {
                _id: uuidV4(),
                title: title,
                description: description,
                completed: false,
                completedAt: null
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
    completeTask(id) {
        if (!id) 
            return Promise.reject("You must provide an id to search for");
        
        return this.getTask(id).then((currentTask) => {
            return todoItems().then((taskCollection) => {
                let newTask = {
                    title: currentTask.title,
                    description: currentTask.description,
                    completed: true,
                    completedAt: new Date()
                };
                return taskCollection.updateOne({_id: id}, newTask).then(() => {
                    return this.getTask(id);
                });
            });
        }).catch((error) => {
            console.log(error);
            return Promise.reject("Unable to complete a task with that ID")  
        });
    },
    removeTask(id) {
        if (!id) 
            return Promise.reject("You must provide an id to search for");
        
        return todoItems().then((taskCollection) => {
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