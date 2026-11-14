#pragma once

#include <string>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
}

namespace lvlve
{

class VideoDecoder
{
public:
    VideoDecoder(const AVStream* videoStream);
    ~VideoDecoder();
    VideoDecoder(const VideoDecoder&) = delete;
    VideoDecoder& operator=(const VideoDecoder&) = delete;
    
    AVFrame* getNextFrame(AVPacket* packet);
    void seek(double t);
    int getVideoWidth() const { return codecContext->width; }
    int getVideoHeight() const { return codecContext->height; }
    
private:
    AVCodecContext* codecContext = nullptr;
    AVFrame* frame = nullptr;
    int64_t target_ts = AV_NOPTS_VALUE;
};

}