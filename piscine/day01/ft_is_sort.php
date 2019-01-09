<?PHP

function ft_is_sort($array)
{
	for ($i = 1; $i < count($array); $i++)
	{
		if ($array[$i - 1] > $array[$i])
			return False;
	}
	return True;
}

?>
