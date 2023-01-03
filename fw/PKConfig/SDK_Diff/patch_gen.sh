#!/bin/bash

function help_info(){
	echo ""
	echo "=========================================================================="
	echo "                  ATEN INTERNATIONAL.,CO, LTD.							"
	echo "       IPMI LINUX SDK - PATCH GENERATOR - VERSION $tool_version           "
	echo "=========================================================================="
	echo ""
    echo "SYNOPSIS:"
    echo "  ./patch_gen [old folder] [new folder] [mode:auto|manual] [patch version]"
	echo ""
    echo "EXAMPLE:"
    echo "  ./patch_gen ./old_folder ./new_folder auto p1"
	echo ""
}

function remove_comment(){
	check_ext=`echo "$tmp_filename" | awk -f ext_check.awk`
	
	for i in $ext_checklist
	do
		if [ ! -z $check_ext ] && [ $i = $check_ext ]; then
			echo "remove comment : $tmp_target_data"
			$cmt_remover_bin $tmp_target_data
			echo ""
		fi
	done	
}

function auto_mode(){
	diff --brief -r $old_folder $new_folder | sed -e '/.metadata/d' -e '/SDK_Diff/d' &> $tmp_folder/$cmp_file
	#read the comparison result
	while IFS=\r read current_cmp
	do
	#echo "readline `: $current_cmp"
        tokens=($current_cmp)
        if [ ${tokens[0]} = "Only" ]; then #only one file exists
	    target_data=${tokens[3]}

            if [ ! -z "`echo ${tokens[2]} | grep $new_folder`" ]; then #need to be added
                    target_dir=`echo ${tokens[2]} $new_folder | awk -f path_replace.awk`
                    if [ ! -d $pf_folder/$target_dir ]; then mkdir -p $pf_folder/$target_dir; fi
                    cp -af $new_folder/$target_dir/$target_data $pf_folder/$target_dir/
                    echo "cp -a $force_option \"$pf_folder/$target_dir/$target_data\" \"$target_dir/$target_data\"" >> $patchname
                    echo "Add $target_dir/$target_data" >> $change_log
            else  #remove the old one
                    if [ ! -z "`echo ${tokens[2]} | grep $old_folder`" ]; then
                        target_dir=`echo ${tokens[2]} $old_folder | awk -f path_replace.awk`
                            echo "rm -r $force_option $target_dir/$target_data" >> $patchname
                            echo "Remove $target_dir/$target_data" >> $change_log
                    fi
            fi
        else #two file comparison
            oldver_file=${tokens[1]}
            newver_file=${tokens[3]}
            pf_target_dir=`echo $newver_file $new_folder 2 | awk -f path_replace.awk`
            pf_target_data=`echo $newver_file $new_folder 1 $pf_folder/$pf_target_dir | awk -f path_replace.awk`
            target_data=`echo $newver_file $new_folder | awk -f path_replace.awk`
            dif_file=$pf_target_data.dif

            if [ ! -d $pf_folder/$pf_target_dir ]; then mkdir -p $pf_folder/$pf_target_dir; fi

	    diff -c $oldver_file $newver_file > $dif_file

            check_binary=`head -n 1 $dif_file | grep Binary | grep differ`

            if [ ! -z "$check_binary" ]; then #binary file checking
                    rm -rf $dif_file
                    cp -af $newver_file $pf_folder/$pf_target_dir/
                    echo "cp -a $force_option \"$pf_target_data\" \"$target_data\"" >> $patchname
                    echo "Replace $target_data (Binary)" >> $change_log
            else
                    echo "patch -p1 $target_data $dif_file" >> $patchname
                    echo "Patch $target_data" >> $change_log
            fi
		fi
	done < $tmp_folder/$cmp_file
}

function partial_mode(){
	g++ -o $cmt_remover_bin $cmt_remover_src

	while IFS=\r read line_buf
	do
		if [ -z "$line_buf" ]; then
			continue;
		fi

		tokens=($line_buf)
		current_op=${tokens[0]}
		current_file=${tokens[1]}

#		echo "read line = $current_file"
		tmp_dir=`echo $current_file  "_fake_pattern_" 2 | awk -f path_replace.awk`	
		tmp_target_dir=$tmp_folder/$tmp_dir

		tmp_filename=`echo $current_file  "_fake_pattern_" 1 | awk -f path_replace.awk`
		tmp_target_data=$tmp_target_dir/$tmp_filename

        pf_target_dir=$pf_folder/$tmp_dir
        pf_target_data=$pf_target_dir/$tmp_filename

        old_target_dir=$old_folder/$tmp_dir
        new_target_dir=$new_folder/$tmp_dir

		old_target_data=$old_folder/$current_file
		new_target_data=$new_folder/$current_file

		case "$current_op" in
		Patch)
			if [ -f $new_target_data ]; then
				if [ ! -d $tmp_target_dir ]; then mkdir -p $tmp_target_dir; fi
				cp -af $new_target_data $tmp_target_dir/
				remove_comment;
			fi		

			if [ ! -f $old_target_data ]; then #add a new one
				if [ ! -d $pf_target_dir ]; then mkdir -p $pf_target_dir; fi
	            cp -af $tmp_target_data $pf_target_dir/
				if [ ! -d $old_target_dir ]; then echo "mkdir -p $tmp_dir" >> $patchname; fi
			    echo "cp -a $force_option \"$pf_target_data\" \"$current_file\"" >> $patchname
				echo "Add $current_file" >> $change_log			

			else #patch the old one

				first_diff=`diff --brief $old_target_data $tmp_target_data`
				if [ ! -z "$first_diff" ]; then #differ
					if [ ! -d $pf_target_dir ]; then mkdir -p $pf_target_dir; fi
					dif_file=$pf_target_data.dif
					diff -c $old_target_data $tmp_target_data > $dif_file

		            check_binary=`head -n 1 $dif_file | grep Binary | grep differ`
				    if [ ! -z "$check_binary" ]; then #binary file checking
						    rm -rf $dif_file
		                    cp -af $tmp_target_data $pf_target_dir/
				            echo "cp -a $force_option \"$pf_target_data\" \"$current_file\"" >> $patchname
						    echo "Replace $current_file (Binary)" >> $change_log
		            else
				            echo "patch -p1 $current_file $dif_file" >> $patchname
						    echo "Patch $current_file" >> $change_log
		            fi
				fi

			fi
		;;
		Remove)
			echo "rm -r $force_option $current_file" >> $patchname
			echo "Remove $current_file" >> $change_log
		;;
		esac

	done < $patch_list
}

tool_version=1.1
old_folder=`cd $1;pwd`
new_folder=`cd $2;pwd`
op_mode=$3
patch_ver=$4

tmp_folder=./patch_tmp
pf_folder=./patch_file

cmp_file=cmp_result
patchname=patcher
patch_tar_name=
patch_list=patch_list

cmt_remover_src=./comment_remover.cpp
cmt_remover_bin=./comment_remover

ext_checklist="c h cpp cc java"

default_language="EN"

LANG=$default_language
export LANG

if [ -z $patch_ver ]; then
	patch_tar_name=aten_ipmi_patch.tar.gz
else
	patch_tar_name=aten_ipmi_patch_$patch_ver.tar.gz
fi

change_log=./change.log
force_option=

if [ -z $old_folder ] || [ -z $new_folder ]; then
	help_info;
	exit 0;
fi

if [ ! "$op_mode" = "auto" ] && [ ! "$op_mode" = "partial" ]; then
	help_info;
	exit 0;
fi

if [ ! -d $old_folder ]; then
	echo "folder : $old_folder does not exist"
	exit 0;
fi

if [ ! -d $new_folder ]; then
    echo "folder : $new_folder does not exist"
	exit 0;
fi

if [ "$op_mode" = "partial" ] && [ ! -f $patch_list ]; then
	echo "file : $patch_list does not exist"
	exit 0;
fi

if [ ! -d  $tmp_folder ]; then
	mkdir -p $tmp_folder
else
	rm -rf $tmp_folder/*
fi

if [ ! -d  $pf_folder ]; then
    mkdir -p $pf_folder
else
    rm -rf $pf_folder/*
fi

echo "#Change Log (Last-Modified : `date -u`)" > $change_log

if [ -f $patchname ]; then rm -rf $patchname; fi
if [ -f $patch_tar_name ]; then rm -rf $patch_tar_name; fi


echo "Old Folder : $old_folder"
echo "New Folder : $new_folder"
echo "Output File : $patch_tar_name"

echo "auto patch without any prompt (y/n)"
read auto_mode

if [ $auto_mode = "y" ] || [ $auto_mode = "Y" ]; then
	force_option="-f"
fi

echo "======== Generate patch files ========"

if [ "$op_mode" = "auto" ]; then
	echo "The auto mode is running......"
	auto_mode;
else
	echo "The partial mode is running..."
	partial_mode;
fi

chmod 744 $patchname

echo "======== Package all patch files ========"
tar -czvf $patch_tar_name $patchname $pf_folder $change_log

echo "======== Remove all temporary files ========="
rm -rf $patchname
#rm -rf $tmp_folder
rm -rf $pf_folder 
rm -rf $change_log
rm -rf $cmt_remover_bin

echo "======== Done ========"
