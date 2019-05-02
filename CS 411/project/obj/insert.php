<?php
include "config.php";
$genre=$_POST['genre']?$_POST['genre']:'';
$rating=$_POST['rating']?$_POST['rating']:'';
$title=$_POST['title']?$_POST['title']:'';
$link=$_POST['link']?$_POST['link']:'';
if($genre && $rating && $title){
  $sqladv="insert into `table`(`COL 2`,`COL 7`,`COL 14`,`COL 16`) values('$title','$rating','$genre','$link')";
  $smtadv=$pdo->prepare($sqladv);
  if($smtadv->execute())
    echo "<script>alert('Successfully Added!')</script>";
}
 ?>


<html lang = "en">
<head>
	<link rel="stylesheet" href="/static/ex.css">
	<link rel="stylesheet" href="/static/demo.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css">
	<title>Insert</title>
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
<body style = "background: url(https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1533691019&di=2830f6144f049c13425e6c1b5d2edf5a&imgtype=jpg&er=1&src=http%3A%2F%2Fimg3.duitang.com%2Fuploads%2Fitem%2F201505%2F12%2F20150512062103_Xsu2J.jpeg);
background-repeat: no-repeat; background-size: cover;">
>
<br>
<br>
<br>
<br>
<br>
<br>


<h2>Text Input</h2>

      	<form action = "insert.php" method="POST">
         Title: <br>
          <input type="text" name="title">
         <br>
         Cover:<br>
         <input type="text" name="link">
         <br>
         Genre:<br>
         <input type="text" name="genre">
         <br>
	       Rating:<br>
	       <input type="text" name="rating" value="<?php echo $rating ?>"><br><br>
	       <input type="submit" value="Insert">
	       <br>
	       </form>


</body>
</html>
