#include <source.h>

class PNMreader : public Source
{
private:
    char *filename;
public:
    PNMreader(char *);
    ~PNMreader();
    virtual void Update();
    virtual void Execute();
    const char *SourceName() { return "PNMreader"; };
};