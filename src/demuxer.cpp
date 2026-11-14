#include <luviolVE/demuxer.hpp>

namespace lvlve
{

Demuxer::Demuxer(const std::string path)
{
    if (avformat_open_input(&formatContext, path.c_str() , nullptr, nullptr) < 0)
    {
       // TODO: Implement logging system
       return;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0)
    {
        // TODO: Implement logging system
        return;
    }
}

Demuxer::~Demuxer()
{
    avformat_close_input(&formatContext);
}

AVStream* Demuxer::getVideoStream() const
{
    if (!formatContext)
    {
        // TODO: Implement logging system
        return nullptr;
    }

    int videoStreamIdx = av_find_best_stream(formatContext,
        AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);

    if (videoStreamIdx < 0)
    {
        // TODO: Implement logging system
        return nullptr;
    }

    return formatContext->streams[videoStreamIdx];
}

}