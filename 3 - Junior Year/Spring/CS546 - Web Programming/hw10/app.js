const express = require("express");
const bodyParser = require("body-parser");
const app = express();
const path = require("path");
const xss = require('xss');



/*
Fixed things:

- Form didn't actually post to /

- Changed hints to <h1>
- Fixed text color contrast issue
- Fixed ambiguous a tag
- Fixed both form entry labels not being properly linked (x2)

- fixed all jquery selectors and fixed their corresponding DOM objects IDs to match (x3)
- JSON.parse(data) on the response to the submit

- protect from xss attack

*/



app.use("/public", express.static(__dirname + "/public"));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.post("/", (req, res) => {
  console.log("We got a post at /")

  const email = req.body.email;
  const message = xss(req.body.message);


  console.log(req.body)

  const dataResponse = {
    email: email,
    message: message,
    reply: `[${email}]: ${message}`
  };

  res.json(JSON.stringify(dataResponse));
});

app.get("/", (req, res) => {
  res.sendFile(path.resolve(__dirname, "index.html"));
});

app.listen(3000, () => {
  console.log("We've now got a server!");
  console.log("Your routes will be running on http://localhost:3000");
});
