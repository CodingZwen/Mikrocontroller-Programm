<!DOCTYPE html>
<html>
<head>

<style type="text/css">

.main
{
background-color: #FF0077;
}


</style>



</head>


<body>

<div class="main">

<h2>Hallo, wie lange sind Ihre Skier?</h2>
</div>

<form>
<input type="text" name ="filepath" value="Dateiname eingeben">
<input type="submit" name="send" value="Los!">

</form>


<?php
include ('Rechteck.php');
$rel = new Rechteck();
$rel->SeiteA=1.5;
$rel->SeiteB=5.2;

echo "Das ergebnis ist". $rel->showFlaeche();

if(isset($_REQUEST['send']))
{
	
	
	
	
	$pfad = $_REQUEST['filepath'];
	
	
	filereader($pfad);
	
}


function filereader($pfad)
{

	$count = 0;
	$bsuccess;
	$pointer = @fopen($pfad,'r'); //or die("wont open file")
	
	if(file_exists($pfad))
	{
		
	
	while(!feof($pointer))
	{
	$count++;
	$zeile = fgets($pointer);
	echo $zeile;
	echo "<br>";
	}
	
	echo "<br>";
	echo "Anzahl der durchläufe: ".$count;
	
	
	
	fclose($pointer);
	
	}else {
		echo "Sie sind behindert";
	}
}



?>


</body>


</html>
