var net = require('net');
var carrier = require('carrier');

var server = net.createServer(function(conn) {
  
  carrier.carry(conn, function(line) {
    
    connections.forEach(function(i) {
        i.write(line);
    })
    console.log(line);
  });

});

server.listen(6667);


connections = [];

broadcaster = net.createServer(function(conn) {
  
  connections.push(conn);  

}).listen(6668);
