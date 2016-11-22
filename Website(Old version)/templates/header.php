<!DOCTYPE html>
<html>
	<head>
		<link rel='SHORTCUT ICON' href='/img/logo.ico'>
		<link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>
		<link href="/css/css.css" rel="stylesheet"/>
		<script src="/js/jquery.min.js"></script>
		<script src="/js/bootstrap.min.js"></script>
		<script type="text/javascript">
<!-->
var image1=new Image()
image1.src="/img/1.png"
var image2=new Image()
image2.src="/img/2.gif"
var image3=new Image()
image3.src="/img/3.png"
//-->
</script>
		<?php if(isset($title)): ?>
			<title>Shopping: <?= htmlspecialchars($title) ?></title>
		<?php else: ?>
			<title>Shopping</title>
		<?php endif ?>
		
	</head>
	<body>
		<div class="container">
			<div id="top">
				<a href="/"><img alt="Shopping" src="/img/logo.gif"/> <!--img alt="Shopping" src="/img/name.png" /--></a>
				<hr>
			</div>
			<div id="middle">