// temp & humi report 
function doGet(e) {
    var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
    let temperature = e.parameter.temperature;
    let humidity = e.parameter.humidity;
    sheet.appendRow([new Date(), temperature, humidity]);
    return ContentService.createTextOutput("Success");
}
