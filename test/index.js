var http = require('http');
var fs = require('fs');

var app = http.createServer(function(req, res) {
  fs.readFile('./space.json', function (err, data) {
    if (err) {
      throw err; 
    }
    res.setHeader('Content-Type', 'application/json');
    res.write(data);
    res.end();
  })
});
app.listen(3000);
