const { app, BrowserWindow } = require('electron');
const path                   = require('path');

// Configure for software rendering (WSL compatible)
app.commandLine.appendSwitch('use-angle', 'swiftshader');
app.commandLine.appendSwitch('use-gl', 'angle');
app.commandLine.appendSwitch('enable-webgl');
app.commandLine.appendSwitch('enable-unsafe-webgpu');

let mainWindow;

function createWindow()
{
    mainWindow = new BrowserWindow({
        width: 1200,
        height: 800,
        webPreferences: { nodeIntegration: true, contextIsolation: false, webgl: true },
        backgroundColor: '#000000',
        title: 'Helios - Earth Visualization'
    });

    mainWindow.loadFile('index.html');

    // Open DevTools in development mode
    if (process.argv.includes('--dev')) { mainWindow.webContents.openDevTools(); }

    mainWindow.on('closed', () => { mainWindow = null; });
}

app.on('ready', createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') { app.quit(); }
});

app.on('activate', () => {
    if (mainWindow === null) { createWindow(); }
});
