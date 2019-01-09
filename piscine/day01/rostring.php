#!/usr/bin/php

<?PHP

function ft_split($s)
{
	$nb_words = 0;
	$mode = 0;
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
	return $result;
}

$array = ft_split($argv[1]);
$c = count($array);

for ($i = 1; $i < count($array); $i++)
{
	echo "$array[$i] ";
}

echo "$array[0]";

?>
