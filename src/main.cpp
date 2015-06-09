#include <iostream>
#include <string>
#include <vector>


std::string timeIntToString(int startH, int startM, int startS, int startD)
{
	std::string start = "";
	if (startH < 10)
	{
		start += "0" + (std::to_string(startH));
	}
	else
	{
		start += (std::to_string(startH));
	}
	start += ":";
	if (startM < 10)
	{
		start += "0" + (std::to_string(startM));
	}
	else
	{
		start += (std::to_string(startM));
	}
	start += ":";
	if (startS < 10)
	{
		start += "0" + (std::to_string(startS));
	}
	else
	{
		start += (std::to_string(startS));
	}
	start += ".";
	if (startD < 10)
	{
		start += "00" + (std::to_string(startD));
	}
	else if (startD < 100)
	{
		start += "0" + (std::to_string(startD));
	}
	else
	{
		start += (std::to_string(startD));
	}
	return start;
}


void finish()
{

	std::cout << std::endl;
	std::cout << "for job in `jobs -p`" << std::endl;
	std::cout << "do" << std::endl;
	std::cout << "    wait $job" << std::endl;
	std::cout << "done" << std::endl;

	std::cout << std::endl << "echo \"YEY !\" " << std::endl;

}


int main(int argc, char* argv[])
{

	std::vector<std::vector<std::string>* > srts;
	std::vector<std::string> fileNames;


	try
	{
		bool first = true;
		while(std::cin)
		{
			std::string data;		
			getline(std::cin, data);
			if (first && data != "=== END ===")
			{
				fileNames.push_back(data);
				std::cout << "#new file name : " << data << std::endl;
				srts.push_back(new std::vector<std::string>());
				first = false;
			} 
			else
			{
				if (data == "=== NEXT ===")
				{
					std::cout << "#=== NEXT === " << std::endl;
					first = true;
				}
				else if (data == "=== END ===")
				{
					std::cout << "#=== END === " << std::endl;
					throw 0;
				}
				else
				{
					std::cout << "# add  " << data << " at " << (srts.size() - 1)<< std::endl;
					srts[srts.size() - 1]->push_back(data);
				}
			}

		};
	}
	catch (...)
	{
	}

	std::vector<unsigned int> validId;
	std::vector<unsigned int> validIdFile;

	try
	{
		bool first = true;
		unsigned int id = -1;
		while(std::cin)
		{
			std::string data;		
			getline(std::cin, data);
			if (first)
			{
				std::cout << "#looking for file : " << data << std::endl;
				id = -1;
				for (unsigned int i = 0; i < fileNames.size(); ++i)
				{
					if (fileNames[i] == data)
					{
						std::cout << "#found at : " << i << std::endl;
						id = i;
						break;
					}
				}
				if (id == -1)
				{
					std::cout << "#not found !" << std::endl;
				}
				first = false;
			} 
			else
			{
				if (id != -1)
				{
					std::cout << "#looking for srt id : " << data << std::endl;
					bool isId = true;
					for (unsigned int i = 0; i < srts[id]->size(); ++i)
					{
						if (isId)
						{
							isId = false;
							if (std::stoi(srts[id]->at(i)) == std::stoi(data)) // just == ?
							{
								std::cout << "#found at : " << i << std::endl;
								validId.push_back(i);
								validIdFile.push_back(id);
							}
						}
						else if (srts[id]->at(i).size() < 1)
						{
							isId = true;
						}
					}
				}
				first = true;
			}

		};
	}
	catch (...)
	{
	}


	std::cout << "#!/bin/bash" << std::endl << std::endl;

	try
	{
		int nbLine = 0;
		int id;
		int startH;
		int startM;
		int startS;
		int startD;
		std::string start;

		int endH;
		int endM;
		int endS;
		int endD;

		int diffH;
		int diffM;
		int diffS;
		int diffD;
		std::string diff;

		std::string text;
		std::string fileName;

		for (unsigned int i = 0; i < validId.size(); ++i)
		{
			nbLine = 0;
			std::cout << "#cut n°" << i << " : " << std::endl;
			fileName = fileNames[validIdFile[i]];	
			std::cout << "#fileName :" << fileName << std::endl;
			std::string data = srts[validIdFile[i]]->at(validId[i]);
			unsigned int offset = 0;	
			while (data.size() > 0)
			{
				std::cout << "#data :" << data << std::endl;
				if (nbLine%4 == 0)
				{
					id =  std::stoi(data);
				}
				else if (nbLine%4 == 1)
				{
					startH = (data[0] - '0')*10 + (data[1] - '0');
					startM = (data[3] - '0')*10 + (data[4] - '0');
					startS = (data[6] - '0')*10 + (data[7] - '0');
					startD = (data[9] - '0')*100 + (data[10] - '0')*10 + (data[11] - '0');

					endH = (data[17] - '0')*10 + (data[18] - '0');
					endM = (data[20] - '0')*10 + (data[21] - '0');
					endS = (data[23] - '0')*10 + (data[24] - '0');
					endD = (data[26] - '0')*100 + (data[27] - '0')*10 + (data[28] - '0');

					diffH = endH - startH;
					diffM = endM - startM;
					diffS = endS - startS;
					diffD = endD - startD;

					if (diffD < 0)
					{
						diffD = 1000 + diffD;
						diffS--;
					}
					if (diffS < 0)
					{
						diffS = 60 + diffS;
						diffM--;
					}
					if (diffM < 0)
					{
						diffM = 60 + diffM;
						diffH--;
					}
					if (diffH < 0)
					{
						diffH = 24 + diffH;
					}

					start = timeIntToString(startH, startM, startS, startD);
					diff = timeIntToString(diffH, diffM, diffS, diffD);

				}
				else if (nbLine%4 == 2)
				{
					text = data;
					std::cout << std::endl;
					std::cout << "#" << data << std::endl;
					if (argc > 1)
					{

						std::cout << "ffmpeg -i " << fileName << "/" << fileName << ".mp4 -ss " << start << " -t " << diff << " -c:v copy -c:a copy -loglevel error out/" << fileName << "." << id << ".mp4 &" << std::endl;
					}
					else
					{
						std::cout << "echo \"" << (i+1) << "/" << validId.size() << " ... \"" << std::endl;
						std::cout << "ffmpeg -i " << fileName << "/" << fileName << ".mp4 -ss " << start << " -t " << diff << " -c:v libx264 -c:a libmp3lame -loglevel error out/" << fileName << "." << id << ".mp4" << std::endl;
					}
				}

				nbLine++;

				offset++;
				//				if (offset + i >= validId
				data = srts[validIdFile[i]]->at(validId[i]+offset);
			}
		}
	}
	catch (...)
	{
	}
	finish();

	std::cout << std::endl;
	std::cout << "#creation of the list" << std::endl;
	std::cout << "rm listTmp.caca 2> /dev/null" << std::endl;
	std::cout << "touch listTmp.caca" << std::endl;
	std::cout << std::endl;

	for (unsigned int i = 0; i < validId.size(); ++i)
	{
		std::cout << "echo \"file 'out/" << fileNames[validIdFile[i]] << "." <<  srts[validIdFile[i]]->at(validId[i]) << ".mp4'\" >> listTmp.caca" << std::endl; 
	}
	std::cout << std::endl;

	std::cout << "echo \"finalization...\"" << std::endl;
	std::cout << std::endl;
	std::cout << "rm final.mp4 2> /dev/null" << std::endl;
	if (argc > 1)
	{
		std::cout << "ffmpeg -f concat -i listTmp.caca -c:v libx264 -c:a copy -loglevel error final.mp4" << std::endl;
	}
	else
	{
		std::cout << "ffmpeg -f concat -i listTmp.caca -c:v copy -c:a copy -loglevel error final.mp4" << std::endl;
	}
	std::cout << "rm listTmp.caca" << std::endl;
	std::cout << "echo \"Done !\"" << std::endl;

	return 0;
}
