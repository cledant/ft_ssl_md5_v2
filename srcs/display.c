#include "ft_ssl.h"

void
display_binary_help()
{
    puts("Usage: ft_ssl command [command options] [command args]\n\tAvailable "
         "commands:\n\t\tmd5\n\t\tsha256");
}

void
display_command_help()
{
    puts("Available commands:\n\nMessage digest commands:\nmd5\nsha256");
}

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