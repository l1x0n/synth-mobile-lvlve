#include <luviolVE/player.hpp>
#include <utility>

namespace lvlve
{

Player::Player()
    : clock()
{}

void Player::open(const std::string& path)
{   
    auto newDemuxer = std::make_unique<Demuxer>(path);
    auto newDecoder = std::make_unique<VideoDecoder>(newDemuxer->getVideoStream());
    auto newRenderer = std::make_unique<VideoRenderer>(newDecoder->getVideoWidth(),
                                                       newDecoder->getVideoHeight());
    
    demuxer = std::move(newDemuxer);
    decoder = std::move(newDecoder);
    renderer = std::move(newRenderer);

    currentFrame = nullptr;
    clock.pause();
    clock.seek(0);
    ended = false;

    renderer->render(decoder->getNextFrame()); 
}

void Player::update()
{
    if (!demuxer || !decoder || !renderer)
        return;
    if (!currentFrame)
        currentFrame = decoder->getNextFrame();
    if (!currentFrame)
    {   
        ended = true;
        clock.pause();
        return;
    }

    int64_t pts = currentFrame->best_effort_timestamp;
    if (pts * av_q2d(demuxer->getVideoTimeBase()) <= clock.time())
    {
        renderer->render(currentFrame);
        currentFrame = nullptr;
    }
}

void Player::play()
{
    if (!decoder)
        return;
    if (ended)
    {
        seek(0);
    }
    clock.play();
}

void Player::pause()
{
    clock.pause();
}

void Player::togglePlay()
{
    if (clock.isPlaying())
        pause();
    else
        play();
}

void Player::seek(double t)
{   
    if (!decoder)
        return;
    currentFrame = nullptr; 
    clock.seek(t);
    decoder->seek(t);
    ended = false;
}

}
