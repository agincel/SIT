/*
    Adam Gincel
    Lab 6

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const recipeData = require("../recipe");

const express = require("express");
const router = express.Router();

router.get('/', function(req, res) {
    recipeData.getAllRecipes().then((recipeList) => {
        res.json(recipeList);
    }, () => {
        res.sendStatus(500).json({error: "lol"}); //something went wrong server-side
    });
});

router.post('/', function(req, res) {
    let postedData = req.body;

    recipeData.createRecipe(postedData.title, postedData.ingredients, postedData.steps).then((newRecipe) => {
        res.json(newRecipe);
    }, () => {
        res.sendStatus(500);
    });
});

router.get('/:id', function(req, res) {
    recipeData.getRecipe(req.params.id).then((foundRecipe) => {
        res.json(foundRecipe);
    }, () => {
        res.status(404).json({error: "Recipe not found"});
    });
});

router.put('/:id', function(req, res) {
    let postedData = req.body;
    recipeData.updateRecipe(req.params.id, postedData.title, postedData.ingredients, postedData.steps).then((updatedRecipe) => {
        res.json(updatedRecipe);
    }, () => {
        res.sendStatus(500);
    });
});

router.delete('/:id', function(req, res) {
    recipeData.removeRecipe(req.params.id).then(() => {
        res.json({message: "Recipe deleted successfully"});
    }, () => {
        res.sentStatus(500);
    });
});




module.exports = router;