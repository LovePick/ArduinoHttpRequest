var http = require('http');

//create a server object:
http.createServer(function (req, res) {

    if (req.method == "POST") {
        console.log('POST /')

        var body = '';
        req.on('data', function (data) {
            body += data;
        });

        req.on('end', function () {
            console.log(body);
        });

    } else {
        console.log('GET /')
    }


    var msg = createMessage();

    var jsonStr = JSON.stringify(msg);
    res.write(jsonStr); //write a response to the client
    res.end(); //end the response
}).listen(8080); //the server object listens on port 8080


function createMessage() {
    return {
        message: 'Hello World!',
        time: '2019-11-23 13:10:00'
    };
}