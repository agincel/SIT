/*
    Adam Gincel
    Lab 6

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const express = require("express");
const router = express.Router();

let info = [
    {
      "schoolName": "Stevens Institute of Technology",
      "degree": "B.S. in Computer Science with a Minor in Quantitative Finance",
      "favoriteClass": "Systems Programming (CS392)",
      "favoriteMemory": "My first semester at the Stevens Game Development Club stands out to me as it really set the course for my entire career at Stevens. The people I met and the things I learned as a member, and now the President, of SGDC shaped me into the person I am today, and I'm very greatful for them."
    },
    {
      "schoolName": "Monroe Township High School",
      "degree": "High School Certificate",
      "favoriteClass": "Honors Advanced Web Design",
      "favoriteMemory": "Favorite memory: I was the Drum Major of our school's Marching Band in Fall 2013 -- at the end of that season we went out to Allentown PA and won Nationals, beating out 33 other marching bands in our division. I would classify that moment as the peak of my high school career, where all of the work and effort I had put into something truly paid off."
    }
]

router.get('/', function(req, res) {
    res.send(info);
});

module.exports = router;