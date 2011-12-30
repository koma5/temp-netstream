var net = require('net');
var carrier = require('carrier');

var server = net.createServer(function(conn) {
  
  carrier.carry(conn, function(line) {
    console.log(line);
  });

});

server.listen(6667);
