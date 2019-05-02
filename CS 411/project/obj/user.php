<?php
include "config.php";
$sqladv1= "set @rownum:=0";
$smtadv1=$pdo->prepare($sqladv1);
$smtadv1->execute();
$sqladv="select @rownum:=@rownum+1 as `rank`,`username`,`popularity` from `users` order by `popularity` asc limit 200";
$smtadv=$pdo->prepare($sqladv);
$smtadv->execute();
$row=$smtadv->fetchAll();
 ?>
<html lang = "en">
<head>
	<link rel="stylesheet" href="/static/ex.css">
	<link rel="stylesheet" href="/static/demo.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css">
	<title>Anime</title>
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
		<!DOCTYPE html>
		<html>
		<body style = "background: url(https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1533693337&di=b6045d13d6a87bb9dff18e167036230d&imgtype=jpg&er=1&src=http%3A%2F%2Fimg5.duitang.com%2Fuploads%2Fitem%2F201208%2F24%2F20120824184557_HhcCK.thumb.700_0.jpeg);
		background-repeat: no-repeat; background-position: center;">
		>
<br/>
		<table class="table table-striped table-bordered table-hover" style="margin-top: 20px;">
			<tr>
				<th width = "70">rank</th>
				<th width = "1500">username</th>
				<th width = "80">popularity</th>
        <th width = "120"follow> </th>
			</tr>
			<?php foreach ($row as $k=>$r) {
					if($k>=0){
			 ?>
			<tr>
				<td><?php echo "<p> <font color = red font face = 'Verdana' size = '30pt'> $r[rank] </font></p>" ?></td>
				<td><?php echo "<p> <font face = 'Verdana' size = '20pt'> {$r['username']} </font></p>" ?></td>
				<td><?php echo "<p> <font face = 'Verdana' size = '15pt'> {$r['popularity']} </font></p>" ?></td>
        <td><p> <input type ="button" style = "width:120px;height:30px" value = "Follow"> </p></td>
			</tr>
			<?php }} ?>
		</table>
