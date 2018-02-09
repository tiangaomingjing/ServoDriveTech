#include "igraphencoder.h"
#include "igraphencoder_p.h"
IGraphEncoderPrivate::IGraphEncoderPrivate():
  m_curEncConfigItem(NULL),
  m_encConfigManage(NULL),
  m_iDataBinding(NULL)
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

IGraphEncoder::IGraphEncoder(IGraphEncoderPrivate &dd, QWidget *parent):IGraph(dd,parent)
{

}
