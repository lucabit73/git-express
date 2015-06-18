var config = require('./config.json');

var addExec = require('child_process').exec,
	addChild;
var commitExec = require('child_process').exec,
	commitChild;
var pushExec = require('child_process').exec,
	pushChild;

addChild = addExec('git -C '+config.env+' add .',
	function(error, stdout, stderr){
		if (error !== null){
			console.log('add exec error: ' + error);
			err_signal();
		}else{
			commitChild = commitExec('git -C '+config.env+' commit -m "Emergency commit"',
				function(error, stdout, stderr){
					if (error !== null) {
						console.log('commit exec error: ' + error);
						err_signal();
				    } else {
				    	console.log(stdout);
				    	pushChild = pushExec('git -C ' + config.env + ' push -u origin master',
				    		function(error, stdout, stderr){
				    			if (error !== null){
				    				console.log('push exec error: ' + error);
									err_signal();
				    			}else{
				    				console.log(stdout);
				    				end_signal();
				    			}
			    		});
				    }	
			});			
		}
});