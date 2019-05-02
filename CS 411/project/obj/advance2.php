<!DOCTYPE html>
<?php
include "config.php";
$sqladv1= "set @rownum:=-1";
$smtadv1=$pdo->prepare($sqladv1);
$smtadv1->execute();
$sqladv= "select @rownum:=@rownum+1 as `rank`, `COL 2`,`COL 7`, `COL 8`, `COL 16` from `table` order by `COL 8` DESC  limit 51;";
$smtadv=$pdo->prepare($sqladv);
$smtadv->execute();
$row=$smtadv->fetchAll();
 ?>

<html lang = "en">
<head>
	<link rel="stylesheet" href="/static/ex.css">
	<link rel="stylesheet" href="/static/demo.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css">
	<title>advance 2</title>
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
          </li>
          <li class="nav-item">
            <a class="nav-link" href="Animelist.php">AnimeList</a>

	  </li>

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
    <div class="jumbotron">
      <div class="container">
        <h2 class="display-3">Hello, This is the TOP 50 animes right now and it's keep updating!!</h2>
      </div>
    </div>

	<html>
    <body>

         <div class="container">
           <div class="row">
             <div class="col-md-8">
               <h2>Vote for your favorite one</h2>
                     <form action = "function2do.php" method="POST">
                     anime_name: <br>
                     <input type="text" name="anime_name">
                    <input type="submit" value="vote">
                    <br>
                    </form>
             </div>

           </div>
    </body>
    </html>

		<table class="table table-striped table-bordered table-hover" style="margin-top: 20px;">
			<tr>
				<th width = "70">rank</th>
				<th width = "150">title</th>
				<th width = "100">image</th>
				<th width = "80">favorite</th>
				<th width = "80">score</th>
			</tr>
			<?php foreach ($row as $k=>$r) {
					if($k>=1){
			 ?>
			<tr>
				<td><?php echo "<p> <font color = red font face = 'Verdana' size = '30pt'> $r[rank] </font></p>" ?></td>
				<td><?php echo "<p> <font face = 'Verdana' size = '20pt'> {$r['COL 2']} </font></p>" ?></td>
				<td><img src= "<?php echo $r['COL 16'];?>" width = "120" height = "200"></td>
				<td><?php echo "<p> <font face = 'Verdana' size = '15pt'> {$r['COL 8']} </font></p>" ?></td>
				<td><?php echo "<p> <font face = 'Verdana' size = '15pt'> {$r['COL 7']} </font></p>" ?></td>

			</tr>
			<?php }} ?>
		</table>
