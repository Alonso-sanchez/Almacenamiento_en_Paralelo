const bodyParser = require('body-parser');
const morgan  = require('morgan');
const express = require('express');
const mongoose = require('mongoose');

const app = express();
const puerto = '3000'
const host = '192.168.0.12'
const deviceRoutes = require('./routes/device');

mongoose.Promise = global.Promise;
mongoose.connect('mongodb://localhost/restapi', {
    useMongoClient: true
}).then(db => console.log('db is connected'))
  .catch(err => console.log(err));

//settings
//app.set('port', process.env.PORT || 3000);
//app.set('json spaces', 2)

//middlewares
app.use(morgan('dev'));
app.use(express.urlencoded({extended: false}));
app.use(express.json());
app.use(bodyParser.json());

//routes
app.use('/device', deviceRoutes);

// starting the server 
app.listen(puerto,host, () => {
    console.log(`Server on port ${puerto}`);
});
