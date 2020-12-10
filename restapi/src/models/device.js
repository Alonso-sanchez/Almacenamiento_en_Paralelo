const mongoose = require('mongoose');
const Schema = mongoose.Schema;


const deviceSchema = new Schema({
    estado : String, 
    angulo : Intl,
    fecha : {
        type: Date,
        default:Date.now}
});

module.exports = mongoose.model('device',deviceSchema)
