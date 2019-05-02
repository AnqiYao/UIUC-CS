<?php
include "config.php";
$genre=$_POST['genre']?$_POST['genre']:'';
$rating=$_POST['rating']?$_POST['rating']:'';
$title = $_POST['title']?$_POST['title']:'';
$mysqli = new mysqli( 'localhost', 'root', 'root', 'anime_cleaned' );
$mysqli->set_charset( 'charset');
$genre = $mysqli->real_escape_string( $genre );
$title = $mysqli->real_escape_string( $title );
if($genre && $rating){
  $sqladv="select * from `table` where `COL 7`='$rating' and `COL 14` like '%$genre%'";
  $smtadv=$pdo->prepare($sqladv);
  $smtadv->execute();
  $row=$smtadv->fetchAll();
}
if($title){
  $sqladv="select * from `table` where `COL 2` like '%$title%'";
  $smtadv=$pdo->prepare($sqladv);
  $smtadv->execute();
  $row=$smtadv->fetchAll();
}
 ?>

<html lang = "en">
<head>
	<link rel="stylesheet" href="/static/ex.css">
	<link rel="stylesheet" href="/static/demo.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css">
	<title>Search</title>
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
<body style = "background: url(https://ss2.bdstatic.com/70cFvnSh_Q1YnxGkpoWK1HF6hhy/it/u=2897595404,549461784&fm=27&gp=0.jpg);
background-repeat: no-repeat; background-position: center;">
>
<br>
<br>
<br>
<br>
<br>
<br>

<h2>Text Input</h2>

      	<form action = "search.php" method="POST">
         Anime Name:<br>
   	     <input type="text" name="title" value="<?php echo $title ?>">
          <br>
         Genre:<br>
  	     <input type="text" name="genre" value="<?php echo $genre ?>">
         <br>
	       Rating:<br>
	       <input type="text" name="rating" value="<?php echo $rating ?>"><br><br>
	       <input type="submit" value="Find">
	       <br>
	       </form>
         <p>
         </p>
         <div class="panel">
          <table class="table table-striped table-bordered table-hover" style="margin-top: 70px;">
            <?php if($genre||$title){foreach ($row as $k=>$r) {
             ?>
             <tr>
               <td><?php echo "<p> <font face = 'Verdana' size = '8pt'> {$r['COL 1']} </font></p>" ?></td>
               <td><?php echo "<p> <font face = 'Verdana' size = '6pt'> {$r['COL 2']} </font></p>" ?></td>
       		<td><img src= "<?php echo $r['COL 16'];?>" width = "90" height = "150"></td>
               <td><?php echo "<p> <font face = 'Verdana' size = '8pt'> {$r['COL 7']} </font></p>" ?></td>
               <td><?php echo "<p> <font face = 'Verdana' size = '3pt'> {$r['COL 14']} </font></p>" ?></td>
             </tr>
            <?php }} ?>
          </table>
         </div>

</body>
</html>
