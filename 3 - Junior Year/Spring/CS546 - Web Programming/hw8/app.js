const express = require("express");
const bodyParser = require("body-parser");
const app = express();
const static = express.static(__dirname + "/public");

const configRoutes = require("./routes");
const exphbs = require("express-handlebars");

app.use("/public", static); //define what server directory applies to the /public folder
app.use(bodyParser.json()); //parses json for requests

app.engine("handlebars", exphbs({defaultLayout: "main"}));
app.set("view engine", "handlebars");

configRoutes(app);

app.listen(3000, () => {
    console.log("Server is up and running at http://localhost:3000");
});