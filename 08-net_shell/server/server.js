const HOST = "192.168.1.11";
const PORT = 3456;

const net = require('net');
const server = net.createServer((socket) => {
	
	// 'connection' listener
	console.log('client connected');
	
	socket.on('end', () => {
		console.log('client disconnected');
	});

	socket.on('data', (chunk) => {
		console.log(chunk.toString());
		socket.write(chunk);
	});
});

server.listen(PORT, HOST, () => {
	console.log('server start listening');
});
