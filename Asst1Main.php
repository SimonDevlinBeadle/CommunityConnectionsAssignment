<?php
/* 
http://localhost/Devlin-BeadleSimonAsst1/asst1main.php
Asst1Main.php
Author: Simon Devlin-Beadle
Date: October 11th 2020
*/
require_once("Asst1Include.php");

//main
date_default_timezone_set ('America/Toronto');
$mysqlObj = CreateConnectionObject(); 
$TableName = "BroadwayShows";
WriteHeaders("Simon Devlin-Beadle Assignment 1"); 

if (isset($_POST['f_CreateTable']))
    CreateTableForm();
else if (isset($_POST['f_AddRecord']))
    AddRecordForm();
else if (isset($_POST['f_ShowData']))
    ShowDataForm();
else if(isset($_POST['f_SaveData']))
    AddRecordToTable();
else
    DisplayMainForm();
WriteFooters();

function CloseConnection()
{
    mysqli_close($mysqlObj);
}

function DisplayMainForm()
{
    echo "<form action = ? method=post>";
    DisplayButton("f_CreateTable", "", "createTable.png", "Create Table");
    echo "</button>";
    DisplayButton("f_AddRecord", "", "addRecord.png", "Add Record");
    echo "</button>";
    DisplayButton("f_ShowData", "", "showData.png", "Show Data");
    echo "</button></form>";
}

function CreateTableForm()
{   
    global $TableName;
    global $mysqlObj;
    $stmt = $mysqlObj->prepare("Drop table If Exists $TableName");
    $stmt->execute();
    $ShowName = "ShowName VARCHAR(50)";
    $PreformanceDateAndTime = "PreformanceDateAndTime DATETIME";
    $NbrTickets =  "NbrTickets INT";
    $TicketPrice = "TicketPrice DECIMAL(5,2)";
    $SQLStatement = "Create Table $TableName($ShowName, $PreformanceDateAndTime, $NbrTickets, $TicketPrice)";
    $stmt = $mysqlObj->prepare($SQLStatement);
    if ($stmt == false) 
    {
        echo "Prepare failed on query $SQLStatement";
	    exit;
    }
    $CreateResult = $stmt->execute();
    if ($CreateResult)
        echo "Table $TableName created.";
    else
        echo "Unable to create table $TableName." . $stmt->error;
    $stmt->close();
    echo "<form action = ? method=post>";
    DisplayButton("f_Home", "", "home.png", "Home");
    echo "</form>";
    if (isset($_POST['f_Home']))
        DisplayMainForm();
    
}

function AddRecordForm()
{
    echo"
    <form action = ? method=post>
		<p>Show Name: <input type = text name = \"f_ShowName\"></p>
        <p>Preformance Date: <input type = date name = \"f_PreformanceDate\" value=";
        date('Y-m-d');
        echo "></p>
        <p>Preformance Time: <input type = time name = \"f_PreformanceTime\" value=";
        date("h:i");
        echo "></p>
        <p>Number Of Tickets: <input type = number name = \"f_NbrTickets\" value=2 min=\"1\" max=\"10\"></p>
        <p>Ticket Prices: </p>
        <input type = \"radio\" id = \"price\" name = \"f_TicketPrice\" value=\"100\" checked>
        <label for = \"price\">$100</label>
        <input type = \"radio\" id = \"price\" name = \"f_TicketPrice\" value=\"150\">
        <label for = \"price\">$150</label>
        <input type = \"radio\" id = \"price\" name = \"f_TicketPrice\" value=\"200\">
        <label for = \"price\">$200</label>";
        DisplayButton("f_SaveData", "", "saveData.png", "Save Data");
        echo "</button>";
        DisplayButton("f_Home", "", "home.png", "Home");
        echo "</button>";
        echo "</form>";
        if (isset($_POST['f_Home']))
        DisplayMainForm();
}

function AddRecordToTable()
{
    global $TableName;
    global $mysqlObj;
    $ShowName = $_POST['f_ShowName'];
    $PreformanceDate = $_POST['f_PreformanceDate'];
    $PreformanceTime = $_POST['f_PreformanceTime'];
    $PreformanceDateAndTime = $PreformanceDate . " " . $PreformanceTime;
    $NbrTickets = $_POST['f_NbrTickets'];
    $TicketPrice = $_POST['f_TicketPrice'];
    $query = "insert into $TableName (ShowName, PreformanceDateAndTime, NbrTickets, TicketPrice) values (?, ?, ?, ?)";
    $stmt = $mysqlObj->prepare($query);
    if($stmt === false)
    {
        echo "prepare failed on $query " . $mysqlObj->error;
        exit;
    }
    $BindSuccess = $stmt->bind_param("ssid", $ShowName, $PreformanceDateAndTime, $NbrTickets, $TicketPrice);
    if(!$BindSuccess)
        echo "Bind failed: " . $stmt->error;
    else
        $success = $stmt->execute();
    
    if ($success)
        echo "Record Successfully added to " . $TableName;
    else
        echo "Unable to add record to " . $TableName;
    $stmt->close();
    echo "<form>";
    DisplayButton("f_Home", "", "home.png", "Home");
    echo "</button>";
    echo "</form>";
    if (isset($_POST['f_Home']))
    DisplayMainForm();
}

function ShowDataForm()
{
    global $TableName;
    global $mysqlObj;
    $query = "select ShowName, PreformanceDateAndTime, NbrTickets, TicketPrice from $TableName ORDER BY TicketPrice";
    $stmt = $mysqlObj->prepare($query);
    $stmt->execute();
    $stmt->bind_result($ShowName, $PreformanceDateAndTime, $NbrTickets, $TicketPrice);
    while($stmt->fetch())
    {
        echo 
        "<table style = \"width:50%\">
            <tr>
                <th>Show Name</th>
                <th>Date and Time</th>
                <th>Number of Tickets</th>
                <th>Ticket Price</th>
            </tr>
            <tr>
                <th>$ShowName</th>
                <th>$PreformanceDateAndTime</th>
                <th>$NbrTickets</th>
                <th>$TicketPrice</th>
            </tr>
        </table>";
    }
    echo "$stmt->num_rows Bookings To Date.";
    $stmt->close();
    $mysqlObj->close();
    echo "<form>";
    DisplayButton("f_Home", "", "home.png", "Home");
    echo "</button>";
    echo "</form>";
    if (isset($_POST['f_Home']))
    DisplayMainForm();

}
?>