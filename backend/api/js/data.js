/* eslint-disable new-cap */
/* eslint-disable require-jsdoc */

module.exports = class db {
  /**
  */
  constructor() {
    this.Recipes = require('../models/recipe.model');
  }
  convertFraction (string) {
    console.log(string)
    const ary = string.split(' ')
    console.log(ary[0])
    if([...ary[0]].every(c => '0123456789.+/'.includes(c))) return eval(ary[0])
    return -1;
};

  async newRecipe(obj) {
    console.log(obj);
    delete obj._id;
    const newRecipe = this.Recipes(obj);
    const result = await newRecipe.save()
      .then((res) => res)// resolve the promise
      .catch((e) => false);

    console.log(result);
    return result;
  }

  async updateRecipe(item) {
    console.log(item);
    const r_sult = await this.Recipes.deleteOne({ '_id': item._id });
    console.log(r_sult);
    
    const result = await this.newRecipe(item);
    console.log(result);
    return result;
  }

  async nameSearch(searchString){
    const result = await this.Recipes
      .find({ $text: { $search: searchString } })
      .then((res) => res)// resolve the promise
      .catch((e) => false);
      return result;
  }
};
