/*
    Adam Gincel
    Lab 9

    I pledge my honor that I have abided by the Stevens Honor System.
*/


const path = require("path");
const router = require("express").Router();

const passport = require("passport");

router.get("/", (req, res) => {
    res.sendFile(path.resolve('public/index.html'));
}); 

router.post('/login',
    passport.authenticate('local', {
        successRedirect: '/private',
        failureRedirect: '/loginFailure'
    })
);

router.get('/loginFailure', function(req, res, next) {
    console.log("Login failure.");
    res.send("<h1>Login failed. Click <a href=\"/\">here</a> to try again.</h1>");
});

router.get('/private', function(req, res, next) {

    if (req.user) {
        console.log("Login success!");
        console.log(req.user);

        var outputPage = "";
        //this is kinda hacky, I know
        //I should probably use handlebars but for now this is what I'm doing
        outputPage += "<h1>" + req.user.username + " -- " + req.user.firstName + " " + req.user.lastName + "</h1>\n";
        outputPage += "<h3>Profession: " + req.user.profession + "</h3>\n";
        outputPage += "<p>" + req.user.bio + "</p>\n";

        res.send(outputPage);
    } else {
        res.redirect("/");
    }
});

router.get("*", (req, res) => {
    res.status(404).json({error: "Not Found"});
});

module.exports = router;