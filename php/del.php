<?php
    $name=$_POST['username'];
    $id=" ";
    if ($name=="user5") {
    $file=fopen("b5","r");
    $bal=fread($file,filesize("b5"));

      $file=fopen("b5","w"); 
      $b=$bal-$bal;
      fwrite($file,$b);
      fclose($file);

      $file=fopen("uid","w"); 
      fwrite($file,$id);
      fclose($file);
    }
    header("Refresh: 1; url=admin.php");
?>