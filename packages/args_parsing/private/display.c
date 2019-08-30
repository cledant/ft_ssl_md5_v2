#include "args_parsing.h"
#include "args_parsing_impl.h"

void
display_md5_help()
{
    puts("Usage: md5\n\n-p : echo STDIN to STDOUT and append the checksum to "
         "STDOUT\n-q : quiet mode\n-r : reverse the format of the output\n-s : "
         "print the checksum of given string");
}

void
display_sha256_help()
{
    puts(
      "Usage: sha256\n\n-p : echo STDIN to STDOUT and append the checksum to "
      "STDOUT\n-q : quiet mode\n-r : reverse the format of the output\n-s : "
      "print the checksum of given string");
}