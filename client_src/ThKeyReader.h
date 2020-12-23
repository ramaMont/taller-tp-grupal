#ifndef __TH_KEY_R__
#define __TH_KEY_R__

#include <ThSender.h>
#include <Thread.h>

class ThKeyReader : public Thread{
private:
    ThSender& th_sender;
public:
    explicit ThKeyReader(ThSender& th_sender);
    virtual void run() override;
    virtual void stop() override;
    ~ThKeyReader();
};

#endif
