#ext_check.awk

function r_index(string, find)
{
    ns = length(string);
    nf = length(find);
    for(k = ns + 1 - nf; k >= 1; k--)
        if(substr(string, k, nf) == find)
            return k
    return 0;
}

function ext_check(filename)
{
	dot_index = r_index(filename, ".");
	if(dot_index > 0)
		print substr(filename, dot_index+1);
	
}

{
	ext_check($1);
}
