const User = require('../models/device');

module.exports = {

    index: async (req,res,next) => {
        const Interruptor = await User.find({});
        res.status(200).json(Interruptor);
    },

    newDevice: async (req, res,next) => {       
        const newInt = new User(req.body);
        const Interruptor = await newInt.save();
        res.status(200).json(Interruptor);
    },

    mayor: async (req, res) => {
        var fecha1 = new Date(req.query.fecha1);
        var fecha2 = new Date(req.query.fecha2);
        const consulta = {
            fecha: {
              $gte: fecha1,
              $lt: fecha2
            }
          };
        const rest = await User.find(consulta);
        res.status(200).json(rest);
    }
 
};