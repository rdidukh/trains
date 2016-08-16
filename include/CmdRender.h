#pragma once

class CmdRender : public Render
{
    public:
    virtual void run();
};

void CmdRender::run()
{
    constexpr int fps = 10;

    int sleepUS = 0;
    int frame = 0;
    int sumTime = 0;

    while(usleep(sleepUS) == 0)
    {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        world.update(frame);
        gettimeofday(&end, NULL);

        int duration = (end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;
        sumTime += duration;
        frame++;

        sleepUS = 1000000/fps - duration;

        if(sleepUS < 0)
        {
            std::cerr << "LATE" << std::endl;
            sleepUS = 0;
        }
    }
}
