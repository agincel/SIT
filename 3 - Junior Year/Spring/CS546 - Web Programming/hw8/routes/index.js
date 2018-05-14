const path = require('path');

const constructorMethod = (app) => {
    app.use("*", (req, res) => {
        res.render("templates/form", {});
    });
};

module.exports = constructorMethod;