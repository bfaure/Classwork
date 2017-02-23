#include "stdio.h" // for printf
#include "string.h" // for strlen, etc.
#include "stdlib.h" 
#include "ctype.h" // for tolower

/*
% echo "aaab" > bar
% ./p05 bar aa B
2
1
%

% echo "abcdefgh" > bar
% ./p05 bar bc
1
%
*/


// Get the number of times "target" is in "filename" file.
int get_match_count(const char* filename,const char *target)
{
	/*
	--> filename: input file (string)
	--> target: target file (string)
	*/

	int match_count = 0;

	// open the "filename" file if possible
	FILE *file_handle;
	file_handle = fopen(filename,"r"); 
	
	// check to ensure we have successfully opened the file
	if(file_handle == NULL) 
	{
		perror("fp");
		exit(1);
	}

	// create buffer of two characters (regular character, null character)
	// to allow for reading in single characters at a time from file
	const int buffer_length = 2;
	char single_char_buffer[buffer_length];

	// create buffer of the same length as the input target to allow us to
	// compare the characters in the file to the target chars
	char *target_sized_buffer;
	const int target_length = strlen(target);
	target_sized_buffer = malloc(sizeof(char) * target_length);

	// iterate over each character in the file
	int i=0;
    while (fgets(single_char_buffer, buffer_length, file_handle)) 
    {
    	// calculate the length of the single_char_buffer to ensure we picked up a character and did not hit an endline
        size_t len = strlen(single_char_buffer);
        if (len && (single_char_buffer[len - 1] != '\n')) 
        {
        	// check if the current character is a letter, if so, convert it to lowercase
        	single_char_buffer = to_lowercase(single_char_buffer);

        	// append the current character to the target_sized_buffer
            target_sized_buffer[i] = single_char_buffer[0];
            // append a null character to designate the end of the string
            target_sized_buffer[i+1] = '\0';

            // check if we have picked up enough characters to allow us to compare against the target string
            if (strlen(target_sized_buffer)==strlen(target))
            {
            	// check if the target_sized_buffer (which we now know is the correct length) equals the target
            	if (strcmp(target_sized_buffer,target)==0)
            	{
            		match_count++;
            	}

            	// because we have the correct number of characters, we need to shift back the characters
            	// to allow us to insert the next character on the next iteration

            	char *temp = malloc(sizeof(char) * target_length); // create temporary char array

            	// fill in temp array with shifted characters of target_sized_buffer (shift left by 1)
            	for (int k=0; k<(target_length-1); k++)
            	{
            		temp[k] = target_sized_buffer[k+1];
            	}

            	// copy temp array into target_sized_buffer
            	strcpy(target_sized_buffer,temp);
            }

            // if we don't have enough characters in target_sized_buffer to compare against
            // the target yet then increment i so that the next character in the file gets appended
            else
            {
            	i++;
            }
        }

    }
	return match_count;
}


int main(int argc, char *argv[])
{
	// need at least 2 arguments (other than ./p05)
	if (argc>=3)
	{
		// copy the input filename
		char input_filename[strlen(argv[1])];
		strcpy(input_filename,argv[1]); 

		// iterate over the rest of the inputs and check how many times they appear in the file 
		for (int i=2; i<(argc); i++)
		{
			// copy the current target input
			char current_target[strlen(argv[i])];
			strcpy(current_target,argv[i]);

			// get the match count and print it out
			printf("%d\n",get_match_count(input_filename,current_target));
		}
	}
}