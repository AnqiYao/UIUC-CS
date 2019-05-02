<?php
include 'config.php';
$data=$_POST;

$sex=$data['sex'];
$birth=$data['birth'];
$episode=$data['episode'];
$type=$data['type'];
$genre=$data['genre'];
 
 $sqldel1="drop view smnewTable1";
 $sc1=$pdo->prepare($sqldel1);
 $sc1->execute();
 $sqldel2="drop view newTable1";
 $sc2=$pdo->prepare($sqldel2);
 $sc2->execute();
 $sqldel3="drop view newTable3";
 $sc3=$pdo->prepare($sqldel3);
 $sc3->execute();
 $sqldel4="drop view newTable4";
 $sc4=$pdo->prepare($sqldel4);
 $sc4->execute();
 $sqldel5="drop view bigTable1";
 $sc5=$pdo->prepare($sqldel5);
 $sc5->execute();
 $sqldel6="drop view bigTable2";
 $sc6=$pdo->prepare($sqldel6);
 $sc6->execute();
 $sqldel7="drop view bigTable3";
 $sc7=$pdo->prepare($sqldel7);
 $sc7->execute();



$smsql1="CREATE VIEW smnewTable1 AS
          SELECT users_final_demo.`Field_0` as Uname
          FROM `users_final_demo`
          where users_final_demo.`Field_2`='{$sex}' and users_final_demo.`Field_3` like '%{$birth}'
          limit 20";
$smt1=$pdo->prepare($smsql1);
$smt1->execute();


$sql1="CREATE VIEW newTable1 AS
      SELECT `smnewTable1`.`Uname` as Uname1, `animelists_final_demo`.`Field_1` as Uid1
      FROM `smnewTable1` inner join `animelists_final_demo` on `smnewTable1`.`Uname`=`animelists_final_demo`.`Field_0`
      order by smnewTable1.`Uname`";

$smt2=$pdo->prepare($sql1);
$smt2->execute();




$sql3="CREATE VIEW bigTable1 AS
      SELECT `table`.`COL 1` as id
      FROM `table`
      where `table`.`COL 3`='{$type}' and `table`.`COL 5` <= '{$episode}' and `table`.`COL 14` like '%{$genre}%'
      order by `table`.`COL 1`";

$smt3=$pdo->prepare($sql3);
$smt3->execute();


$sql4="CREATE VIEW bigTable2 AS
      SELECT `newTable1`.`Uname1` as Uname2, `newTable1`.`Uid1` as Uid2
      FROM `newTable1`
      where `newTable1`.`Uid1` in (SELECT * from `bigTable1`)";

  $smt4=$pdo->prepare($sql4);
  $smt4->execute();


   $sql5="CREATE VIEW bigTable3 AS
          SELECT `bigTable2`.`Uid2` as Fid, count(`BigTable2`.`Uname2`) as numP
          FROM `bigTable2`
          GROUP BY `bigTable2`.`Uid2`";

     $smt5=$pdo->prepare($sql5);
     $smt5->execute();



$sql3 = "CREATE VIEW newTable3 AS
         SELECT `newTable1`.`Uid1` as Fid, count(`newTable1`.`Uname1`) as numP
         FROM `newTable1`
         GROUP BY `newTable1`.`Uid1`";
$smt3=$pdo->prepare($sql3);
$smt3->execute();


$sql6= "CREATE VIEW newTable4 AS
          SELECT `newTable3`.`Fid` as id
          FROM `newTable3`
          order by `newTable3`.`numP` DESC
          limit 6";

      $smt6=$pdo->prepare($sql6);
      $smt6->execute();


$sql7=  "SELECT `COL 2`, `COL 16` FROM `table`, `newTable4`
         WHERE `table`.`COL 1` = `newTable4`.`id`";

      $smt7=$pdo->prepare($sql7);
      $smt7->execute();
      $row=$smt7->fetchAll();

?>
<html lang = "en">
<head>
	<link rel="stylesheet" href="/static/ex.css">
	<link rel="stylesheet" href="/static/demo.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css">
	<title>AnimeList</title>
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
     <table class="table table-striped table-bordered table-hover" style="margin-top: 70px;">
       <tr>
         <th width = "20">Recommandation</th>
         <th width = "70">cover</th>
       </tr>
       <?php foreach ($row as $k=>$r) {
           if($k>=1){
        ?>
       <tr>
         <td><?php echo "<p> <font face = 'Verdana' size = '14pt'> {$r['COL 2']} </font></p>" ?></td>
     <td><img src= "<?php echo $r['COL 16'];?>" width = "90" height = "150"></td>
       </tr>
       <?php }} ?>
     </table>
