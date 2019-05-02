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
			<a class="btn btn-bd-download d-none d-lg-inline-block mb-3 mb-md-0 ml-md-3" href="login.php">login</a>
    </nav>

		<!DOCTYPE html>
		<html>
		<body style = "background: url(https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1533693337&di=b6045d13d6a87bb9dff18e167036230d&imgtype=jpg&er=1&src=http%3A%2F%2Fimg5.duitang.com%2Fuploads%2Fitem%2F201208%2F24%2F20120824184557_HhcCK.thumb.700_0.jpeg);
		background-repeat: no-repeat; background-position: center;">
		>




		<?php

		$host="localhost"; // Host name
		$username="root"; // Mysql username
		$password="root"; // Mysql password
		$db_name="myforum"; // Database name
		$tbl_name="fquestions"; // Table name

		// Connect to server and select databse.
		mysql_connect("$host", "$username", "$password")or die("cannot connect");
		mysql_select_db("$db_name")or die("cannot select DB");

		$sql="SELECT * FROM $tbl_name ORDER BY id DESC";
		// OREDER BY id DESC is order result by descending

		$result=mysql_query($sql);
		?>

		<table width="90%" border="0" align="center" cellpadding="3" cellspacing="1" bgcolor="#CCCCCC">
		<tr>
		<td width="6%" align="center" bgcolor="#E6E6E6"><strong>#</strong></td>
		<td width="53%" align="center" bgcolor="#E6E6E6"><strong>Topic</strong></td>
		<td width="15%" align="center" bgcolor="#E6E6E6"><strong>Views</strong></td>
		<td width="13%" align="center" bgcolor="#E6E6E6"><strong>Replies</strong></td>
		<td width="13%" align="center" bgcolor="#E6E6E6"><strong>Date/Time</strong></td>
		</tr>

		<?php

		// Start looping table row
		while($rows = mysql_fetch_array($result)){
		?>
		<tr>
		<td bgcolor="#FFFFFF"><?php echo $rows['id']; ?></td>
		<td bgcolor="#FFFFFF"><a href="view_topic.php?id=<?php echo $rows['id']; ?>"><?php echo $rows['topic']; ?></a><BR></td>
		<td align="center" bgcolor="#FFFFFF"><?php echo $rows['view']; ?></td>
		<td align="center" bgcolor="#FFFFFF"><?php echo $rows['reply']; ?></td>
		<td align="center" bgcolor="#FFFFFF"><?php echo $rows['datetime']; ?></td>
		</tr>

		<?php
		// Exit looping and close connection
		}
		mysql_close();
		?>

		<tr>
		<td colspan="5" align="right" bgcolor="#E6E6E6"><a href="new_topic.php"><strong>Create New Topic</strong> </a></td>
		</tr>
		</table>
