/*
    Adam Gincel
    Lab 6

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const express = require("express");
const router = express.Router();

let info = {
    "name": "Adam Gincel",
    "biography": "My name is Adam Gincel, and I'm a 3/4 CS undergrad at Stevens Institute of Technology. I'm President of the Game Development Club, Treasurer of the Computer and Console Gaming Society, and a member of the Stevens Concert Band and Concert Choir.\nIn my spare time I make games and write music, but also make sure I fit in academics and even fun when I can. I hail from central New Jersey, and didn't go to Rutgers like most of my high school class.",
    "favoriteShows": ["Super Smash Bros. Melee", "Minecraft", "Rocket League", "FlyFF"],
    "hobbies": ["Game Development", "Music Composition", "Competitive Smash Bros.", "Playing Instruments and Singing"]
}

router.get('/', function(req, res) {
    res.send(info);
});

module.exports = router;