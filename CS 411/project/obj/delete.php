<?php
include "config.php";
$genre=$_POST['genre']?$_POST['genre']:'';
$rating=$_POST['rating']?$_POST['rating']:'';
if($genre && $rating){
  $sqladv="delete from `table` where `COL 7` = '$rating' and `COL 14` like '%$genre%'";
  $smtadv=$pdo->prepare($sqladv);
  if($smtadv->execute()){
    echo "<script>alert('Successfully Romoved!')</script>";
  }
}
 ?>

<html lang = "en">
<head>
	<link rel="stylesheet" href="/static/ex.css">
	<link rel="stylesheet" href="/static/demo.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css">
	<title>Delete</title>
	<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
</head>
	<nav class="navbar navbar-expand-md navbar-dark fixed-top bg-dark">
      <a class="navbar-brand" href="index.php">Anime</a>
      <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>

      <div class="collapse navbar-collapse" id="navbarsExampleDefault">
        <ul class="navbar-nav mr-auto">
          <li class="nav-item active">
            <a class="nav-link" href="index.php">Home <span class="sr-only">(current)</span></a>
	<li class="nav-item">
    <a class="nav-link" href="Animelist.php">AnimeList</a>

  </li>
	<li class="nav-item">
    <a class="nav-link" href="Search.php">Search</a>

  </li>

  <li class="nav-item">
    <a class="nav-link" href="Insert.php">Insert</a>

  </li>
  <li class="nav-item">
    <a class="nav-link" href="Update.php">Update</a>

  </li>
  <li class="nav-item">
    <a class="nav-link" href="Delete.php">Delete</a>
  </li>
</ul>
</div>
</nav>


<!DOCTYPE html>
<html>
<body style = "background: url(https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1533693494&di=0dd63470e89e0450e7fb4a8dcb485bf4&imgtype=jpg&er=1&src=http%3A%2F%2Fn1.itc.cn%2Fimg8%2Fwb%2Frecom%2F2016%2F03%2F05%2F145716343712633217.JPEG);
background-repeat: no-repeat; background-position: center;">
>
<br>
<br>
<br>
<br>
<br>
<br>

<h2>Text Input</h2>

      	<form action = "delete.php" method="POST">
         Genre:<br>
  	     <input type="text" name="genre" value="<?php echo $genre ?>">
         <br>
	       Rating:<br>
	       <input type="text" name="rating" value="<?php echo $rating ?>"><br><br>
	       <input type="submit" value="Delete">
	       <br>
	       </form>
</body>
</html>
