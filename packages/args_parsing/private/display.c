#include "args_parsing_impl.h"

void
display_md5_help()
{
    puts("Usage: md5 [options] [file...]\nfile... files to digest (default is "
         "stdin)\n-p : echo STDIN to STDOUT and append the checksum to "
         "STDOUT\n-q : quiet mode\n-r : reverse the format of the output\n-s : "
         "print the checksum of given string\n-h : display help");
}

void
display_sha256_help()
{
    puts(
      "Usage: sha256 [options] [file...]\nfile... files to digest (default is "
      "stdin)\n-p : echo STDIN to STDOUT and append the checksum to "
      "STDOUT\n-q : quiet mode\n-r : reverse the format of the output\n-s : "
      "print the checksum of given string\n-h : display help");
}