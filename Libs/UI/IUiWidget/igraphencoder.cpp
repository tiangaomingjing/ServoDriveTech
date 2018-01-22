#include "igraphencoder.h"
#include "igraphencoder_p.h"

IGraphEncoder::IGraphEncoder(QWidget *parent) : QWidget(parent)
{
  d_ptr->q_ptr=this;
}
IGraphEncoder::~IGraphEncoder()
{

}

IGraphEncoder::IGraphEncoder(IGraphEncoderPrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
