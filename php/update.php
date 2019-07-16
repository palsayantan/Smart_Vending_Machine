<?php 

    $name=$_POST['username'];
    $id=$_POST['userid'];
    $bal=$_POST['balance'];

    
    if ($name=="user1") {
    $file=fopen("b1","r");
    $b1=fread($file,filesize("b1"));

      $file=fopen("b1","w"); 
      $b=$bal+$b1;
      fwrite($file,$b);
      fclose($file);
    }
    if ($name=="user2") {
    $file=fopen("b2","r");
    $b1=fread($file,filesize("b2"));

      $file=fopen("b2","w"); 
      $b=$bal+$b1;
      fwrite($file,$b);
      fclose($file);
    }
    if ($name=="user3") {
    $file=fopen("b3","r");
    $b1=fread($file,filesize("b3"));

      $file=fopen("b3","w"); 
      $b=$bal+$b1;
      fwrite($file,$b);
      fclose($file);
    }
    if ($name=="user4") {
    $file=fopen("b4","r");
    $b1=fread($file,filesize("b4"));

     $file=fopen("b4","w"); 
      $b=$bal+$b1;
      fwrite($file,$b);
      fclose($file);
    }
    if ($name=="user5") {
      if ($id) {
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
      else{
          echo "User Does not exist";
      }
    }
    header("Refresh: 1; url=admin.php");
 ?>