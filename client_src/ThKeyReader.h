#ifndef __TH_KEY_R__
#define __TH_KEY_R__

#include <ThSender.h>
#include <Protocol.h>

class ThKeyReader{
private:
    ThSender& th_sender;
public:
    explicit ThKeyReader(ThSender& th_sender);
    void run();
    ~ThKeyReader();
};

#endif
