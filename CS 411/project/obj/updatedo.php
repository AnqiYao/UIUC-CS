<?php
include "config.php";
$anime_id=$_POST['anime_id']?$_POST['anime_id']:'';
if($anime_id){
  $sqladv="select * from `table` where `COL 1`=".$anime_id;
  $smtadv=$pdo->prepare($sqladv);
  $smtadv->execute();
  $row=$smtadv->fetch();
}


$type=$_POST['type']?$_POST['type']:'';
if($type){
  $genre=$_POST['genre1']?$_POST['genre1']:'';
  $rating=$_POST['rating1']?$_POST['rating1']:'';
  $link=$_POST['link1']?$_POST['link1']:'';
  $title=$_POST['title1']?$_POST['title1']:'';
  $anime_id=$_POST['anime_id1']?$_POST['anime_id1']:'';
  if($genre && $rating && $link && $title && $anime_id){
    $sqladv="update `table` set `COL 1`='$anime_id',`COL 2`='$title',`COL 7`='$rating',`COL 14`='$genre', `COL 16`='$link'WHERE `COL 1` ='$anime_id'";
    $smtadv=$pdo->prepare($sqladv);
    if($smtadv->execute())
      echo "<script>alert('Successfully Modified!');location.href='update.php'</script>";
  }
}
 ?>

<html lang = "en">
<body style = "background: url(https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1533693337&di=b6045d13d6a87bb9dff18e167036230d&imgtype=jpg&er=1&src=http%3A%2F%2Fimg5.duitang.com%2Fuploads%2Fitem%2F201208%2F24%2F20120824184557_HhcCK.thumb.700_0.jpeg);
background-repeat: no-repeat; background-position: center;">
>
<head>
	<link rel="stylesheet" href="/static/ex.css">
	<link rel="stylesheet" href="/static/demo.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css">
	<title>Update</title>
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
<a class="btn btn-bd-download d-none d-lg-inline-block mb-3 mb-md-0 ml-md-3" href="login.php">login</a>
</nav>


<!DOCTYPE html>
<html>
<body>
<br>
<br>
<br>
<br>
<br>
<br>

<h2>Text Input</h2>

      	<form action = "updatedo.php" method="POST">
         Anime_id: <br>
          <input type="text" name="anime_id1" value="<?php echo $row['COL 1'] ?>">
         <br>
         Title: <br>
          <input type="text" name="title1" value="<?php echo $row['COL 2'] ?>">
         <br>
         Cover:<br>
         <input type="text" name="link1" value="<?php echo $row['COL 16'] ?>">
         <br>
         Genre:<br>
         <input type="text" name="genre1" value="<?php echo $row['COL 14'] ?>">
         <br>
	       Rating:<br>
	       <input type="text" name="rating1" value="<?php echo $row['COL 7'] ?>"><br><br>
         <input type="hidden" name="type" value='1'>
	       <input type="submit" value="update">
	       <br>
	       </form>

</body>
</html>
