#include <string>
#include "CodesTree.hpp"

class Decoder {

public:

	void decompress(std::string fileName, CodesTree& tree) {

		std::ifstream file(fileName);
		std::ofstream fs;
		std::string newFileName = "decoded.bin";
		fs.open(newFileName, std::fstream::out | std::fstream::trunc);

		int written_bits = 0;//биты, которые уже были записаны
		char byte_to_write = 0;

		int return_shift = 0;
		int tmp_leng = 16; // 8

		//char c;
		//char tmp_c;

		unsigned short c;
		unsigned short tmp_c;

		unsigned char lo;
		unsigned char hi;

		int read_ans;

		int bytes_restored = 0;
		int init_file_size = 0; 
		file.read((char*)&init_file_size, sizeof(init_file_size));

		int key_map_size = 0;
		file.read((char*)&key_map_size, sizeof(key_map_size));
		std::map<char, int> key_table;
		for (int ii = 0; ii < key_map_size; ++ii)
		{
			char key;
			int freq;
			file.get(key);
			file.read((char*)&freq, sizeof(freq));

			key_table.insert(std::pair<char, int>(key, freq));
		}
		CodesTree trCd(key_table);

		//file.get(c);
		//file.get(tmp_c);

		file.read(reinterpret_cast<char*>(&hi), 1);
		file.read(reinterpret_cast<char*>(&lo), 1);
		c = (hi << 8) | lo;

		file.read(reinterpret_cast<char*>(&hi), 1);
		file.read(reinterpret_cast<char*>(&lo), 1);
		tmp_c = (hi << 8) | lo;

		//file.read(reinterpret_cast<char*>(&c), sizeof(c));
		//file.read((char*)&tmp_c, sizeof(tmp_c));

		//while (file.get(c)) 
		while(bytes_restored < init_file_size)
		{ //читаем из файла по байту
			//std::vector<char> code = tree.getSymbolsCode(c);//получаем код для символа в виде строки

			return_shift = 0;
			char code = trCd.findFirstSymbolInCode(c, return_shift);
			if (code != NULL)
			{
				fs << code;
				bytes_restored++;
				if (bytes_restored == init_file_size)
				{
					break;
				}

				if (return_shift <= tmp_leng)
				{
					c <<= return_shift;
					//unsigned char watch = ((unsigned char)(tmp_c)) >> (8 - return_shift);
					c |= (((unsigned short)(tmp_c)) >> (16 - return_shift)); // 8
					tmp_c <<= return_shift;
					tmp_leng -= return_shift;

					if (tmp_leng == 0)
					{
						if (file.read((char*)&tmp_c, sizeof(tmp_c)))
						{
							unsigned char tmp = tmp_c >> 8;
							tmp_c = (tmp_c << 8) | tmp;
							tmp_leng = 16;
						}
						else
						{
							break;
						}
					}
				}
				else if(return_shift > tmp_leng)
				{
					c <<= tmp_leng;
					c |= (((unsigned short)(tmp_c)) >> (16 - tmp_leng));

					if (file.read((char*)&tmp_c, sizeof(tmp_c)))
					{
						unsigned char tmp = tmp_c >> 8;
						tmp_c = (tmp_c << 8) | tmp;

						c <<= (return_shift - tmp_leng);
						c |= (((unsigned short)(tmp_c)) >> (16 - (return_shift - tmp_leng)));
						tmp_c <<= (return_shift - tmp_leng);
						tmp_leng = 16 - (return_shift - tmp_leng);
					}
					else
					{
						tmp_c = 0xFFFF;
						c <<= (return_shift - tmp_leng);
						c |= (((unsigned short)(tmp_c)) >> (16 - (return_shift - tmp_leng)));
						tmp_leng = 16 - (return_shift - tmp_leng);
						//break;
					}
				}
			}
			else
			{
				break;
			}

			if (tmp_leng == 0)
			{
				break;
			}


			/*
			for (char c2 : code) {
				c2 <<= 7 - written_bits;
				byte_to_write |= c2;
				++written_bits;
				if (written_bits == 8) {
					fs << byte_to_write;
					byte_to_write = 0;
					written_bits = 0;
				}
			}
			*/
		}

		fs.close();
	}

};