const controller = {};
const models = require("../models")

controller.showList = async (req, res) => {
    res.locals.blogs = await models.Blog.findAll({
        attributes: ['id', 'title', 'imagePath', 'summary', 'createdAt'],
        include:[{model: models.Comment }]
    })
    res.render("index")
}

controller.showDetails = async (req, res) => {
    let id = isNaN(req.params.id) ? 0 : req.params.id
    res.locals.blogs = await models.Blog.findOne({
        attributes: ['id', 'title', 'description', 'createdAt'],
        where: {id: id},
        include:[{model: models.Category },
            {model: models.User },
            {model: models.Tag }
        ]
    })
    res.render("details")
}

module.exports = controller