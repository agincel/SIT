const clientRoutes = require("./client");

const constructor = (app) => {
    app.use("/", clientRoutes);
    
    app.use("*", (req, res) => {
        res.status(404).json({error: "Page not found"});
    });
};

module.exports = constructor;