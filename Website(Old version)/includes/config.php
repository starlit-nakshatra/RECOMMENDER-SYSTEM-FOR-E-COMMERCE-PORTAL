<?php

	ini_set("display_errors", true);
	error_reporting(E_ALL);
	// Database Variables.
	/*
	$host="localhost";
	$username="root";
	$password="";
	//Connecting to database
	$con=mysql_connect($host,$username,$password);
	
	// Check connection
	if (!$con) {
		echo "Failed to connect to MySQL: " . mysql_connect_error();
	}
	mysql_select_db("store");
	*/
	require("functions.php");

	session_start();

?>