const express = require('express');
const expressHbs = require('express-handlebars');

const app = express();
const port = 4000 || process.env.PORT;

app.use(express.static(__dirname + "/html"))

app.engine('hbs', expressHbs.engine ({
    layout : __dirname + "/views/layouts",
    partialsDir : __dirname + "/views/partials",
    defaultLayout : 'layout',
    extname : 'hbs',
    runtimeOptions: {
        allowProtoPropertiesByDefault: true,
    },
    helpers: {
        showDate: (date) => {
            return date.toLocalDateString('en-US', {
                year: 'numeric',
                month: 'long',
                day: 'numeric',
            })
        }
    }
})
)


app.set("view engine", "hbs")
app.get("/",(req,res)=> res.redirect("/blogs"))
app.use("/blogs", require('./routes/blogRouter'))

app.get('/',(req,res)=> res.send('Hello World!'))

app.get("/createTables", (req, res) => {
    let models = require("./models");
    models.sequelize.sync().then(() => {
      res.send("Tables created!");
    });
});

app.listen(port, () => console.log(`Example app listening on port ${port}!`))