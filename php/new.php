<?php
    $name=$_POST['username'];
    $id=$_POST['userid'];
    $bal=$_POST['balance'];

    if ($name=="user5") {
    $file=fopen("b5","r");
    $b1=fread($file,filesize("b5"));

      $file=fopen("b5","w"); 
      $b=$bal+$b1;
      fwrite($file,$b);
      fclose($file);

      $file=fopen("uid","w"); 
      fwrite($file,$id);
      fclose($file);
    }
    header("Refresh: 1; url=admin.php");
?>