#pragma once

#include <string>

extern "C"
{
#include <libavformat/avformat.h>
}

namespace lvlve
{

class Demuxer
{
public:
    Demuxer(const std::string path);
    ~Demuxer();

    AVStream* getVideoStream() const;
    AVPacket* getNextPacket() const;
    AVRational getVideoTimeBase() const { return getVideoStream()->time_base; }
private:
    AVFormatContext* formatContext = nullptr;
};

}