#include "types.h"
#include "stat.h"
#include "user.h"

/** 
 * @brief Converts a string to integer using atoi.
 * @param s Character pointer. Represents a string. 
 * @return Integer if the string is a correct representation 
 * integer, otherwise -1.
*/
int getLineNumber(char *s)
{
  // If atoi(s) returns 0 but the string is not zero
  if ((atoi(s) == 0) && *s != '0')
    return -1;
  return atoi(s);
}

/** 
 * @brief Print lines from start (including) to end (excluding)
 * of a file
 * @param start non-negative integer denoting the starting line
 * @param end non-negative integer denoting the ending line
 * @param fileName Character pointer, representing the file name.
*/
void printLines(int start, int end, char *fileName)
{
  int f; // Holds the file pointer
  if ((f = open(fileName, 0)) < 0)
  {
    // Cannot open file
    // End of file if f == 0
    // Error if f == -1
    printf(1, "printLines: cannot open the specified file, %s\n", fileName);
    exit();
  }

  char buffer[512];   // Read 512 bytes at a time from file
  char line[512];     // Holds a line of file
  int n;              // Number of bytes read
  int lineCount = -1; // Number of lines read (end of a line is '\n')
  int charCount = 0;  // Holdss number of characters in a line

  while ((n = read(f, buffer, sizeof(buffer))) > 0)
  {
    for (int i = 0; i < n; i++)
    {
      // End of a line
      if (buffer[i] == '\n')
      {
        ++lineCount; // Increment the line counter

        // Check whether lineCount is in the range of start to end
        if ((start <= lineCount) && (lineCount <= end))
          printf(1, "%s\n", line); // Print the line
        memset(line, 0, 512);      // Set the line array to 0
        charCount = 0;             // Reset character counter
      }
      else
        line[charCount++] = buffer[i]; // Add a character from buffer to line and increment the character counter

      // Reached end
      if (lineCount + 1 == end)
      {
        // Close the file and return
        close(f);
        return;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  // Count of arguments must be either 2 or 4
  if ((argc != 2) && (argc != 4))
  {
    printf(1, "Invalid Command\nTry 'printLines --help' for more information\n");
    exit();
  }

  // Count of arguments is 2 implies the command used is
  // printLines --help
  if (argc == 2)
  {
    if (!strcmp("--help", argv[1])) // Display help
      printf(1, "Usage: printLines [Starting Line Number] [Ending Line Number] [File name]\nPrints a range of lines from file.\nPossible arguments are:\n    s e fileName    prints the lines starting from s (including) and ending at e (excluding) of file fileName;\n");
    else // Display error
      printf(1, "Invalid Command\nTry 'printLines --help' for more information\n");
    exit();
  }

  // Count of arguments is 4 implies the command used is
  // printLines x y filename
  // x and y are line numbers

  int start = getLineNumber(argv[1]); // Get the start line number
  int end = getLineNumber(argv[2]);   // Get the end line number

  if ((start < 0) || (end < 0)) // Display err if any of them is negative
  {
    printf(1, "Invalid line numbers\nTry 'printLines --help' for more information\n");
    exit();
  }
  printLines(start, end, argv[3]); // Print lines from start to end
  exit();
}
