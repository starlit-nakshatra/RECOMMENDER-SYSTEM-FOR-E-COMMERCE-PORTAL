<?php
	$product = $_POST["product"];
	$mini = $_POST["mini"];
	$maxi = $_POST["maxi"];
	
	$sql="";
	if($product=="phone") {
		$sql = "SELECT * FROM phone WHERE price>=$mini AND price<=$maxi";
	}
	else if($product=="tv") {
		$sql = "SELECT * FROM tv WHERE price>=$mini AND price<=$maxi";
	}
	
	/*$rows = query($sql);
	if (!$rows) {
         die('Error: ' . mysql_error($con));
	}
	
	*/
	?>
		<?='<table class="table table-striped">'?>
		<?php foreach($rows as $row): ?>
        <?= "<td>" ?>
			<?= "<tr><img src=".$row[img_link]."/></tr>" ?>
			<?= "<tr>".$row["title"]."</tr>" ?>
            <?= "<tr>".$row["price"]."</tr>" ?>
        <?= "</td>" ?>
        <?php endforeach ?>
		<?='</table>'?>
	
	<?php
	/*
echo '<table bgcolor="lightgreen" width="100%" border="1">';
echo '
	<tr>
	<th><font color="Red">Enrollment No</font></th>
	<th><font color="Red">Name</font></th>
	<th><font color="Red">Total Score</font></th>
	</tr>';

while($row = mysql_fetch_array($sql)) {
	echo '<tr>'.'<td>'.$row['Enrollment_No'].'</td>'.'<td>'.$row['Name'].'</td>'.'<td>'.$row['Total'].'</td>'.'</tr>';
}
echo '</table>';
mysql_free_result($sql);
*/
	echo "<h1>".$sql."</h1>";
?>