<?php
  
  function sys_cmd($cmd, $name) {
    $val = "none"; 

    if(strncmp($cmd, "reboot", strlen("reboot")) == 0) {
      shell_exec('sudo shutdown -r now');
    } else if(strncmp($cmd, "shutdown", strlen("shutdown")) == 0) {
      shell_exec('sudo shutdown -h now');
    } else if(strncmp($cmd, "rlaser", strlen("rlaser")) == 0) {
      $val = shell_exec('sudo python serial/serialAll.py r 1');
    } else if(strncmp($cmd, "pleft", strlen("pleft")) == 0) {
      shell_exec('sudo python serial/serialAll.py p 1');
    } else if(strncmp($cmd, "pright", strlen("pright")) == 0) {
      shell_exec('sudo python serial/serialAll.py p 2');
    } else if(strncmp($cmd, "tup", strlen("tup")) == 0) {
      shell_exec('sudo python serial/serialAll.py t 1');
    } else if(strncmp($cmd, "tdown", strlen("tdown")) == 0) {
      shell_exec('sudo python serial/serialAll.py t 2');
    } else if(strncmp($cmd, "center", strlen("center")) == 0) {
      shell_exec('sudo python serial/serialAll.py p 90; sudo python serial/serialAll.py t 90');
    } else if(strncmp($cmd, "ct", strlen("ct")) == 0) {
      shell_exec('sudo python nslaser_mysql.py c');
    } else if(strncmp($cmd, "st", strlen("st")) == 0) {
      $val = shell_exec('sudo python nslaser_mysql.py w '.$name);
    } else if(strncmp($cmd, "vt", strlen("vt")) == 0) {
      $val = shell_exec('sudo python nslaser_mysql.py v');
    } else if(strncmp($cmd, "dt", strlen("dt")) == 0) {
      $val = shell_exec('sudo python nslaser_mysql.py d');
    } else {
      $val = "Unknown command";
    }

    return $val;
  }

  $retVal = "none-out";
  if(isset($_GET['cmd'])) {
    $cmd=$_GET['cmd'];

    $name = "none";
    if(isset($_GET['name'])){
      $name=$_GET['name'];
    }
    $retVal = sys_cmd($cmd, $name);
  }
  echo $retVal;

?>