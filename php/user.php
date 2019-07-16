<!DOCTYPE html>
<html>
<head>
  <title>User Panel</title>
</head>
<link rel="stylesheet" type="text/css" href="../css/user.css">
<body class="body" background="../image/a.jpg";>
<?php
$u=$_GET['user'];

if ($u=="user1") {
  $file=fopen("b1","r");
  $b=fread($file,filesize("b1"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else if ($u=="user2") {
  $file=fopen("b2","r");
  $b=fread($file,filesize("b2"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else if ($u=="user3") {
  $file=fopen("b3","r");
  $b=fread($file,filesize("b3"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else if ($u=="user4") {
  $file=fopen("b4","r");
  $b=fread($file,filesize("b4"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else if ($u=="user5") {
  $file=fopen("b5","r");
  $b=fread($file,filesize("b5"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else if ($u=="user6") {
  $file=fopen("b6","r");
  $b=fread($file,filesize("b6"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else if ($u=="user7") {
  $file=fopen("b7","r");
  $b=fread($file,filesize("b7"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else if ($u=="user8") {
  $file=fopen("b8","r");
  $b=fread($file,filesize("b8"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else if ($u=="user9") {
  $file=fopen("b9","r");
  $b=fread($file,filesize("b9"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else if ($u=="user10") {
  $file=fopen("b10","r");
  $b=fread($file,filesize("b10"));
  fclose($file);
  echo ('<div class="user">'."User Name : ".$u." <br> "."Avalable Balance : ".$b."</div>");
}
else{
  echo ('<div class="user">'."No Data Avalable!".'</div>');
}








?>
</body>
</html>