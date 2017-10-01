#include <limits>
#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

// http://en.cppreference.com/w/cpp/language/type_alias
using byte = unsigned char ;

// http://en.cppreference.com/w/cpp/types/numeric_limits
constexpr std::size_t BITS_PER_BYTE = std::numeric_limits<byte>::digits ;

// http://en.cppreference.com/w/cpp/utility/bitset
using bits_in_byte = std::bitset<BITS_PER_BYTE> ;

std::string read_bits( const char* path_to_file )
{
    std::string bitstring ;
    std::ifstream file( path_to_file, std::ios::binary ) ; // open in binary mode

    char c ;
    int pos = 0;
    bool impares = true;
    while( file.get(c) ) { // read byte by byte 
	for (unsigned short i = 0; i < 8; i++) {
	  bool isOne = bits_in_byte(byte(c))[i];
	  std::cout << isOne << std::endl; 
	  if (pos % 2 != 0 && isOne) {
	    impares = false;
   	  }
          pos++;
	}
	std::cout << "NEXT BYTE" << std::endl;
        bitstring += bits_in_byte( byte(c) ).to_string() ; // append as string of '0' '1'

    }
    if (impares) std::cout << "En las posiciones impares hay un 1" << std::endl;

    return bitstring ;
}

void write_bits( std::string bitstring, const char* path_to_file )
{
    // pad with zeroes to make it represent an integral multiple of bytes
    while( bitstring.size()% BITS_PER_BYTE ) bitstring += '0' ;

    std::ofstream file( path_to_file, std::ios::binary ) ; // open in binary mode

    for( std::size_t i = 0 ; i < bitstring.size() ; i += BITS_PER_BYTE )
    {
        // convert each sequence of '0' or '1' to a byte
        byte b = bits_in_byte( bitstring.substr( i, BITS_PER_BYTE ) ).to_ulong() ;
        file << b ; // and write it
    }
}

int main()
{
     // read this file as a string of bits
     std::string bits = read_bits("1.txt") ;
     //std::cout << bits << '\n' ;

     // flip every hundredth bit
     for( std::size_t i = 0 ; i < bits.size() ; i += 100 )
     {
         if( bits[i] == 0 ) bits[i] = '1' ;
         else bits[i] = '0' ;
     }


     bits += "01010101" ; // append another 27 bits

     write_bits( bits, "1.txt" ) ;

     //std::cout << std::ifstream("out.txt").rdbuf() ;
}
