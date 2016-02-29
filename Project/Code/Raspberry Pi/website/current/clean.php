<!DOCTYPE html>
<html>
  <head>
    <title>New Spin RMS</title>
    <script src="script_min.js"></script>
    <link rel="stylesheet" href="styles.css">
    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css">

    <!-- Optional theme -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap-theme.min.css">

    <!-- Latest compiled and minified JavaScript -->
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/js/bootstrap.min.js"></script>
  </head>
  
  <body background="nice_snow_@2x.png" onload="setTimeout('init();', 100);">

    <nav class="navbar navbar-default" role="navigation">
      <div class="container-fluid">
        <!-- Brand and toggle get grouped for better mobile display -->
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="http://www.newspin.com">
            <img src="ns_logo.jpeg" width="25" height="30">
          </a>
        </div>

        <!-- Collect the nav links, forms, and other content for toggling -->
        <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
          <ul class="nav navbar-nav">
            <li class="active"><a href="clean.php">Home<span class="sr-only">(current)</span></a></li>
            <li><a href="targeting.php">Targeting</a></li>
            <li><a href="stream.php">Stream</a></li>
            <li><a href="configuration.php">Config</a></li>
          </ul>
        </div><!-- /.navbar-collapse -->
      </div><!-- /.container-fluid -->
    </nav>



      <div class="page-header">
        <center> <h1>New Spin Remote Measurement Tool</h1> </center>
      </div> 

      <div>
        <center>
          <img id="mjpeg_dest" />
        </center>
      </div>

      <div>
        <center>

        <br>
        <br>

        <table style="width:10%">
          <tr>
            <td></td>
            <td><center><button type='button' class="myBtn btn btn-info btn-lg" id='tilt_up' onClick='tilt_up();'><span class="glyphicon glyphicon-arrow-up" aria-hidden="true"></span></button></td>
            <td></td>
          </tr>
          <tr>
            <td><center><button type='button' class="myBtn btn btn-info btn-lg" id='pan_left' onClick='pan_left();'><span class="glyphicon glyphicon-arrow-left" aria-hidden="true"></span></button></center></td>

            <td><center><button type='button' class="myBtn btn btn-info btn-lg" id='measure_lrf' onClick='read_laser();'><span class="glyphicon glyphicon-screenshot" aria-hidden="true"></span></button></center></td>

            <td><center><button type='button' class=" myBtn btn btn-info btn-lg" id='pan_right' onClick='pan_right();'><span class="glyphicon glyphicon-arrow-right" aria-hidden="true"></span></button></center></td>
          </tr>
          <tr>
            <td></td>
            <td><center><button type='button' class="myBtn btn btn-info btn-lg" id='tilt_down' onClick='tilt_down();'><span class="glyphicon glyphicon-arrow-down" aria-hidden="true"></span></button></center></td>
            <td></td>
          </tr>
        </table>

        <br>
        
        <button type='button' class="btn btn-info btn-log" id='center' onClick='center();'><span class="glyphicon glyphicon-star-empty" aria-hidden="true"></span> Center System</button>
        
        <br>
        <br>
        <br>
        </center>

        
      </div>
  </body>
</html>