#include <sink.h>

class PNMwriter : public Sink
{
public:
    PNMwriter();
    ~PNMwriter();
    void Write(char *);
    const char *SinkName() { return "PNMwriter"; };
};