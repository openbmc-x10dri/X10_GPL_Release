/*author : chester lin*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define SINGLE_LINE			0
#define MULTIPLE_LINE		1
#define MULTIPLE_STR_LINE	2
#define SL_WITH_SLASH		3

#define CHECK_FINISH		0
#define CHECK_NEXT_LINE		1

#define EMPTY_CHECK_FAIL	0
#define LINE_EMPTY			1
#define	LINE_NOT_EMPTY		2

#define READ_BUF_LEN        4096

#define W_FILENAME_TAIL	"_xx##_tmp"
#define INC_BEGIN '<'
#define INC_END '>'
#define STR_BEGIN '"'
#define STR_END '"'
#define SINGLE_Q_BEGIN '\''
#define SINGLE_Q_END '\''
#define SLASH_SYMBOL '\\'
#define MCOMMENT_BEGIN "/*"
#define MCOMMENT_END "*/"
#define SCOMMENT_SYMBOL "//"

#define FIND_PATTERN(PAT_BEGIN, PAT_END)    head_pos = strchr(read_buf, PAT_BEGIN); \
										    if((head_pos != NULL) && (head_pos < comment_begin)){ \
										        tail_pos = strchr(read_buf, PAT_END); \
									        if(tail_pos != NULL && (tail_pos > comment_begin)) \
									            return tail_pos; \
										    }

inline char* symbol_locator(char *read_buf, char *target_buf);
char* check_pattern(char *read_buf, char *comment_begin, char parse_mode);
inline char is_empty_line(char *tmp_buf);

bool multi_line_str;
bool sl_with_slash;

int main(int argc, char *argv[])
{
	char parse_mode = SINGLE_LINE;	

	char w_filename[256];	
	char replace_cmd[1024];
	char rm_cmd[512];
	char read_buf[READ_BUF_LEN];	

	char *write_begin;
	char *write_end;
	char *tmp_end;

	char *tmp_end_s;
	char *tmp_end_m;

	char *slash_ptr;

	bool conti_flag = true;
	bool conti_read_line = true;
	bool line_first_proc = true;
	bool line_all_comment = false;

	multi_line_str = false;	
	sl_with_slash = false;
	//int l_num = 0;

	if(argc < 2 || argc >2){
		cout << "Input argument error!" << endl;
		return -1;
	}
	
	char *r_filename = argv[1];

	ifstream file_in(r_filename);

	if(file_in.fail()){
		cerr << "open file : " << r_filename << " failed." << endl;		
		return -1;
	}

	strcpy(w_filename, r_filename);
	strcat(w_filename, W_FILENAME_TAIL);
	
	ofstream file_out(w_filename);

	if(file_out.fail()){
        cerr << "create file : " << w_filename << " failed." << endl;
        return -1;
	}

	/*Comment Parsing*/
	cout << "[Parsing] " << r_filename << "...........";

	while(conti_flag) //continue to parse contents
	{
		if(conti_read_line) //continue to read next line
		{
			file_in.getline(read_buf, READ_BUF_LEN); //read one line at a time
			line_first_proc = true;
			line_all_comment = false;
			//l_num++;

			if(file_in.eofbit & file_in.rdstate())  //EOF detection
			{
				cout << "finished" << endl;
				conti_flag = false;

				if(strlen(read_buf) == 0)
					continue;
			}
			else if(file_in.failbit & file_in.badbit & file_in.rdstate()) //error condition
			{
				cout << "failed" << endl;
	            conti_flag = false;
		        continue;	
			}

			write_begin = read_buf;
		}
		else
		{	
			line_first_proc = false;
			conti_read_line = true;
		}

		switch(parse_mode){	//parsing mode deicision

			case SINGLE_LINE: //single line mode

				tmp_end_s = symbol_locator(write_begin, SCOMMENT_SYMBOL);
				tmp_end_m = symbol_locator(write_begin, MCOMMENT_BEGIN);
	
				if(tmp_end_s == NULL && tmp_end_m == NULL) //normal statement
				{					
                    file_out << write_begin << endl;
                    break;
				}
				else if(tmp_end_m == NULL || ( (tmp_end_s != NULL) && (tmp_end_s < tmp_end_m)) ) //  '//' comment
				{
					if ((write_end = check_pattern(write_begin, tmp_end_s, parse_mode))!=NULL){ //found string or other patterns
						file_out.write(write_begin, (write_end - write_begin)+1 );
						write_begin = write_end + 1;

						if(is_empty_line(write_begin) == LINE_NOT_EMPTY)
							conti_read_line = false;						
                        else
                            file_out << endl;
		

						if(multi_line_str)
							parse_mode = MULTIPLE_STR_LINE;
					}
					else
					{
						write_end = tmp_end_s;
						if(write_end != write_begin){
							write_end[0] = '\0';	

							if(line_first_proc==false || is_empty_line(write_begin) == LINE_NOT_EMPTY)		
	                            file_out << write_begin << endl;
						}

						if(sl_with_slash)
							parse_mode = SL_WITH_SLASH;
					}
					break;
				}
				else if(tmp_end_s == NULL || ( (tmp_end_m != NULL) && (tmp_end_s > tmp_end_m))) // '/*' comment
				{					
                    if ((write_end = check_pattern(write_begin, tmp_end_m, parse_mode))!=NULL){ //found string or other patterns
                        file_out.write(write_begin, (write_end - write_begin)+1 );

                        write_begin = write_end + 1;

                        if(is_empty_line(write_begin) == LINE_NOT_EMPTY)
                            conti_read_line = false;
						else
							file_out << endl;

                        if(multi_line_str)
                            parse_mode = MULTIPLE_STR_LINE;

						break;
                    }
					else
					{
						write_end = tmp_end_m;
		                if(write_end != write_begin){
			                write_end[0] = '\0';											

							if(line_first_proc && is_empty_line(write_begin) == LINE_EMPTY)
								line_all_comment = true;
							else
								file_out << write_begin;	

					    }else
							if(line_first_proc)
								line_all_comment = true;

						write_begin = write_end + strlen(MCOMMENT_BEGIN);
					}

                    parse_mode = MULTIPLE_LINE;

				}else{
					;
				}
				//'break' keyword is not needed here !!	

			case MULTIPLE_LINE: //multiple comment line mode

				if(( write_end = symbol_locator(write_begin, MCOMMENT_END) )){
					write_begin = write_end + strlen(MCOMMENT_END);

					if(is_empty_line(write_begin) == LINE_NOT_EMPTY)
						conti_read_line = false;
					else
						if(!line_all_comment)
							file_out << endl;  					
					
					parse_mode = SINGLE_LINE;
				}

				break;

			case MULTIPLE_STR_LINE: //multiple string line mode
				write_end = strrchr(write_begin, SLASH_SYMBOL);	

				if(write_end!=NULL){
					if( is_empty_line(write_end+1) == LINE_EMPTY)
					{
						file_out << write_begin << endl;
						break;
					}

					//last string line touched
					write_end = write_end + 1;
				}
				else //last string line touched
				{
					write_end = write_begin;
				}

                while(write_end != NULL)
				{
                     write_end = strchr(write_end, STR_END);

					if(write_end!=NULL && *(write_end-1) != '\\'){
                        file_out.write(write_begin, (write_end-write_begin)+1);
						write_begin = write_end + 1;

						if(is_empty_line(write_begin) == LINE_NOT_EMPTY)
							conti_read_line = false;
						else
							file_out << endl;
						
						break;
                    }
					else
					{
						if(write_end!=NULL)
							write_end++;	
					}
				
                }

				multi_line_str = false;
				parse_mode = SINGLE_LINE;
				break;

			case SL_WITH_SLASH:
				slash_ptr = strrchr(write_begin, SLASH_SYMBOL);

				if(slash_ptr == NULL){
					sl_with_slash = false;
					parse_mode = SINGLE_LINE;
				}

				break;

			default:
				; //do nothing

		} //end of switch
	
	} //end of while

	/*close files*/
	file_in.close();
	file_out.close();

	sprintf(replace_cmd, "cat %s | tr -d '\\r' > %s", w_filename, r_filename);
	sprintf(rm_cmd, "rm -f %s", w_filename);
	system(replace_cmd);
	system(rm_cmd);

	return 0;
}

inline char* symbol_locator(char *read_buf, char *target_buf)
{
    return strstr(read_buf, target_buf);
}

char* check_pattern(char *read_buf, char *comment_begin, char parse_mode) //string or other patterns checking procedure.
{
	char *head_pos = NULL;
	char *tail_pos = NULL;	
	char *buf_ptr = NULL;
	char *slash_ptr = NULL;

	if(comment_begin == NULL || read_buf == NULL)
		return NULL;

	buf_ptr = read_buf;

	head_pos = strchr(buf_ptr, STR_BEGIN); // "....." pattern
	if((head_pos != NULL) && (head_pos < comment_begin)){

		tail_pos = comment_begin;
		while(tail_pos != NULL)
		{
			buf_ptr = tail_pos+1;
			tail_pos = strchr(buf_ptr, STR_END);

			if(tail_pos != NULL)
			{
				if(*(tail_pos-1) != '\\')
					return tail_pos;
			}else //tail_pos = NULL
			{
				slash_ptr = strrchr(comment_begin, SLASH_SYMBOL);

				if(slash_ptr != NULL && (is_empty_line(slash_ptr+1) == LINE_EMPTY)){ //check if the slash symbol is the last one
					multi_line_str = true;
					return (slash_ptr);	
				}else{
					multi_line_str = false;
				}
			}
		} //end of while
	}

	FIND_PATTERN(INC_BEGIN, INC_END); // <....> pattern
	FIND_PATTERN(SINGLE_Q_BEGIN, SINGLE_Q_END); // '.....' pattern

	if(parse_mode == SINGLE_LINE){
	    slash_ptr = strrchr(comment_begin, SLASH_SYMBOL);
		if(slash_ptr != NULL && (is_empty_line(slash_ptr+1) == LINE_EMPTY)){ //check if the slash symbol is the last one
			sl_with_slash = true;
		}
	}

	return NULL;
}

inline char is_empty_line(char *tmp_buf)
{
	char *buf_ptr = tmp_buf;

	if(buf_ptr == NULL)
		return EMPTY_CHECK_FAIL;

	while(*buf_ptr != '\n' && *buf_ptr != '\r' && *buf_ptr != '\0'){ //not touch end
		if(*buf_ptr == ' ' || *buf_ptr == '\t') //blank or tab
			buf_ptr++;		
		else //alphabet or number
			return LINE_NOT_EMPTY;
	}	

	return LINE_EMPTY;
}
