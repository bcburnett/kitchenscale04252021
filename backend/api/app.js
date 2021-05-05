const express = require('express');
const app = express();

const mongoose = require('mongoose');
const DB = new (require('./js/data'))();
mongoose.connect('mongodb://localhost/recipes', {
    useFindAndModify: false,
    useCreateIndex: true,
    useUnifiedTopology: true,
    useNewUrlParser: true,
     });
const db = mongoose.connection;
db.on('error',e=>console.log(e));
db.once('open', e => console.log('Connected to database'));

const cors = require('cors');
app.use(cors());

app.use(express.json());

app.get('/', (req, res) => {
    res.json({
        message: 'Hello World'
    });
});

app.get('/:recipe', (req, res) => {
    let recipe = req.params.recipe;

    res.json({
        message: `${recipe}`
    });
    console.log(JSON.parse(recipe))
});

app.post('/recipe', async (req, res) => {
    let recipe = req.body;
    console.log(recipe.name);
    const result = await DB.newRecipe(recipe);
    res.json(result);
    console.log(result);
});

app.post('/update', async (req, res) => {
    let recipe = req.body;
    console.log(recipe.name);
    const result = await DB.updateRecipe(recipe);
    res.json(result);
    console.log(result);
});

app.post('/search', async (req, res) => {
    let recipe = req.body;
    console.log(recipe.search);
    const result = await DB.nameSearch(recipe.search);
    res.json(result);
    console.log(result);
});

app.listen(2020, () => {
    console.log('server is listening on port 2020');
});
