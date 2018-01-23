#include "igraphencoder.h"
#include "igraphencoder_p.h"
IGraphEncoderPrivate::IGraphEncoderPrivate()
{

}

IGraphEncoderPrivate::~IGraphEncoderPrivate()
{

}

IGraphEncoder::IGraphEncoder(QWidget *parent) :IGraph(*(new IGraphEncoderPrivate),parent)
{

}
IGraphEncoder::~IGraphEncoder()
{

}

IGraphEncoder::IGraphEncoder(IGraphEncoderPrivate &d, QWidget *parent):IGraph(d,parent)
{

}
