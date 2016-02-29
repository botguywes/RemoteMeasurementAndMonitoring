//
// MJPEG
//
var mjpeg_img;

function reload_img () {
  mjpeg_img.src = "cam_pic.php?time=" + new Date().getTime();
}

function error_img () {
  setTimeout("mjpeg_img.src = 'cam_pic.php?time=' + new Date().getTime();", 100);
}

//
// Ajax Status
//
function createAjaxCommand(){
  var ajax;
  if(window.XMLHttpRequest) {
    ajax = new XMLHttpRequest();
  } else {
    ajax = new ActiveXObject("Microsoft.XMLHTTP");
  }
  return ajax;
}

function reboot() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      //alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=reboot", true);
  ajaxCmd.send();
}

function shutdown() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      //alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=shutdown", true);
  ajaxCmd.send();
}

/*
In the onreadystatechange in the ajaxCmd is where you would change the webpage via the response text
*/

function pan_left() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      //alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=pleft", true);
  ajaxCmd.send();
}

function pan_right() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      //alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=pright", true);
  ajaxCmd.send();
}

function tilt_up() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      //alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=tup", true);
  ajaxCmd.send();
}

function tilt_down() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      //alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=tdown", true);
  ajaxCmd.send();
}

function read_laser() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      alert('Distance to target: ' + ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=rlaser", true);
  ajaxCmd.send();
}

function center() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      //alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=center", true);
  ajaxCmd.send();
}

/*
MySQL commands
*/

function verify_targets() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=vt", true);
  ajaxCmd.send();
}

function clear_targets() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      //alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=ct", true);
  ajaxCmd.send();
}

function display_targets() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      alert(ajaxCmd.responseText);
    }
  };
  ajaxCmd.open("GET", "cmd_func.php?cmd=dt", true);
  ajaxCmd.send();
}

function select_target() {
  var ajaxCmd = createAjaxCommand();
  ajaxCmd.onreadystatechange = function() {
    if(ajaxCmd.readyState == 4 && ajaxCmd.status == 200) {
      alert(ajaxCmd.responseText);
    }
  };

  var obj = document.getElementById('target_name');
  
  if (obj.value == "") {
    alert('Target name field must be filled.');
  }
  else if (obj.value.length >= 16) {
    alert('Target name must be less than 15 characters.');
  }
  else {
    var call = "cmd_func.php?cmd=st&name=";
    ajaxCmd.open("GET", call.concat(obj.value), true);
    ajaxCmd.send();
  }
  
}

//
// Init
//
function init() {

  // mjpeg
  mjpeg_img = document.getElementById("mjpeg_dest");
  mjpeg_img.onload = reload_img;
  mjpeg_img.onerror = error_img;
  reload_img();

}
