<?php

	 function apologize($message) {
		render("apology.php", ["message" => $message]);
		exit;
	}
	function redirect($destination) {

		if(preg_match("/^http?:\/\//",$destination)) {
			header("Location: ".$destination);
		}

		else if(preg_match("/^\//", $destination)) {
			$protocol = (isset($_SERVER["HTTPS"])) ? "https" : "http";
			$host = $_SERVER["HTTP_HOST"];
			header("Location: $protocol://$host$destination");
		}

		else {
			// adapted from http://www.php.net/header
			$protocol = (isset($_SERVER["HTTPS"])) ? "https" : "http";
			$host = $_SERVER["HTTP_HOST"];
			$path = rtrim(dirname($_SERVER["PHP_SELF"]), "/\\");
			header("Location: $protocol://$host$path/$destination");
		}
	}

	function render($template, $values = []) {
		// if template exists, render it
		if (file_exists("../templates/$template")) {
			// extract variables into local scope
			extract($values);
			// render header
			require("../templates/header.php");
			// render template
			require("../templates/$template");
			// render footer
			require("../templates/footer.php");
		}
		// else err
		else {
			trigger_error("Invalid template: $template", E_USER_ERROR);
		}
	}
?>