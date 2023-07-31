// Import necessary modules
const {app, BrowserWindow} = require('electron');
const fs = require('fs');
const url = require('url');
const path = require('path');

// Define the path to the index.html file
const index = 'dist/penguin-talk-electron/index.html';

// Function to patch the index.html file
function patchIndex() {
    // Read the file
    let file = fs.readFileSync(index);
    // Get the index of the '<base href="/">'
    let _index = file.toString().indexOf('<base href="/">');
    if (_index) {
        // Replace '<base href="/">' with '<base href="./">'
        let buff = file.toString();
        let newStr = buff.replace('<base href="/">', '<base href="./">');
        // Remove the old index.html file and write the patched version
        fs.rmSync(index);
        fs.writeFileSync(index, newStr);
    }
}

// Function to create the main window
function onReady() {
    // Apply the patch to the index.html file
    patchIndex();

    // Create a new browser window
    let win = new BrowserWindow({width: 900, height: 6700});

    // Load the index.html file in the window
    win.loadURL(url.format({
        pathname: path.join(__dirname, 'dist/penguin-talk-electron/index.html'),
        protocol: 'file:',
        slashes: true
    }));
}

// Call onReady when the Electron app is ready
app.on('ready', onReady);