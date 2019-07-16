<?php 
	$n=$_POST['n'];
	$p=$_POST['p'];
	
    if ($n=="admin" && $p=="1234") {
    	header("Location: admin.php", true, 301);
    }
    else
    	header("location: user.php?user=$n")
 ?>
