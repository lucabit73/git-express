
var serialport = require("serialport");
var SerialPort = serialport.SerialPort; // localize object constructor

var config = require('./config.json');
var serial = config.serial_port;
 
var sp = new SerialPort(serial, {
  parser: serialport.parsers.readline("\n")
});

var status = 0;

sp.on("data", function (data) {

    data = data.substring(0, data.length-1);
    //console.log("Arduino say: ",data);

    if (data == "Power ON - GIT EXPRESS"){
        console.log('Ready to Push!!');
        sp.write('start');
    }


    if (data == "start" && status == 0){
    	status = 1;
    	console.log('Push start!');
    	sp.write('wait');

		/*var spawn = require('child_process').spawn,
		command = spawn('ls', [], { cwd: config.env });
		//command = spawn('git', ['push','-u', 'origin', 'master'], { cwd: config.env });
		command.stdout.on('data', function (data) {
		  console.log('stdout: ' + data);
		});
		command.stderr.setEncoding('utf8');
		command.stderr.on('data', function (data) {
		  console.log('stderr: ' + data);
		  err_signal();
		});

		command.on('close', function (code) {
		  console.log('child process exited with code ' + code);
		  end_signal();
		});*/

		var exec = require('child_process').exec,
		command = exec('git -C '+config.env+' push -u origin master', function(error, stdout, stderr){
			if (error !== null) {
		      console.log('exec error: ' + error);
		      err_signal();
		    } else {
		    	console.log(stdout);
		    	end_signal();
		    }
			
		});
    }      
});

function end_signal(){
	setTimeout(function(){
		sp.write('end');
		setTimeout(function(){
			sp.write('start');
			status = 0;
		},config.blink_time)	
	},config.add_time)

}

function err_signal(){
	sp.write('err');
}