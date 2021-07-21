// Imports
const express = require('express');

// Express app
const app = express();

// Serve files from the public directory
app.use(express.static('public'));

// Selecting port
app.listen(8000, () => {
    console.log(`Server running on port : ${8000}`);
});

// Routing
app.get('/', (req, res) => {
    res.sendFile(__dirname+'/index.html');
});