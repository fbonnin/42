#!/usr/bin/php

<?PHP

include("ft_is_sort.php");

$tab = array("!/@#;^", "42", "Hello World", "salut", "zZzZzZz");
$tab[] = "Et qu'est-ce qu'on fait maintenant ?";

if (ft_is_sort($tab))
	echo "trie\n";
else
	echo "pas trie\n";

?>
