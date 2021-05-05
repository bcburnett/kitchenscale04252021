const mongoose = require('mongoose');

const RecipeSchema = new mongoose.Schema(

    {
      ingredients: {
        type: [mongoose.Schema.Types.Mixed],
      },
      instructions: {
        type: [mongoose.Schema.Types.Mixed],
      },
      quantity: {
        type: [mongoose.Schema.Types.Mixed],
      },
      title: {
        type: String,
      },
      unit: {
        type: [mongoose.Schema.Types.Mixed],
      },
      url: {
        type: String,
      },
      comments: {
        type: [mongoose.Schema.Types.Mixed],
      },
      description: {
        type: String,
      },
      image: {
        type: String,
      },
    }

);

const Recipes = mongoose.model('Recipes', RecipeSchema);

module.exports = Recipes;
