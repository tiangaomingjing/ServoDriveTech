#include "rnnet.h"
#include "rnnet_p.h"
#include "ServoDriverComDll.h"
#include "comglobal.h"
#include <QDebug>

COM_USE_NAMESPACE

RnNetPrivate::RnNetPrivate():IComPrivate()
{

}
RnNetPrivate::~RnNetPrivate()
{

}

RnNet::RnNet(const string &objectName):ICom(*new RnNetPrivate())
{
  Q_D(RnNet);
  d->m_objectName=objectName;
  d->m_comType=ICOM_TYPE_RNNET;
  d->m_rnStation=0xf0;
//  printf("net object name =%s\n",objectName.c_str());
}
RnNet::~RnNet()
{

}

errcode_t RnNet::setServoEnable(uint8_t axis, bool on)
{
    Q_D(RnNet);

    int16_t ret=-1;
    if(on)
      ret=GTSD_CMD_SetServoOn(axis,d->m_comType,d->m_rnStation);
    else
      ret=GTSD_CMD_SetServoOff(axis,d->m_comType, d->m_rnStation);
    return ret;
}

errcode_t RnNet::getUcRef(uint8_t axis, double &value)
{
    Q_D(RnNet);

    UC_STATE uc;
    int16_t ret=GTSD_CMD_GetUcRef(axis,&uc,d->m_comType,d->m_rnStation);
    value=uc.cur_uc;
    return ret;
}

errcode_t RnNet::setPosAdjRef(uint8_t axis, double posAdjRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetPosAdjRef(axis,posAdjRef,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::getPosAdjRef(uint8_t axis, double &value)
{
    Q_D(RnNet);

    POS_ADJ_STATE pos;
    int16_t ret=GTSD_CMD_GetPosAdjRef(axis,&pos,d->m_comType,d->m_rnStation);
    value=pos.rsv_pos_in;
    return ret;
}

errcode_t RnNet::setPosRef(uint8_t axis, double posRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetPosRef(axis,int32(posRef),d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::sendGeneralCmd(uint8_t axis, GeneralPDU &pdu)
{
    Q_D(RnNet);

    GENERALFUNCTION func;
    errno_t err;
    int16_t buf[16]={0};
    //王彬data[0],data[1],data[2]存放协议的东西

    /**填王彬结构体，然后调用它的指令下发
     *
     * cmd 是指其指令号
     * GENERALFUNCTION 中的data[]数组长度为:length
     * data[0],data[1]不用填，他下面已经写了
     * data[3]当xml表中的id不为-1时，data[3]=id
     * GTSD_CMD_ProcessorGeneralFunc(axisIndex,&func,comtype)中func写下去，再由下面修改，其返回结果在func中
     * 返回结果从getIndex位开始获得
     * 读命令返回的最终结果要/kgain,如果是设置写命令要*kgain
    */
    if(pdu.subId>0)//有二级ID
    {
      buf[3]=pdu.subId;
      err=memcpy_s(&buf[4],sizeof(buf)*sizeof(int16_t),pdu.data,pdu.length*sizeof(int16_t));
      if(err)
      {
        printf("Error executing memcpy_s.\n");
        return err;
      }
      func.dataLenth=pdu.length+1+3;
    }
    else
    {
      err=memcpy_s(&buf[3],sizeof(buf)*sizeof(int16_t),pdu.data,pdu.length*sizeof(int16_t));
      if(err)
      {
        printf("Error executing memcpy_s.\n");
        return err;
      }
      func.dataLenth=pdu.length+3;
    }
    func.cmd=pdu.cmd;
    func.mode=pdu.mode;

    func.data=buf;
    int16_t ret=GTSD_CMD_ProcessorGeneralFunc(axis, &func, d->m_comType, d->m_rnStation);
    if(ret!=0)
    {
      ret=GTSD_CMD_ProcessorGeneralFunc(axis, &func, d->m_comType, d->m_rnStation);
      if(ret!=0)
        return ret;
    }
    if(pdu.mode==GENERAL_PDU_READ)//1:为读    0：写
    {
      if(pdu.subId>0)
      {
        memcpy_s(pdu.data,sizeof(pdu.data)*sizeof(int16_t),&buf[1],pdu.length*sizeof(int16_t));
      }
      else
      {
        memcpy_s(pdu.data,sizeof(pdu.data)*sizeof(int16_t),&buf[0],pdu.length*sizeof(int16_t));
      }
    }

    return ret;
}

errcode_t RnNet::readDSPVersion(uint8_t dspInx, uint16_t &version)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_ReadProcessorVersion(dspInx*2,version,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readFPGAVersion(uint8_t fpgaInx, uint16_t &version)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_ReadFirmwareVersion(fpgaInx,version,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readFPGAYearDay(uint8_t fpgaInx, uint16_t &year, uint16_t &day)
{
    Q_D(RnNet);

    VERSION v;
    int16_t ret=GTSD_CMD_ReadFpgaVersion(fpgaInx,&v,d->m_comType,d->m_rnStation);
    year=v.usYear;
    day=v.usMonthDay;
    return ret;
}

errcode_t RnNet::hex2LdrFormat(const wstring &hexFile, const wstring &ldrFile)
{
    Q_D(RnNet);

    wstring hex=hexFile;
    wstring ldr=ldrFile;
    int16_t ret=GTSD_CMD_Hex2Ldr(hex,ldr,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::uartBootHandler(uint8_t dspInx, const wstring &filePath, int32_t baudRate, int16_t cmd, const string &inputKey, void (*processCallBack)(void *, short *), void *prm)
{
    Q_D(RnNet);

    wstring file=filePath;
    string key=inputKey;
    int16_t ret=GTSD_CMD_ProcessorUartBootHandler(dspInx*2,file,\
                                                  baudRate,cmd,key,\
                                                  processCallBack,prm,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::resetDSP(uint8_t dspInx)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_ResetSystem(dspInx*2,d->m_comType,d->m_rnStation);
    return ret;
}

bool RnNet::checkResetFinish(uint8_t dspInx, errcode_t &errCode)
{
    Q_D(RnNet);

    bool finish=false;
    int16_t ret=GTSD_CMD_CheckResetFinish(dspInx*2,finish,d->m_comType,d->m_rnStation);
    errCode=ret;
    return finish;
}

errcode_t RnNet::downLoadDSPFLASH(uint8_t dspInx, const wstring &fileName, void (*processCallBack)(void *, short *), void *parameters)
{
    Q_D(RnNet);

    wstring file=fileName;
    int16_t ret=GTSD_CMD_ProcessorFlashHandler(dspInx*2,file,processCallBack,parameters,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::downLoadFPGAFLASH(uint8_t fpgaInx, const wstring &fileName, void (*processCallBack)(void *, short *), void *parameters)
{
    Q_D(RnNet);

    wstring file=fileName;
    int16_t ret=GTSD_CMD_FirmwareFlashHandler(fpgaInx,file,processCallBack,parameters,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readEEPROM(uint16_t ofst, uint8_t *value, uint16_t num, uint8_t cs)
{
    Q_D(RnNet);

    int16_t ret=-1;
    EEPROMSelect select=EEPROMSelect(cs);
    switch (select)
    {
    case EEPROM_CS_CONTROL:
      ret=GTSD_CMD_ReadEEPROM(0,ofst,value,num,d->m_comType,d->m_rnStation);
      break;
    case EEPROM_CS_POWER:
      ret=GTSD_CMD_ReadEEPROMExt(0,ofst,value,num,d->m_comType,d->m_rnStation);
      break;
    default:
      ret=GTSD_CMD_ReadEEPROM(0,ofst,value,num,d->m_comType,d->m_rnStation);
      break;
    }

    return ret;
}

errcode_t RnNet::writeEEPROM(uint16_t ofst, const uint8_t *value, uint16_t num, uint8_t cs)
{
    Q_D(RnNet);

    int16_t ret=-1;
    EEPROMSelect select=EEPROMSelect(cs);
    uint8_t* ptr=new uint8_t[num];
    memcpy_s(ptr,num,value,num);
    switch (select)
    {
    case EEPROM_CS_CONTROL:
      ret=GTSD_CMD_WriteEEPROM(0,ofst,ptr,num,d->m_comType,d->m_rnStation);
      break;
    case EEPROM_CS_POWER:
      ret=GTSD_CMD_WriteEEPROMExt(0,ofst,ptr,num,d->m_comType,d->m_rnStation);
      break;
    default:
      ret=GTSD_CMD_WriteEEPROM(0,ofst,ptr,num,d->m_comType,d->m_rnStation);
      break;
    }

    delete ptr;
    return ret;
}

errcode_t RnNet::startPlot(const PlotControlPrm &ctrPrm)
{
    Q_D(RnNet);
    int16_t ret=-1;
    WAVE_BUF_PRM bufPrm;
    bufPrm.cmd.bit.ENP=1;
    bufPrm.cmd.bit.TIM=ctrPrm.samplingScale;
    bufPrm.cmd.bit.NUM=ctrPrm.number;
    if(ctrPrm.number>ctrPrm.curveInfo.size())
      return COM_ERR_RANGE;
    PlotCurveInfoConstIterator cIt=ctrPrm.curveInfo.cbegin();
    int i=0;
    for(;cIt!=ctrPrm.curveInfo.cend();cIt++)
    {
      bufPrm.inf[i].base=(*cIt).base;
      bufPrm.inf[i].bytes=(*cIt).bytes;
      bufPrm.inf[i].ofst=(*cIt).ofst;
      i++;
    }

    int16_t axis=ctrPrm.dspIndex*2;
    ret=GTSD_CMD_StartPlot(axis,bufPrm,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::stopPlot(const PlotControlPrm &ctrPrm)
{
    Q_D(RnNet);
    int16_t ret=-1;
    WAVE_BUF_PRM bufPrm;
    bufPrm.cmd.bit.ENP=0;
    bufPrm.cmd.bit.TIM=ctrPrm.samplingScale;
    bufPrm.cmd.bit.NUM=ctrPrm.number;

    if(ctrPrm.number>ctrPrm.curveInfo.size())
      return COM_ERR_RANGE;
    PlotCurveInfoConstIterator cIt=ctrPrm.curveInfo.cbegin();
    int i=0;
    for(;cIt!=ctrPrm.curveInfo.cend();cIt++)
    {
      bufPrm.inf[i].base=(*cIt).base;
      bufPrm.inf[i].bytes=(*cIt).bytes;
      bufPrm.inf[i].ofst=(*cIt).ofst;
      i++;
    }

    int16_t axis=ctrPrm.dspIndex*2;
    ret=GTSD_CMD_StopPlot(axis,bufPrm,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::getPlotData(const PlotControlPrm &ctrPrm, CurveList &curveList)
{
    Q_D(RnNet);
    errcode_t ret=-1;
    int16_t axis=ctrPrm.dspIndex*2;
    int32_t retNumber;
    double *ptr;

    curveList.clear();
    ret=GTSD_CMD_PcGetWaveData(axis, &ptr, retNumber,d->m_comType,d->m_rnStation);

    if(ret!=0)
      return ret;

    if(retNumber>0)
    {
      for(int row=0;row<ctrPrm.number;row++)
      {
        CurveDatas curveDatas;
        double value;
        for(int col=0;col<retNumber;col++)
        {
          value=*(ptr+row*PLOT_ARRAY_COLUMN_SIZE+col);
          curveDatas.push_back(value);
        }
        curveList.push_back(curveDatas);
      }
    }
    return ret;
}

errcode_t RnNet::writeRAM16(uint8_t axis, uint16_t ofst, uint8_t page, int16_t value)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_Write16BitByAdr(axis,ofst,value,&page,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readRAM16(uint8_t axis, uint16_t ofst, uint8_t page, int16_t &value)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_Read16BitByAdr(axis,ofst,&value,&page,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::writeRAM32(uint8_t axis, uint16_t ofst, uint8_t page, int32_t value)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_Write32BitByAdr(axis,ofst,value,&page,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readRAM32(uint8_t axis, uint16_t ofst, uint8_t page, int32_t &value)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_Read32BitByAdr(axis,ofst,&value,&page,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::writeRAM64(uint8_t axis, uint16_t ofst, uint8_t page, int64_t value)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_Write64BitByAdr(axis,ofst,value,&page,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readRAM64(uint8_t axis, uint16_t ofst, uint8_t page, int64_t &value)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_Read64BitByAdr(axis,ofst,&value,&page,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::writeFLASH16(uint8_t axis, uint16_t ofst, uint8_t page, int16_t value)
{
    Q_D(RnNet);

    UN_USED(page);
    int16_t ret=GTSD_CMD_Fram_Write16BitByAdr(axis,ofst,value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readFLASH16(uint8_t axis, uint16_t ofst, uint8_t page, int16_t &value)
{
    Q_D(RnNet);

    UN_USED(page);
    int16_t ret=GTSD_CMD_Fram_Read16BitByAdr(axis,ofst,&value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::writeFLASH32(uint8_t axis, uint16_t ofst, uint8_t page, int32_t value)
{
    Q_D(RnNet);

    UN_USED(page);
    int16_t ret=GTSD_CMD_Fram_Write32BitByAdr(axis,ofst,value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readFLASH32(uint8_t axis, uint16_t ofst, uint8_t page, int32_t &value)
{
    Q_D(RnNet);

    UN_USED(page);
    int16_t ret=GTSD_CMD_Fram_Read32BitByAdr(axis,ofst,&value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::writeFLASH64(uint8_t axis, uint16_t ofst, uint8_t page, int64_t value)
{
    Q_D(RnNet);

    UN_USED(page);
    int16_t ret=GTSD_CMD_Fram_Write64BitByAdr(axis,ofst,value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readFLASH64(uint8_t axis, uint16_t ofst, uint8_t page, int64_t &value)
{
    Q_D(RnNet);

    UN_USED(page);
    int16_t ret=GTSD_CMD_Fram_Read64BitByAdr(axis,ofst,&value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readFPGAReg16(uint8_t fpgaInx, uint16_t address, int16_t &value, uint16_t base)
{
    Q_D(RnNet);

    UN_USED(base);
    int16_t ret=GTSD_CMD_Get16bitFPGAByAddr(fpgaInx,address,&value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::writeFPGAReg16(uint8_t fpgaInx, uint16_t address, int16_t value, uint16_t base)
{
    Q_D(RnNet);

    UN_USED(base);
    int16_t ret=GTSD_CMD_Set16bitFPGAByAddr(fpgaInx,address,value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readFPGAReg32(uint8_t fpgaInx, uint16_t address, int32_t &value, uint16_t base)
{
    Q_D(RnNet);

    UN_USED(base);
    int16_t ret=GTSD_CMD_Get32bitFPGAByAddr(fpgaInx,address,&value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::writeFPGAReg32(uint8_t fpgaInx, uint16_t address, int32_t value, uint16_t base)
{
    Q_D(RnNet);

    UN_USED(base);
    int16_t ret=GTSD_CMD_Set32bitFPGAByAddr(fpgaInx,address,value,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::readFPGAReg64(uint8_t fpgaInx, uint16_t address, int64_t &value, uint16_t base)
{
    UN_USED(fpgaInx);
    UN_USED(address);
    UN_USED(value);
    UN_USED(base);
    return -1;
}

errcode_t RnNet::writeFPGAReg64(uint8_t fpgaInx, uint16_t address, int64_t value, uint16_t base)
{
    UN_USED(fpgaInx);
    UN_USED(address);
    UN_USED(value);
    UN_USED(base);
    return -1;
}

errcode_t RnNet::writeXML(uint8_t axis, char *pFileNameList[], int pFileTypeList[], int file_num, void (*processCallBack)(void *, short *), void *ptrv, short &progress)
{
    Q_D(RnNet);
    short ret = GTSD_CMD_XmlWriteFile(axis, pFileNameList, pFileTypeList, file_num, processCallBack, ptrv, progress, d->m_comType, d->m_rnStation);
    return ret;
}

errcode_t RnNet::readXML(uint8_t axis, char *pFileNameList[], int pFileTypeList[], int file_num, void (*processCallBack)(void *, short *), void *ptrv, short &progress)
{
    Q_D(RnNet);
    short ret = GTSD_CMD_XmlReadFile(axis, pFileNameList, pFileTypeList, file_num, processCallBack, ptrv, progress, d->m_comType, d->m_rnStation);
    return ret;
}

errcode_t RnNet::setUcRef(uint8_t axis, double ucRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetUcRef(axis,ucRef,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::getUbRef(uint8_t axis, double &value)
{
    Q_D(RnNet);

    UB_STATE ub;
    int16_t ret=GTSD_CMD_GetUbRef(axis,&ub,d->m_comType,d->m_rnStation);
    value=ub.cur_ub;
    return ret;
}

errcode_t RnNet::setUbRef(uint8_t axis, double ubRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetUbRef(axis,ubRef,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::getUaRef(uint8_t axis, double &value)
{
    Q_D(RnNet);

    UA_STATE ua;
    int16_t ret=GTSD_CMD_GetUaRef(axis,&ua,d->m_comType,d->m_rnStation);
    value=ua.cur_ua;
    return ret;
}

errcode_t RnNet::setUaRef(uint8_t axis, double uaRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetUaRef(axis,uaRef,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::getUqRef(uint8_t axis, double &value)
{
    Q_D(RnNet);

    UQ_STATE uq;
    int16_t ret=GTSD_CMD_GetUqRef(axis,&uq,d->m_comType,d->m_rnStation);
    value=uq.cur_uq;
    return ret;
}

errcode_t RnNet::setUqRef(uint8_t axis, double uqRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetUqRef(axis,uqRef,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::getUdRef(uint8_t axis, double &value)
{
    Q_D(RnNet);

    UD_STATE udState;
    int16_t ret=GTSD_CMD_GetUdRef(axis,&udState,d->m_comType,d->m_rnStation);
    value=udState.cur_ud;
    return ret;
}

errcode_t RnNet::setUdRef(uint8_t axis, double udRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetUdRef(axis,udRef,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::getSpdRef(uint8_t axis, double &value)
{
    Q_D(RnNet);

    SPD_STATE spdState;
    int16_t ret=GTSD_CMD_GetSpdRef(axis,&spdState,d->m_comType,d->m_rnStation);
    value=spdState.ctl_spd_ref;
    return ret;
}

errcode_t RnNet::getSpdFb(uint8_t axis, double &value)
{
  Q_D(RnNet);

  SPD_STATE spdState;
  int16_t ret=GTSD_CMD_GetSpdRef(axis,&spdState,d->m_comType,d->m_rnStation);
  value=spdState.rsv_mot_spd;
  return ret;
}

errcode_t RnNet::setSpdRef(uint8_t axis, double spdRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetSpdRef(axis,spdRef,d->m_comType, d->m_rnStation);
    return ret;
}

errcode_t RnNet::getIqRef(uint8_t axis, double &value)
{
    Q_D(RnNet);

    IQ_STATE iqState;
    int16_t ret=GTSD_CMD_GetIqRef(axis,&iqState,d->m_comType,d->m_rnStation);
    value=iqState.ctl_iq_ref;
    return ret;
}

errcode_t RnNet::setIqRef(uint8_t axis, double iqRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetIqRef(axis,iqRef,d->m_comType,d->m_rnStation);
    return ret;
}

errcode_t RnNet::getIdRef(uint8_t axis, double &value)
{
    Q_D(RnNet);

    ID_STATE idState;
    int16_t ret=GTSD_CMD_GetIdRef(axis,&idState,d->m_comType,d->m_rnStation);
    value=idState.ctl_id_ref;
    return ret;
}

errcode_t RnNet::setIdRef(uint8_t axis, double idRef)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetIdRef(axis, idRef, d->m_comType, d->m_rnStation);
    return ret;
}

errcode_t RnNet::clearAlarm(uint8_t axis)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_ClrAlarm(axis,d->m_comType,d->m_rnStation);
    return ret;
}

int16_t RnNet::currentServoTaskMode(uint8_t axis, errcode_t &errcode)
{
    Q_D(RnNet);
    SERVO_MODE mode;
    int16_t ret=-1;
    ret=GTSD_CMD_GetServoTaskMode(axis,&mode,d->m_comType, d->m_rnStation);
    errcode=ret;

    return int16_t(mode.usr_mode);
}

errcode_t RnNet::setServoTaskMode(uint8_t axis, int16_t mode)
{
    Q_D(RnNet);

    int16_t ret=GTSD_CMD_SetServoTaskMode(axis,mode ,d->m_comType, d->m_rnStation);
    return ret;
}

errcode_t RnNet::checkServoIsEnable(uint8_t axis, bool &enable)
{
    Q_D(RnNet);

    int16_t ret=-1;
    SERVO_STATE state;
    ret=GTSD_CMD_GetServoState(axis,&state,d->m_comType, d->m_rnStation);
    if(state.serv_ready!=0)
      enable=true;
    else
      enable=false;
    return ret;
}

errcode_t RnNet::setRnStation(uint16_t rnstation)
{
  Q_D(RnNet);
  d->m_rnStation=rnstation;
  return 0;
}

uint16_t RnNet::currentRnStation() const
{
  Q_D(const RnNet);
  return d->m_rnStation;
}
std::vector<int16_t> RnNet::broadcast()
{
//  std::vector<uint8_t> vtr;
//  vtr.push_back(0xf0);
////  vtr.push_back(0xf1);//测试得到多个站信息
//  return vtr;

  Q_D(RnNet);
  std::vector<qint16> v;
  v.clear();
  qint16 ret=GTSD_CMD_GetStationIdList(v, d->m_comType);
//  qDebug()<<"GTSD_CMD_GetStationIdList ret="<<ret;
  if(ret!=0)
    v.clear();
  return v;
}

int16_t RnNet::getCurrentAxisNumByReadFPGA()
{
    Q_D(RnNet);
    int16_t num = -1;
    GTSD_CMD_GetStationAxisNum(&num, d->m_comType, d->m_rnStation);
    return num;
}


