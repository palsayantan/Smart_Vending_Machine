<?php

$id=$_GET['uid'];
$m=$_GET['mod'];

$x=5;
$y=10;

 $file=fopen("mode","w"); //mode save here
 fwrite($file,$m);
 fclose($file);

 $file=fopen("id","w"); //id save here
 fwrite($file,$id);
 fclose($file);

if ($id=="user1" && $m=="a") {
  $file=fopen("b1","r");
  $bal=fread($file,filesize("b1"));
  fclose($file);
  if ($bal>10) {
    $file=fopen("b1","w"); 
      $b=($bal-$x);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b1","r");
          $b=fread($file,filesize("b1"));
            if ($b>10) {
              echo $b;
              }
            }
            else{
              echo "lb";
            }
}
else if ($id=="user1" && $m=="b") {
  $file=fopen("b1","r");
  $bal=fread($file,filesize("b1"));
  fclose($file);
  if ($bal>10) {
  $file=fopen("b1","w");
      $b=($bal-$y);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b1","r");
          $b=fread($file,filesize("b1"));
            if ($b>10) {
              echo $b;
            }
          }
            else{
              echo "lb";
            }
}
else if ($id=="user1" && $m=="x") {
          $file=fopen("b1","r");
          $b=fread($file,filesize("b1"));
          echo $b;
}

else if ($id=="user2" && $m=="a") {
  $file=fopen("b2","r");
  $bal=fread($file,filesize("b2"));
  fclose($file);
  if ($bal>10) {
  $file=fopen("b2","w");
      $b=($bal-$x);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b2","r");
          $b=fread($file,filesize("b2"));
            if ($b>10) {
              echo $b;
            }
          }
            else{
              echo "lb";
            }
}
else if ($id=="user2" && $m=="b") {
  $file=fopen("b2","r");
  $bal=fread($file,filesize("b2"));
  fclose($file);
  if ($bal>10) {
  $file=fopen("b2","w");
      $b=($bal-$y);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b2","r");
          $b=fread($file,filesize("b2"));
            if ($b>10) {
              echo $b;
            }
          }
            else{
              echo "lb";
            }
}
else if ($id=="user2" && $m=="x") {
          $file=fopen("b2","r");
          $b=fread($file,filesize("b2"));
          echo $b;

}

else if ($id=="user3" && $m=="a") {
  $file=fopen("b3","r");
  $bal=fread($file,filesize("b3"));
  fclose($file);
  if ($bal>10) {
  $file=fopen("b3","w");
      $b=($bal-$x);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b3","r");
          $b=fread($file,filesize("b3"));
            if ($b>10) {
              echo $b;
            }
          }
            else{
              echo "lb";
            }

}
else if ($id=="user3" && $m=="b") {
  $file=fopen("b3","r");
  $bal=fread($file,filesize("b3"));
  fclose($file);
  if ($bal>10) {
  $file=fopen("b3","w");
      $b=($bal-$y);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b3","r");
          $b=fread($file,filesize("b3"));
            if ($b>10) {
              echo $b;
            }
          }
            else{
              echo "lb";
            }

}
else if ($id=="user3" && $m=="x") {
          $file=fopen("b3","r");
          $b=fread($file,filesize("b3"));
          echo $b;


}

else if ($id=="user4" && $m=="a") {
  $file=fopen("b4","r");
  $bal=fread($file,filesize("b4"));
  fclose($file);
  if ($bal>10) {
  $file=fopen("b4","w");
      $b=($bal-$x);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b4","r");
          $b=fread($file,filesize("b4"));
            if ($b>10) {
              echo $b;
            }
          }
            else{
              echo "lb";
            }

}
else if ($id=="user4" && $m=="b") {
  $file=fopen("b4","r");
  $bal=fread($file,filesize("b4"));
  fclose($file);
  if ($bal>10) {
  $file=fopen("b4","w");
      $b=($bal-$y);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b4","r");
          $b=fread($file,filesize("b4"));
            if ($b>10) {
              echo $b;
            }
          }
            else{
              echo "lb";
            }

}
else if ($id=="user4" && $m=="x"){ 
          $file=fopen("b4","r");
          $b=fread($file,filesize("b4"));
          echo $b;
}
else if ($id=="user5" && $m=="a") {
  $file=fopen("b5","r");
  $bal=fread($file,filesize("b5"));
  fclose($file);
  if($bal>0){
  $file=fopen("b5","w");
      $b=($bal-$x);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b5","r");
          $b=fread($file,filesize("b5"));
            if ($b>10) {
              echo $b;
            }
            else
              echo "lb";
            }
    else
        echo "nd";
}

else if ($id=="user5" && $m=="b") {
  $file=fopen("b5","r");
  $bal=fread($file,filesize("b5"));
  fclose($file);
  if($bal>0){
  $file=fopen("b5","w");
      $b=($bal-$y);
      fwrite($file,$b);
      fclose($file);
          $file=fopen("b5","r");
          $b=fread($file,filesize("b5"));
            if ($b>10) {
              echo $b;
            }
            else
              echo "lb";
            }
    else
        echo "nd";
}

else if ($id=="user5" && $m=="x") {
          $file=fopen("b5","r");
          $b=fread($file,filesize("b5"));
          if ($b>0) {
              echo $b;
            }
            else
              echo "nd";
}

  else echo "nd";



    

?>