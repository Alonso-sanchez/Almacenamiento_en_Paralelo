const User = require('../models/device');

module.exports = {

    index: async (req, res, next) => {
        const Interruptor = await User.find({});
        res.status(200).json(Interruptor);
    },

    newDevice: async (req, res, next) => {
        const newInt = new User(req.body);
        const Interruptor = await newInt.save();
        res.status(200).json(Interruptor);
    },

    getDevice: async (req, res, next) => {
        const { deviceId } = req.params;
        const Interruptor = await Use.findById(deviceId);
        res.status(200).json(Interruptor);
    },
 
};