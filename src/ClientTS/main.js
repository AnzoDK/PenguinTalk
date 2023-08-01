// Import necessary modules
const {app, BrowserWindow} = require('electron');
const fs = require('fs');
const url = require('url');
const path = require('path');

// Function to create the main window
function onReady() {
    // Apply the patch to the index.html file
    //patchIndex();

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