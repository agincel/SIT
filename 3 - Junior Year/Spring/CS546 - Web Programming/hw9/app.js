/*
    Adam Gincel
    Lab 9

    I pledge my honor that I have abided by the Stevens Honor System.
*/

const express = require("express");
const session = require("express-session");

const bodyParser = require("body-parser");
const cookieParser = require("cookie-parser");

const passport = require('passport');
const LocalStrategy = require("passport-local").Strategy;

const bcrypt = require("bcrypt-nodejs");

let app = express();


const static = express.static(__dirname + "/public");
let configRoutes = require("./routes");


app.use("/public", static); //define what server directory applies to the /public folder
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(cookieParser());

const userData = [
    {
        _id: "11111",
        username: "masterdetective123",
        firstName: "Sherlock",
        lastName: "Holmes",
        profession: "Detective",
        bio: "Sherlock Holmes is a fictional private detective created by British author Sir Arthur Conan Doyle. Known as a \"consulting detective\" in the stories, Holmes is known for a proficiency with observation, forensic science, and logical reasoning that borders on the fantastic, which he employs when investigating cases for a wide variety of clients, including Scotland Yard.",
        hashedPassword: "$2a$06$yYiM1gV7zu5PHdhTEBJ44ehCN5l/97jzq6K7f6X5vqSWDI9k5ca9q"
    },
    {
        _id: "22222",
        username: "lemon",
        firstName: "Elizabeth",
        lastName: "Lemon",
        profession: "Writer",
        bio: "Elizabeth Miervaldis \"Liz\" Lemon is the main character of the American television series 30 Rock. She created and writes for the fictional comedy-sketch show The Girlie Show or TGS with Tracy Jordan.",
        hashedPassword: "$2a$06$OWpYOlG1QTPJ2IqWIyS2segDkL/hJz1sXqqP41W/ZTtrz5.gZqKSa"
    },
    {
        _id: "33333",
        username: "theboywholived",
        firstName: "Harry",
        lastName: "Potter",
        profession: "Student",
        bio: "Harry Potter is a series of fantasy novels written by British author J. K. Rowling. The novels chronicle the life of a young wizard, Harry Potter, and his friends Hermione Granger and Ron Weasley, all of whom are students at Hogwarts School of Witchcraft and Wizardry . The main story arc concerns Harry's struggle against Lord Voldemort, a dark wizard who intends to become immortal, overthrow the wizard governing body known as the Ministry of Magic, and subjugate all wizards and Muggles.",
        hashedPassword: "$2a$06$7BUA0vT5jWHpmDtlErf6AuuIND2ucVXrFRd8fJxRu9ciHadOzm/OK"
    }
]

app.use(session({ secret: "Ihavenoideawhatthisisfor", resave: true, saveUninitialized: true}));
app.use(passport.initialize());
app.use(passport.session());

passport.serializeUser(function(user, done) {
  done(null, user);
});

passport.deserializeUser(function(user, done) {
  done(null, user);
});

passport.use(new LocalStrategy(function(username, password, done) {
    process.nextTick(function() {
                var userObj = userData.find(u => u.username == username);
                if (!userObj) { //if wrong username
                    console.log("Didn't find user");
                    return done(null, false);
                }

                if (!bcrypt.compareSync(password, userObj.hashedPassword)) { //if wrong password
                    console.log("Incorrect Password");
                    return done(null, false);
                }

                return done(null, userObj);
    });
}));


require('./routes/index.js')(app, passport);



app.listen(3000, () => {
    console.log("Server is up and running!");
    console.log("Check it out at http://localhost:3000");
});

