const mongoose = require('mongoose');

const PantryItemSchema = new mongoose.Schema({
  name: String,
  lowlimit: Number,
  description: String,
  comments: String,
  category: String,
  onhand: Number,
  userid: String,
});

const PantryItem = mongoose.model('PantryItem', PantryItemSchema);

module.exports = PantryItem;
