#!/usr/bin/php

<?PHP

if (count($argv) < 2)
	exit();

$s = $argv[1];

$s = preg_replace("/[ \t]+/", " ", $s);

$s = preg_replace("/^[ \t]+/", "", $s);

$s = preg_replace("/[ \t]+$/", "", $s);

echo "$s";

?>
