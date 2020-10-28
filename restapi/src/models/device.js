const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const deviceSchema = new Schema({
    estado : String
});

module.exports = mongoose.model('device',deviceSchema)