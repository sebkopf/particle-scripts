//------------------------------------
// inspired by https://github.com/deancs/particlePostGoogle

var errSheetID = "*********************************************";
var logSheetID = "*********************************************";
var particleToken = "*********************************************";
var addTimeStamp = true;

//------------------------------------
// Process particle data
//

function doPost(e) {

  Logger = BetterLog.useSpreadsheet(errSheetID);

  var raw_data = "UNDEFINED";
  var device_name = "UNDEFINED";

  try {

    var hook_data = JSON.parse(e.postData.contents);
    raw_data = hook_data.data
    device_name = getdevice_name(hook_data.coreid);
    var device_data = JSON.parse(raw_data);
    var ws = setWorksheet(device_name,device_data);

    var vals = Object.keys(device_data).map(function (key) {
      return device_data[key];
    });

    if (addTimeStamp) {
      var t = new Date(hook_data.published_at);
      vals.unshift(t);
    }

    ws.appendRow(vals);

    Logger.info('Succesfully added row %d for device %s', ws.getLastRow(), device_name);

  } catch(err) {
    err = (typeof err === 'string') ? new Error(err) : err;
    Logger.severe('%s: %s (line %s, file "%s"). Stack: "%s" . While processing data %s from device %s.',err.name||'',
                  err.message||'', err.lineNumber||'', err.fileName||'', err.stack||'', raw_data||'', device_name||'');

    return ContentService.createTextOutput('{"status":"error"}');
  }

  return ContentService.createTextOutput('{"status":"ok"}');
}

//------------------------------------
//Return device name from particle.io
//

function getdevice_name(deviceId) {

  try {
    var response = UrlFetchApp.fetch("https://api.particle.io/v1/devices/" + deviceId + "?access_token=" + particleToken);
    var device = JSON.parse(response);
    return device.name;

  } catch(err) {
    Logger = BetterLog.useSpreadsheet(errSheetID);
    Logger.warning(err.message);
    return deviceId;
  }

}

//------------------------------------
//Set the current worksheet to the device-name, if it doesnt exist create it.
//

function setWorksheet(device_name,device_data) {

  var ss = SpreadsheetApp.openById(logSheetID);
  var ws = ss.getSheetByName(device_name);

  if (ws == null) {
    ws = ss.insertSheet(device_name);

    //Get field names from object to use for column titles
    var myKeys = Object.keys(device_data);
    if (addTimeStamp) {
      myKeys.unshift("Timestamp");
    }

    ws.appendRow(myKeys);
  }

  return ws;

}
