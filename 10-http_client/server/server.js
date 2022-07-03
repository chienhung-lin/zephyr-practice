const http = require('http');

const host = "192.168.1.150";
const port = 8000;

const requestListener = function (req, res) {
	res.setHeader("Content-Type", "text/html");

	switch (req.url) {
		case "/":
			req.on('data', chunk => {
				console.log(chunk.toString());
			});
			req.on('end', () => {
				res.writeHead(200);
				res.end();
			});
			break
		default:
			res.writeHead(404);
			res.end();
	}
};

const server = http.createServer(requestListener);

server.listen(port, host, () => {
	console.log(`Server is running on http://${host}:${port}`);
});
