/*
    Adam Gincel
    recipe.js
    Defines the recipeItems mongoCollections

    I pledge my honor that I have abided by the Stevens Honor System.
*/ 


const mongoCollections = require("./mongoCollections");
const recipeItems = mongoCollections.recipeItems;
const uuidV4 = require("uuid/V4");

let exportedMethods = {
    getRecipe(id) {
        if (!id) 
            return Promise.reject("You must provide an id to search for");
        
        return recipeItems().then((recipeCollection) => {
            return recipeCollection.findOne({_id: id});
        }).catch((error) => {
            return Promise.reject(error);  
        });
    },
    getAllRecipes() {
        return recipeItems().then((recipeCollection) => {
            return recipeCollection.find().toArray();
        });
    },
    createRecipe(title, ingredients, steps) {
        if (!title) 
            return Promise.reject("You must provide a title for your recipe");
        
        if (!ingredients || ingredients.length == 0) 
            return Promise.reject("You must provide a list of ingredients for your recipe");

        if (!steps || steps.length == 0) 
            return Promise.reject("You must provide a list of steps for your recipe");
        
        return recipeItems().then((recipeCollection) => {
            let newRecipe = {
                _id: uuidV4(),
                title: title,
                ingredients: ingredients,
                steps: steps,
                comments: []
            };
            
            return recipeCollection
                .insertOne(newRecipe)
                .then((newInsertInformation) => {
                    return newInsertInformation.insertedId;
                })
                .then((newId) => {
                    return this.getRecipe(newId);
                });
        }).catch((error) => {
            console.log(error);
            return Promise.reject("Recipe was unable to be created");
        });
    },
    updateRecipe(id, title, ingredients, steps) {
        return recipeItems().then((recipeCollection) => {
           return this.getRecipe(id).then((recipeToUpdate) => {
                if (!title) {
                    title = recipeToUpdate.title;
                }

                if (!ingredients) {
                    ingredients = recipeToUpdate.ingredients;
                }

                if (!steps) {
                    steps = recipeToUpdate.steps;
                }

                let updatedRecipe = {
                    _id: recipeToUpdate._id,
                    title: title,
                    ingredients: ingredients,
                    steps: steps,
                    comments: recipeToUpdate.comments
                }

                return recipeCollection.updateOne({_id: id}, updatedRecipe).then(() => {
                        return this.getRecipe(id);
                });
            });
        });
    },
    addComment(recipeID, posterName, comment) {
        if (!recipeID || !posterName || !comment) {
            return Promise.reject("You must provide a recipeID, poster name, and comment.");
        }
        console.log("Adding comment, recipeID " + recipeID + " name " + posterName + " comment " + comment);
        return this.getRecipe(recipeID).then((currentRecipe) => {
            console.log("Found recipe");
            let newComment = {
                _id: uuidV4(),
                poster: posterName,
                comment: comment
            }

            return recipeItems().then((recipeCollection) => {
                console.log("Got full recipe list")
                let commentsList = currentRecipe.comments;
                commentsList.push(newComment);

                let newRecipe = {
                    _id: currentRecipe._id,
                    title: currentRecipe.title,
                    ingredients: currentRecipe.ingredients,
                    steps: currentRecipe.steps,
                    comments: commentsList
                };

                return recipeCollection.updateOne({_id: recipeID}, newRecipe).then(() => {
                    console.log("Updated recipe");
                    return newComment;
                });
            })
        })
    },
    updateComment(recipeID, commentID, posterName, newComment) {
        if (!recipeID || !commentID) {
            return Promise.reject("You must provide a recipeID and a commentID");
        }

        return this.getRecipe(recipeID).then((currentRecipe) => {
            console.log("Found recipe");
            return recipeItems().then((recipeCollection) => {
                console.log("Got full recipe list")
                let commentsList = currentRecipe.comments;
                let indexToSplice = -1;
                for(var i = 0; i < commentsList.length; i++) {
                    if (commentsList[i]._id == commentID) {
                        indexToSplice = i;
                        break;
                    }
                }

                let updatedComment = {
                    _id: commentID,
                    poster: posterName,
                    comment: newComment
                }

                commentsList.splice(indexToSplice, 1, updatedComment);


                let newRecipe = {
                    _id: currentRecipe._id,
                    title: currentRecipe.title,
                    ingredients: currentRecipe.ingredients,
                    steps: currentRecipe.steps,
                    comments: commentsList
                };

                return recipeCollection.updateOne({_id: recipeID}, newRecipe).then(() => {
                    console.log("Updated recipe with updated comment");
                    return updatedComment;
                });
            });
        });
    },
    removeComment(recipeID, commentID) {
        if (!recipeID || !commentID) {
            return Promise.reject("You must provide a recipeID and a commentID");
        }

        return this.getRecipe(recipeID).then((currentRecipe) => {
            console.log("Found recipe");
            return recipeItems().then((recipeCollection) => {
                console.log("Got full recipe list")
                let commentsList = currentRecipe.comments;
                let indexToSplice = -1;
                for(var i = 0; i < commentsList.length; i++) {
                    if (commentsList[i]._id == commentID) {
                        indexToSplice = i;
                        break;
                    }
                }

                commentsList.splice(indexToSplice, 1);

                let newRecipe = {
                    _id: currentRecipe._id,
                    title: currentRecipe.title,
                    ingredients: currentRecipe.ingredients,
                    steps: currentRecipe.steps,
                    comments: commentsList
                };

                return recipeCollection.updateOne({_id: recipeID}, newRecipe).then(() => {
                    console.log("Updated recipe with removed comment");
                    return {message: "Deleted successfully."};
                });
            });
        });
    },
    removeRecipe(id) {
        if (!id) 
            return Promise.reject("You must provide an id to search for");
        
        return recipeItems().then((recipeCollection) => {
            return recipeCollection
                .removeOne({_id: id})
                .then((deletionInfo) => {
                    if (deletionInfo.deletedCount === 0) {
                        throw(`Could not delete recipe with id of ${id}`)
                    }
                });
        });
    },
}

module.exports = exportedMethods;