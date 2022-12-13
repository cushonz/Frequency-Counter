#include <iostream>
#include <fstream>

#include <string>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Function prototype
void freq(char *buff, long size, char countIn);

int main() {

    // Instantiate variables
	char *buff;
	long size;
    FILE *pfile;
	
    // Try to open file, if file doesn't exist error.

	pfile = fopen("test.txt", "rb");
	if (!pfile) {
		perror("test.txt");
		exit(1);
	}

	// Move cursor to end of file
	fseek(pfile, 0L, SEEK_END);

    // Take current value of position indicator, this can be used for the size
	size = ftell(pfile);

    // Set back to zero
	rewind(pfile);

    // Allocate buffer memory
	buff = (char*) malloc(size);

    //catch potential errors when allocating memory for buffer
	if (!buff) 
    {
		fclose(pfile); // Close file
		cout << "Memory Allocation failed" << endl;
		exit(1);
	}


	fread(buff, size, 1, pfile);
	fclose(pfile);
	
    //Loop through the alphabet and create child processes to calculate the percentages of letter occurences
	for (int i = 0; i < 26; i++) 
    {
		int child_pid = fork(); // Create child
		if (child_pid < 0) 
        {
			perror("fork\n"); // Error
		} 
        else if (child_pid == 0) // If the child process is made then calc freq
        { 
			freq(buff, size, (char) i+97); // +97 for ASCII values
			break;
		}
	}
	return 0;
}

// Calculate the frequency of the char and print

void freq(char *buff, long size, char countIn)
{
    // Variables to keep track of
    int count = 0;
    int total = 0;

    for (int i = 0; i < size; i++)
    {
        // Convert to lowercase so all chars of the same letter are evaluated equally
        if(tolower(buff[i]) == countIn){
            count++;
        }
        
        // All alphabetical values will be added, this is used to skip all punctuation
        if (isalpha(buff[i])){ 
            total++;
        }
    }
    cout << countIn << ": " << ((float)count/(float)total*100) << "%" <<endl;
}