#ifndef FILTERS_H
#define FILTERS_H

#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink
{
public:
    const char *SourceName(){ return FilterName(); };
    const char *SinkName() { return FilterName(); };
    virtual const char *FilterName() = 0;
};

class Shrinker : public Filter
{
public:
    virtual const char *FilterName() { return "Shrinker"; };
    virtual void Execute();
    virtual void Update();
};

class TBConcat : public Filter
{
public:
    virtual const char *FilterName() { return "TBConcat"; };
    virtual void Execute();
    virtual void Update();
};

class LRConcat : public Filter
{
public:
    virtual const char *FilterName() { return "LRConcat"; };
    virtual void Execute();
    virtual void Update();
};

class Blender : public Filter
{
private:
    float factor;
public:
    virtual const char *FilterName() { return "Blender"; };
    virtual void Execute();
    virtual void Update();
    void SetFactor(float);
};

class Crop : public Filter
{
public:
    Crop() { Istart = Istop = Jstart = Jstop = -1; };
    virtual const char *FilterName() { return "Crop"; };
    virtual void Execute();
    virtual void Update();
    void SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
    {
        Istart = Istart_;
        Istop  = Istop_;
        Jstart = Jstart_;
        Jstop  = Jstop_;
    }
    
private:
    int Istart, Istop, Jstart, Jstop;
};

class Transpose : public Filter
{
public:
    virtual void Execute();
    virtual void Update();
    virtual const char *FilterName() { return "Transpose"; };
};

class Invert : public Filter
{
public:
    virtual void Execute();
    virtual void Update();
    virtual const char *FilterName() { return "Invert"; };
};
#endif