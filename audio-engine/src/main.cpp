#include "../include/audiodecoder.hh"
#include <iostream>
#include <vector>


std::vector<float> stereo_to_mono(std::vector<float>& stereo_buf)
{
	std::vector<float> mono_buf;
	mono_buf.reserve(stereo_buf.size()/2);
	float avg;
	for(size_t i = 0; i<stereo_buf.size(); i+=2)
	{
		avg = (stereo_buf[i] + stereo_buf[i+1]) / 2;
		mono_buf.push_back(avg);
	}
	return mono_buf;
}


int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout << "Usage: ./executable audiofile.[mp3][WAV][FLAC]" << std::endl;
		return 1;
	}

	std::cout << "opening " << argv[1] << std::endl;
	AudioDecoder audioFile(argv[1]);

	std::cout << "opened file" << std::endl;

	uint64_t channels = audioFile.getChannels();
	uint64_t sampleRate = audioFile.getSampleRate();

	std::cout << "channels: " << channels << std:: endl << "sample rate: " << sampleRate << std::endl;


	std::vector<float> buf(1024 * audioFile.getChannels());
	audioFile.readFrames(buf.data(),1024);

	for(int i = 0; i<20; i++)
	{
		std::cout << buf[i] << std::endl;
	}

	std::vector<float> mono = stereo_to_mono(buf);

	std::cout << "Stereo ^^ Mono \\/\\/" << std::endl;

	for(int i = 0; i<20; i++)
	{
		std::cout << buf[i] <<std::endl;
	}

	


	return 0;

}
