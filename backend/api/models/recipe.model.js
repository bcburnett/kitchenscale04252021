const mongoose = require('mongoose');

const RecipeSchema = new mongoose.Schema({
    name: {
        type: String
    },
    description: {
        type: String
    },
    cuisine: {
        type: String
    },
    type: {
        type: String
    },
    priingredient: {
        type: String
    },
    ingredients: {
        type: [
            Array
        ]
    },
    instructions: {
        type: String
    },
    ptime: {
        type: String
    },
    ctime: {
        type: String
    },
    servings: {
        type: String
    },
    source: {
        type: String
    },
    website: {
        type: String
    }
});

const Recipes = mongoose.model('recipes', RecipeSchema);

module.exports = Recipes;

