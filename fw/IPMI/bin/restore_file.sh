#!/bin/sh
PATH=/SMASH:/SFCB/local/bin:/SFCB/local/sbin:/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin
export PATH

#1.for factory default setting
#rm_files is defined in SM_SRC\Utils\Host\HERMON\Board\(board defined)\define_var.sh
UPLOAD_TMP_FILE="upload_config_tmp.tar.gz"
source define_var.sh

if [ $1 == '1' ]; then
	
	for file in $rm_files
	do
		if [ -f "/nv/"$file ];then
			rm -r "/nv/"$file 
		fi
	done
#2.for save ipmi config
#process who calls this script need to putenv of $SAVE_CONF_DIR $TARGET_FOLDER $SAVE_TAG_PATH...
elif [ $1 == '0' ]; then
	for file in $cp_files 
	do
		if [ ! -d "$SAVE_CONF_DIR/$TARGET_FOLDER" ]; then
			mkdir $SAVE_CONF_DIR/$TARGET_FOLDER
		fi
		cp -rdf "/nv/"$file $SAVE_CONF_DIR/$TARGET_FOLDER
	done
	cp $SAVE_XML_PATH $SAVE_CONF_DIR/$TARGET_FOLDER
	cp $SAVE_TAG_PATH $SAVE_CONF_DIR/$TARGET_FOLDER
	dmesg > /tmp/log
	mv /tmp/log  $SAVE_CONF_DIR/$TARGET_FOLDER
	cd /tmp
	tar -zcvf $SAVE_CONF_DIR/$SAVE_TARGET_ZIP ./$TARGET_FOLDER/ > /dev/null
	echo $SAVE_CONF_DIR/$SAVE_TARGET_BIN
	mv $SAVE_CONF_DIR/$SAVE_TARGET_ZIP $SAVE_CONF_DIR/$SAVE_TARGET_BIN
	rm -r $SAVE_CONF_DIR/$TARGET_FOLDER
	rm $SAVE_XML_PATH
	rm log
#3.for reload ipmi config
#cd /tmp and decompress the target file and replace the files in /nv 
#process who calls this script need to putenv of $SAVE_CONF_DIR $TARGET_FOLDER $TARGET_FILE
elif [ $1 == '2' ]; then
	cd $SAVE_CONF_DIR
	#   tar zxvf $SAVE_CONF_DIR/$TARGET_FILE > /dev/null
#	/bin/ipmi_conf_backup_tool -d -i $TARGET_FILE -o $UPLOAD_TMP_FILE
	tar zxvf $SAVE_CONF_DIR/$UPLOAD_TMP_FILE > /dev/null

	if [ $? -ne 0 ];then #old reload method
#		echo "decryption failed. try to reload the config file in raw-data mode..."
		rm -rf $UPLOAD_TMP_FILE
		tar zxvf $SAVE_CONF_DIR/$TARGET_FILE > /dev/null

	    if [ $? -ne 0 ];then #all failed situation.
		    echo "tar_fail"
			return
	    fi
	fi

#	echo "decryption complete."

	rm -rf $UPLOAD_TMP_FILE
	for file in $cp_files
	do
		if [ $file == "lighttpd.conf" ] ; then
			sh /etc/scripts/check_web_conf.sh $SAVE_CONF_DIR/$TARGET_FOLDER/$file
			if [ $? != 0 ];then 
				echo "web config has problem!"
				continue;
			fi
		fi
		if [ $file == "SDRBlock" ] || [ $file == "PSBlock" ] || [ $file == "system_logena" ]; then
			:
		else
			rm -rf /nv/$file
			cp -rdf $SAVE_CONF_DIR/$TARGET_FOLDER/$file /nv
		fi
	done
fi
