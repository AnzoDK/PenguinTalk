const {app, BrowserWindow} = require('electron');  
const fs = require('fs');
const url = require('url');
const path = require('path');
const index = 'dist/penguin-talk-electron/index.html';

function patchIndex()
{
	let file = fs.readFileSync(index);
	let _index = file.toString().indexOf('<base href="/">');
	if(_index)
	{
		let buff = file.toString();
		let newStr = buff.replace('<base href="/">','<base href="./">');
		fs.rmSync(index);
		fs.writeFileSync(index,newStr);
	}
}
	
function onReady () {

	patchIndex();
	win = new BrowserWindow({width: 900, height: 6700})    
	win.loadURL(url.format({      
		pathname: path.join(
			__dirname,
			'dist/penguin-talk-electron/index.html'),       
		protocol: 'file:',      
		slashes: true     
	}))   
} 

app.on('ready', onReady);
