<!DOCTYPE html>
<html lang = "en">
<body style = "background: url(https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1533694155&di=304272bb9294871747d7e625ef7cae99&imgtype=jpg&er=1&src=http%3A%2F%2Fimg1.3lian.com%2F2015%2Fa2%2F226%2Fd%2F306.jpg);
background-repeat: no-repeat; background-position: right;">
>
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="/static/ex.css">
    <link rel="stylesheet" href="/static/demo.css">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css">
    <title>advance1</title>
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
    <main role="main" style="margin-top: 80px;padding-left: 8px">
        <form action="result.php" method='post'>
            <p>
                gender ：
               <label>
                   <input type="radio" name="sex" id="optionsRadios2" value="Male" checked>
                   male
               </label>
               <label>
                   <input type="radio" name="sex" id="optionsRadios2" value="Female">
                   female
               </label>
            </p>
            <p>
                birth date :
                <input type="text" name='birth'> ( eg.1990 )
            </p>
            <p>
                episode : &nbsp;&nbsp;
                <input type="text" name='episode'> (The amount of episodes you prefer)
            </p>
            <p>
                type : &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <!-- <input type="text" name='type'> (Choose from TV【】Movie【】OVA【】ONA【】Special【】Music【】Unknown) -->
                <label>
                    <input type="radio" name="type" id="optionsRadios2" value="TV" checked>
                    TV
                </label>
                <label>
                    <input type="radio" name="type" id="optionsRadios2" value="Movie" checked>
                    Movie
                </label>
                <label>
                    <input type="radio" name="type" id="optionsRadios2" value="OVA" checked>
                    OVA
                </label>
                <label>
                    <input type="radio" name="type" id="optionsRadios2" value="ONA" checked>
                    ONA
                </label>
                <label>
                    <input type="radio" name="type" id="optionsRadios2" value="Special" checked>
                    Special
                </label>
            </p>
            <p>
                genre : &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <!-- <input type="text" name='genre'> (Comedy【】Romance【】Drama【】Fantasy【】Action【】Music【】Adventure【】Sci-Fi【】Horror【】Psychological【】Military) -->
                <label>
                    <input type="radio" name="genre" id="optionsRadios2" value="Comedy" checked>
                    Comedy
                </label>
                <label>
                    <input type="radio" name="genre" id="optionsRadios2" value="Romance" checked>
                    Romance
                </label>
                <label>
                    <input type="radio" name="genre" id="optionsRadios2" value="Drama" checked>
                    Drama
                </label>
                <label>
                    <input type="radio" name="genre" id="optionsRadios2" value="Fantasy" checked>
                    Fantasy
                </label>
                <label>
                    <input type="radio" name="genre" id="optionsRadios2" value="Action" checked>
                    Action
                </label>
                <label>
                    <input type="radio" name="genre" id="optionsRadios2" value="Adventure" checked>
                    Adventure
                </label>
                <label>
                    <input type="radio" name="genre" id="optionsRadios2" value="Sci-Fi" checked>
                    Sci-Fi
                </label>
                <label>
                    <input type="radio" name="genre" id="optionsRadios2" value="Horror" checked>
                    Horror
                </label>
            </p>
            <input type="submit" value="submit">
        </form>
    </main>
<style>
    input[type='text']{
        padding-left: 3px;
        border-radius:3px;
    }
</style>
