#include "Process.h"
//https://ffmpeg.org/ffmpeg.html
//https://ffmpeg.org/doxygen/3.1/demuxing_decoding_8c-example.html#a30

Process::Process() : formatContext(nullptr) {
    av_register_all(); //Register muxers/demuxers
    av_log_set_level(AV_LOG_INFO); //Set log level (What FFMPEG prints on screen)
}

Process::~Process() {
}

void Process::openFile(const std::string& input) throw(ProcessError) {
    /* open input file, and allocate format context */

    std::cout << "Opening: " << input << std::endl;
    if (avformat_open_input(&formatContext, input.c_str(), nullptr, nullptr) < 0) {
        throw ProcessError("Could not open source file");
    }

    // retrieve stream information
    if(avformat_find_stream_info(formatContext, nullptr) < 0){
        throw ProcessError("Could not find stream information");
    }

    if(open_codec_context(&video_stream_idx, &videodecodeCtx, formatContext, AVMEDIA_TYPE_VIDEO, &refcount) >= 0) {
        /*Receiving the ID of the best stream video of the input coming from method  ---- video_stream_idx its changed */
        video_stream = formatContext->streams[video_stream_idx];

        //Creating video file to write to it
        video_dst_file = std::fopen(input.c_str(), "wb");
        if (!video_dst_file) {
            ret = 1;
            throw ProcessError("Could not open destination file " + input);
        }

        /* allocate image where the decoded image will be put */
        width = videodecodeCtx->width;
        height = videodecodeCtx->height;
        pix_fmt = videodecodeCtx->pix_fmt;

        frameBuffer->width = width;
        frameBuffer->height = height;
        frameBuffer->format = pix_fmt;

        ret = av_frame_get_pkt_size(frameBuffer);

        av_frame_free(&frameBuffer);
        std::cout << "SIZE BUFFER " + std::to_string(ret) << '\n';
        // ret = av_image_alloc(video_dst_data, video_dst_linesize,
        //                      width, height, pix_fmt, 1);
        if (ret < 0) {
            throw ProcessError("Could not allocate raw video buffer");
        }
        /*Size in bytes required for the image buffer*/
        video_dst_bufsize = ret;
    }

    // Paste stream information on the screen
    av_dump_format(formatContext, 0, input.c_str(), 0);

    // if (!video_stream) {
    //     ret = 1;
    //     throw ProcessError("Could not find video stream in the input, aborting");
    // }
    //
    // /*Allocate an AVFrame and set its fields to default values. The resulting struct must be freed using av_frame_free().*/
    // frame = av_frame_alloc();
    //
    // if (!frame) {
    //     ret = AVERROR(ENOMEM);
    //     throw ProcessError("Could not allocate frame");
    // }
    //
    // /* initialize packet, set data to NULL, let the demuxer fill it */
    // av_init_packet(&pkt);
    // pkt.data = NULL;
    // pkt.size = 0;
    // do {
    //     decode_packet(&got_frame, 1);
    // } while (got_frame);




}
