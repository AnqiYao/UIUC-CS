<?php
    $uname = $_POST['username'];
		$password = $_POST['password'];

		$con = mysqli_connect("localhost","root","root","anime_cleaned");
		$result = mysqli_query($con,"SELECT * FROM `users` WHERE `username` = '$uname'");
		if(!$result || mysqli_num_rows($result) == 0){
      include "config.php";
      $sqladv="insert into `users`(`username`,`password`) values('$uname','$password')";
      $smtadv=$pdo->prepare($sqladv);
      $smtadv->execute();
      echo "success";
			header("refresh:1; url= login.php");
		}else{
      echo "Account already registered";
      header("refresh:3; url= register.php");
		}
?>
