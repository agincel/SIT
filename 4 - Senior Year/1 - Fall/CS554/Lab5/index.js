const express = require("express");
var app = express();
var configRoutes = require("./routes");

configRoutes(app);

app.listen(3000, () => {
    console.log("Server online at localhost:3000");
});

