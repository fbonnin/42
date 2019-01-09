#!/usr/bin/php

<?PHP

while (True)
{
	echo "Entrez un nombre: ";
	$line = readline();
	$is_number = True;
	if ($line == "")
		$is_number = False;
	for ($i = 0; $i < strlen($line); $i++)
	{
		if ($line[$i] < '0' || $line[$i] > '9')
		{
			$is_number = False;
		}
	}
	if ($is_number == False)
	{
		echo "'$line' n'est pas un chiffre";
	}
	else
	{
		echo "Le chiffre $line est ";
		if (intval($line) % 2 == 0)
		{
			echo "Pair"; 
		}
		else
		{
			echo "Impair";
		}
	}
	echo "\n";
}

?>
