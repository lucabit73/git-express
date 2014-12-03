
var serialport = require("serialport");
var SerialPort = serialport.SerialPort; // localize object constructor

var config = require('./config.json');
var serial = config.serial_port;
 
var sp = new SerialPort(serial, {
  parser: serialport.parsers.readline("\n")
});

sp.on("data", function (data) {

    data = data.substring(0, data.length-1);
    //console.log("Arduino say: ",data);

    if (data == "Power ON - MASBOOTH"){
        console.log('Ready to Push!!');
    }


    if (data == "green"){
    	console.log('green push');

    	var spawn = require('child_process').spawn,
		    
		gitadd = spawn('git', ['push','-u', 'origin', 'master'], { cwd: config.env });

		gitadd.stdout.on('data', function (data) {
		  console.log('stdout: ' + data);
		});

		gitadd.stderr.on('data', function (data) {
		  console.log('stderr: ' + data);
		});

		gitadd.on('close', function (code) {
		  console.log('child process exited with code ' + code);
		  ok_signal();
		});
    }      
});

function ok_signal(){
	//
}