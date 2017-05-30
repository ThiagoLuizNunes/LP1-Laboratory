#ifndef PROCESS_PROCESS_H
#define PROCESS_PROCESS_H

#include <string>
#include <iostream>

#include "ProcessError.h"
#include "OpenCodec.h"

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavformat/avio.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/audio_fifo.h>
    #include <libavutil/avutil.h>
    #include <libavutil/imgutils.h>
}

#define AV_OUTPUT_FORMAT "mp4"
#define AUDIO_OUTPUT_CODEC "ac3"

class Process {
private:
  AVFormatContext *inputformatContext = nullptr;
  AVCodecContext *inputCodecCtx;
  AVCodec *inputEncoder;
  AVStream *inStream;
  int streamIndex = -1;

  AVFormatContext *outputFormatContext;
  AVCodecContext *outputCodecCtx;
  AVCodec *outputEncoder;
  AVStream *outStream;

public:
    Process();
    ~Process();

    void openFile(const std::string& type, const std::string& input) throw(ProcessError);

    Process(const Process&)            = delete; // We don't need the copy constructor as this is a singleton.
    Process& operator=(const Process&) = delete; // Copy assignment is not needed also.
};

#endif //defined as PROCESS_PROCESS_H
