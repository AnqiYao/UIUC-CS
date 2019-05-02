
<?php
    $uname = $_POST['username'];
		$password = $_POST['password'];

		$con = mysqli_connect("localhost","root","root","anime_cleaned");
		$result = mysqli_query($con,"SELECT * FROM `users` WHERE `username` = '$uname' && `password` = '$password'");
		if(!$result || mysqli_num_rows($result) == 0){
      echo "incorrect password or id";
			header("refresh:3; url= login.php");
		}else if(mysqli_num_rows($result) == 1){
      include "config.php";
      $sqladv="select * from `users` WHERE `username` = '$uname'";
      $smtadv=$pdo->prepare($sqladv);
      $smtadv->execute();
      $row=$smtadv->fetchAll();
      header("Location: profile.php");
		}else{
      echo "incorrect password or id";
			header("refresh:3; url= login.php");
    }
?>
