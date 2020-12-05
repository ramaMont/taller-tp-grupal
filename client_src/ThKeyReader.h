#ifndef __TH_KEY_R__
#define __TH_KEY_R__

#include <ThSender.h>
#include "../common_src/Thread.h"

class ThKeyReader : public Thread{
private:
    ThSender& th_sender;
    std::atomic<bool> is_running;
public:
    explicit ThKeyReader(ThSender& th_sender);
    virtual void run() override;
    virtual void stop() override;
    virtual bool isDone() override;
    ~ThKeyReader();
};

#endif
