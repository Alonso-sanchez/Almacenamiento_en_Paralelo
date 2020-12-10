const router = require('express-promise-router')();

const {
    index,
    newDevice,
    mayor
} = require('../controllers/device');

router.get('/', index);
router.post('/', newDevice);
router.get('/mayor', mayor);

module.exports  = router;