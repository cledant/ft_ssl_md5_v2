# ft_ssl_md5

This 42 project aims to implement md5 and sha256 cryptographic hash functions.

## Compiling

You may compile `ft_ssl` by running `cmake`.  

## Usage  

Usage: ft_ssl command \[command options\] \[command args\]  
* Available commands:
    * md5  
	* sha256  

## Md5 options

Usage: `md5` \[options\] \[file...\]  
file... files to digest (default is stdin)  
-p : echo STDIN to STDOUT and append the checksum to STDOUT  
-q : quiet mode  
-r : reverse the format of the output  
-s : print the checksum of given string  
-h : display help  

## Sha256 options

Usage: `sha256` \[options\] \[file...\]  
file... files to digest (default is stdin)  
-p : echo STDIN to STDOUT and append the checksum to STDOUT  
-q : quiet mode  
-r : reverse the format of the output  
-s : print the checksum of given string  
-h : display help  