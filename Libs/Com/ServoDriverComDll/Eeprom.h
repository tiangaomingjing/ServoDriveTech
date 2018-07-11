#pragma once
#include "Basetype_def.h"
#include "ComBase.h"

#define FPGA_NORMAL_EEPROM (0)
#define FPGA_EXT_EEPROM (1)

typedef struct 
{
	Uint8 ctl_read_write			: 1;	//��д����λ��0��д�� 1����
	Uint8 addr_chip					: 3;	//оƬӲ����ַ��6������Ϊ0
	Uint8 enable_RW				: 1;	//��дģ��ʹ��λ��0�������ܣ�1��ʹ�ܣ��Զ����㣩
	Uint8 reset_chip					: 1;	//оƬ��λλ��0������λ��1��ͬʱenable_RW=1ʱоƬ��λ
	Uint8 resd							: 2;	//����
}StEepromCtlBit;
typedef union 
{
	Uint8 all;
	StEepromCtlBit bit;
}StEepromCtl;

class CEeprom
{
public:
	CEeprom();
	~CEeprom();

public:
	CComBase*		m_pCom;
	Uint16			m_des_id;
	Uint16			m_eeprom_id;
private:
	//Eeprom��ַ�궨��byte��ַ
	static const  Uint8  ADDR_CRL = (0x00);
	static const  Uint8  ADDR_WRITE_ADDR = (0x02);
	static const  Uint8 ADDR_WRITE_DATA = (0x04);
	static const  Uint8 ADDR_READ_ADDR = (0x06);
	static const  Uint8 ADDR_STS = (0x08);
	static const  Uint8 ADDR_READ_DATA = (0x0A);
	//�Ȼ���ƫ�Ƶ�ַbyte��ַ
	static const Uint16 FPGA_EEPROM_BASEADDR = (0x0900);
	static const Uint16 FPGA_EEPROM_EXT_BASEADDR = (0x8900);
	// pcdebug ��ַΪdsp��fpga֮��ͨ�ŵ�fpga��ַ����ͬ��dsp��Ӧ��ͬ��fpga��ַ��byte��ַ
	static const Uint16 FPGA_RN_EPR_START_OFST = (0x0900);
	static const Uint16 FPGA_RN_EPR_EXT_START_OFST = (0x8900);

	StEepromCtl m_stEepromClt;
	int16 EepromBaseOptWr(Uint16 eeprom_addr, Uint8 byte_data);
	int16 EepromBaseOptRd(Uint16 eeprom_addr, Uint8* byte_data);
	int16 EepromWrite8bit(Uint16 byte_addr, Uint8 byte_data);
	int16 EepromRead8bit(Uint16 byte_addr, Uint8* byte_data);
public:
	int16 Initial(CComBase* pComBase);
	int16 EepromWrite(Uint16 byte_addr, Uint8* byte_data, Uint16 byte_num);
	int16 EepromRead(Uint16 byte_addr, Uint8* byte_data, Uint16 byte_num);
};
