#!/usr/bin/php

<?PHP

function ft_split($s)
{
	$nb_words = 0;
	$mode = 0;
	$result = array();
	for ($i = 0; $i < strlen($s); $i++)
	{
		if ($s[$i] != ' ')
		{
			if ($mode == 0)
			{
				$word = $s[$i];
			}
			else
			{
				$word = $word . $s[$i];
			}
			$mode = 1;
		}
		else
		{
			if ($mode == 1)
			{
				$result[$nb_words] = $word;
				$nb_words++;
			}
			$mode = 0;
		}
	}
	if ($mode == 1)
	{
		$result[$nb_words] = $word;
	}
	sort($result);
	return $result;
}

$total = "";

for ($i = 1; $i < count($argv); $i++)
{
	$total = $total . $argv[$i] . " ";
}


$array = ft_split($total);

for ($i = 0; $i < count($array); $i++)
{
	echo "$array[$i]\n";
}

?>
