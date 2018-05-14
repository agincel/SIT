/*
    Adam Gincel
    Lab 6

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const recipeData = require("../recipe");

const express = require("express");
const router = express.Router();

router.post('/:recipeID', function(req, res) {
    recipeData.addComment(req.params.recipeID, req.body.poster, req.body.comment).then((newComment) => {
        res.json(newComment);
    }, () => {
        res.sendStatus(500);
    });
});

router.put('/:commentID', function(req, res) {
    recipeData.getAllRecipes().then((recipeList) => {
        let hasFoundComment = false;
        let recipeID = null;
        for(var i = 0; i < recipeList.length && !hasFoundComment; i++) {
            for (var j = 0; j < recipeList[i].comments.length && !hasFoundComment; j++) {
                if (recipeList[i].comments[j]._id == req.params.commentID) {
                    hasFoundComment = true;
                    recipeID = recipeList[i]._id;
                    break;
                }
            }
        }
        if (!hasFoundComment) {
            res.status(404).json({error: "Could not find comment with that ID"});
        } else {
            recipeData.updateComment(recipeID, req.params.commentID, req.body.poster, req.body.comment).then((message) => {
                console.log("success");
                res.json(message);
            }, () => {
                res.sendStatus(500);
            });
        }
    });
});

router.delete('/:commentID', function(req, res) {
    recipeData.getAllRecipes().then((recipeList) => {
        let hasFoundComment = false;
        let recipeID = null;
        for(var i = 0; i < recipeList.length && !hasFoundComment; i++) {
            for (var j = 0; j < recipeList[i].comments.length && !hasFoundComment; j++) {
                if (recipeList[i].comments[j]._id == req.params.commentID) {
                    hasFoundComment = true;
                    recipeID = recipeList[i]._id;
                    break;
                }
            }
        }
        if (!hasFoundComment) {
            res.status(404).json({error: "Could not find comment with that ID"});
        } else {
            recipeData.removeComment(recipeID, req.params.commentID).then((message) => {
                console.log("success");
                res.json({message: "Comment removed successfully."});
            }, () => {
                res.sendStatus(500);
            })
        }
    });
});

module.exports = router;