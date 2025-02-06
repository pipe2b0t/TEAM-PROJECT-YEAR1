// Attendance System
function doGet(e) {
    let studentid = e.parameter.studentid; 

    const studentsheet = SpreadsheetApp.openById("1Qaa7VqRKXkJF_37QopVU75qS--71uw4UHNGqOq3ZGj8");
    const studentrange = studentsheet.getSheetByName("studentdata").getRange("A2:C61");
    const studentvalue = studentrange.getValues();

    const attendsheetss = SpreadsheetApp.openById("18jrGS6l614L7LafIL4C6zZuf2UgxZ1bS8Gk5SrWsRpY");
    const attendSheet = attendsheetss.getSheetByName("attend"); 

    for (let i = 0; i < studentvalue.length; i++) {
      if (studentid == studentvalue[i][0]) {
        //console.log("Found: " + studentvalue[i][0]);

        attendSheet.appendRow([new Date(), studentvalue[i][0], studentvalue[i][1], studentvalue[i][2]]);
        return ContentService.createTextOutput("Success").setMimeType(ContentService.MimeType.TEXT);
      }
    }
}
