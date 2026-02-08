#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <string>
#include <stdexcept>

class AudioDecoder
{
	public:
		explicit AudioDecoder(const std::string& file)
		{
			ma_decoder_config conf = ma_decoder_config_init(ma_format_f32, 0,0);
			ma_result result = ma_decoder_init_file(file.c_str(),&conf, &decoder);
			if(result != MA_SUCCESS)
			{
				throw std::runtime_error("Failed to open audio file: " + file);
			}
		}
		~AudioDecoder()
		{
			ma_decoder_uninit(&decoder);
		}
		AudioDecoder(const AudioDecoder&) = delete;
		AudioDecoder& operator=(const AudioDecoder&) = delete;
		AudioDecoder(AudioDecoder&& other) noexcept : decoder(other.decoder)
		{
			other.decoder = {};
		}

		uint64_t readFrames(float* buffer, uint64_t framesToRead)
		{
			ma_uint64 framesRead;
			ma_decoder_read_pcm_frames(&decoder,buffer,framesToRead,&framesRead);
			return framesRead;
		}

		uint32_t getChannels() const 
		{
			return decoder.outputChannels;
		}
		uint32_t getSampleRate() const
		{
			return decoder.outputSampleRate;
		}
	
	private:
		ma_decoder decoder;
};
