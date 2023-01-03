#path_replace.awk

function r_index(string, find)
{
	ns = length(string);
	nf = length(find); 
	for(k = ns + 1 - nf; k >= 1; k--)
		if(substr(string, k, nf) == find)
			return k
	return 0;
}

function do_replace(origin_str, str_pattern, mode, filepath)
{
	target_file="";

	if(index(origin_str, str_pattern) || str_pattern == "_fake_pattern_"){
		sub(str_pattern, "", origin_str);

		if(index(origin_str,":"))
			sub(":", "", origin_str);

		if(mode == "1")
		{
			last_index = r_index(origin_str, "/");

			if(filepath != "")
				target_file = filepath "/" substr(origin_str, last_index+1);
			else
				target_file = substr(origin_str, last_index+1);

			print target_file
			return ;
		}
		else if(mode == "2")
		{
			last_index = r_index(origin_str, "/");
			origin_str = substr(origin_str, 1, last_index-1)
		}

		if(index(origin_str, "/") == 1)
			print "."origin_str
		else
			print "./"origin_str

	}
}

{
	do_replace($1, $2, $3, $4)
}
