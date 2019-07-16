<!DOCTYPE html>
<html>
<head>
  <title>Admin Panel</title>
</head>
<link rel="stylesheet" type="text/css" href="../css/admin.css">
<body background="../image/b.png">
    <center>
        <h1>User Database</h1>
  <form method="post" action="update.php">
  <table border="0" width="500" align="center" class="demo-table">
    
    <tr>
      <td>User Name</td><td></td>
      <td><input type="text" class="demoInputBox" name="username" value="<?php if(isset($_POST['username'])) echo $_POST['username']; ?>"></td>
    </tr>
    <tr>
      <td>User ID</td><td></td>
      <td><input type="text" class="demoInputBox" name="userid" value="<?php if(isset($_POST['userid'])) echo $_POST['userid']; ?>"></td>
    </tr>
    <tr>
      <td>Balance</td><td></td>
      <td><input type="text" class="demoInputBox" name="balance" value="<?php if(isset($_POST['balance'])) echo $_POST['balance']; ?>"></td>
    </tr>
    <tr>
    <td><input type="submit" name="register-user" value="Add" class="btnRegister1" formaction="new.php"></td>
    <td><button class="btnRegister2" formaction="del.php">Delete</button></td>
    <td><input type="submit" name="register-user" value="Update" class="btnRegister"></td>
    </tr>
  </table>
</form>
<br><br>
<div>
    
    <table class="blueTable">
<thead>
<tr>
<th>User Name</th>
<th>User ID</th>
<th>Balence</th>
</tr>
</thead>
<tbody>
<tr>
<td>User_1</td>
<td> 35 29 EE 2B</td>
<td><?php
  $file=fopen("b1","r");
  $b1=fread($file,filesize("b1"));
  echo $b1;
  fclose($file);
  ?>
</td>
</tr>
<tr>
<td>User_2</td>
<td> A7 6D 2F BE</td>
<td><?php
  $file=fopen("b2","r");
  $b2=fread($file,filesize("b2"));
  echo $b2;
  fclose($file);
  ?>
</td>
</tr>
<tr>
<td>User_3</td>
<td> C7 A1 38 BE</td>
<td><?php
  $file=fopen("b3","r");
  $b3=fread($file,filesize("b3"));
  echo $b3;
  fclose($file);
  ?>
</td>
</tr>
<tr>
<td>User_4</td>
<td> 61 D5 9D 0A</td>
<td><?php
  $file=fopen("b4","r");
  $b4=fread($file,filesize("b4"));
  echo $b4;
  fclose($file);
  ?>
</td>
</tr>
<tr>
<td>User_5</td>
<td><?php 
  $file=fopen("uid","r");
  $id=fread($file,filesize("uid"));
  echo $id;
  fclose($file);
  ?>
  </td>
<td><?php
  $file=fopen("b5","r");
  $b5=fread($file,filesize("b5"));
  echo $b5;
  fclose($file);
  ?>
</td>
</tr>
</tbody>
</table>
<br>
</div>
<?php
$file=fopen("id","r");
  $id=fread($file,filesize("id"));
  echo"<div style='background-color:powderblue;color:blue;'><h1>"."Last user : ".$id."</h1></div>";
  fclose($file);
?>
</center>

</body>
</html>
