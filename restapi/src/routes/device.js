const router = require('express-promise-router')();

const {
    index,
    newDevice,
    getDevice
} = require('../controllers/device');

router.get('/', index);
router.post('/', newDevice);

router.get('/:deviceId', getDevice);

module.exports  = router;