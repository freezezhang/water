#include "TDateTime.h"

// TDateTimeSpan
TDateTimeSpan::TDateTimeSpan(TDateTime dateTime1, TDateTime dateTime2)
{

}

TDateTimeSpan::~TDateTimeSpan()
{

}

TDateTimeSpan::doTm()
{
	if (!_bIsToTm)
	{
	}

}

// TDateTime
TDateTime::TDateTime() 
	: _iMicrosecondsSinceEpoch(0)
{
}

TDateTime::TDateTime(TSecond seconds) 
	: _iMicrosecondsSinceEpoch(second * kMillisecondPerSecond)
{
}

TDateTime::TDateTime(TSecond seconds, TMicrosecond microsecond)
	: _iMicrosecondsSinceEpoch(second * kMillisecondPerSecond + microsecond)
{
}

TDateTime::TDateTime(const TDateTime& dateTime)
	: _iMicrosecondsSinceEpoch(dateTime.getMicrosecondSinceEpoch())
{
}

TDateTime::~TDateTime()
{
	_iMicrosecondsSinceEpoch = 0;
}

TSecond TDateTime::secondSinceEpoch()
{
	return time(NULL);
}

TMillisecond TDateTime::millisecondSinceEpoch()
{
	timeval stTimeValue;
	if (gettimeofday(&stTimeValue, NULL) != 0)
	{
		return stTimeValue.tv_sec * kMillisecondPerSecond + stTimeValue.tv_usec / kMicroSecondsPerMillisecond;
	}
	return 0;
}

TMicrosecond TDateTime::microsecondsSinceEpoch()
{
	timeval stTimeValue;
	if (gettimeofday(&stTimeValue, NULL) != 0)
	{
		return stTimeValue.tv_sec * kMillisecondPerSecond + stTimeValue.tv_usec;
	}
	return 0;
}

tm* TDateTime::localTm()
{
	return localtime(secondSinceEpoch());
}

tm* TDateTime::UTCTm()
{
	return gmtime(secondSinceEpoch());
}

TDateTime TDateTime::now()
{
	return TDateTime(microsecondsSinceEpoch());
}

TDateTime TDateTime::invalid()
{
	return TDateTime();
}

bool TDateTime::isValid()
{
	return _iMicrosecondSinceepoch > 0;
}

int32_t TDateTime::getYearsSinceEpoch()
{
	doTm();
	return _stTm.m_year - 1970;
}

int32_t TDateTime::getMonthsSinceEpoch()
{
	
}

int32_t TDateTime::getDaysSinceEpoch()
{
	return getSecondSinceEpoch() / kSecondPerDay;
}

TSecond TDateTime::getSecondSinceEpoch()
{
	return getMicrosecondsSinceEpoch() / kMicroSecondsPerSecond;
}

TMillisecond TDateTime::getMillisecondSinceEpoch()
{
	return getMicrosecondsSinceEpoch() / kMicroSecondsPerMillisecond;
}

TMicrosecond TDateTime::getMicrosecondsSinceEpoch()
{
	return _iMicrosecondSinceEpoch;
}

inline int32_t TDateTime::getYear()
{
	if (doTm())
	{
		return _stTm.m_year;
	}
	return -1;
}

inline int32_t TDateTime::getMonth()
{
	if (doTm())
	{
		return _stTm.m_year;
	}
	return -1;
}

struct tm {
	int tm_sec;     /* �� �C ȡֵ����Ϊ[0,59] */
	int tm_min;     /* �� - ȡֵ����Ϊ[0,59] */
	int tm_hour;    /* ʱ - ȡֵ����Ϊ[0,23] */
	int tm_mday;    /* һ�����е����� - ȡֵ����Ϊ[1,31] */
	int tm_mon;     /* �·ݣ���һ�¿�ʼ��0����һ�£� - ȡֵ����Ϊ[0,11] */
	int tm_year;    /* ��ݣ���ֵ����ʵ����ݼ�ȥ1900 */
	int tm_wday;    /* ���� �C ȡֵ����Ϊ[0,6]������0���������죬1��������һ���Դ����� */
	int tm_yday;    /* ��ÿ���1��1�տ�ʼ������ �C ȡֵ����Ϊ[0,365]������0����1��1�գ�1����1��2�գ��Դ����� */
	int tm_isdst;   /* ����ʱ��ʶ����ʵ������ʱ��ʱ��tm_isdstΪ������ʵ������ʱ�Ľ���tm_isdstΪ0�����˽����ʱ��tm_isdst()Ϊ����*/
};

inline int32_t TDateTime::getDay()
{
}
inline int32_t TDateTime::getHour()
{
}
inline int32_t TDateTime::getMinute()
{
}
inline int32_t TDateTime::getSecond()
{
	
}

inline int32_t TDateTime::getUTCYear()
{

}
inline int32_t TDateTime::getUTCMonth()
{
}
inline int32_t TDateTime::getUTCDay()
{
}
inline int32_t TDateTime::getUTCHour()
{
}
inline int32_t TDateTime::getUTCMinute()
{
}
inline int32_t TDateTime::getUTCSecond()
{
}

inline int32_t TDateTime::getMillisecond()
{
}

inline int32_t TDateTime::getMicrosecond()
{
}

inline const tm& TDateTime::toTm()
{
}
inline const tm& TDateTime::toUTCTm()
{
	
}

TDateTime& TDateTime::operator=(const TDateTime& dateTime)
{
}

bool TDateTime::doTm()
{
	tm* pTm = localtime(getSecondSinceEpoch());
	if (stTm != NULL)
	{
		_eTmUsed = TmUse_Local;
		memcpy(&_stTm, pTm, sizeof(_stTm));
		return true;
	}
	return false;
}

bool TDateTime::doUTCTm()
{
	tm* pTm = gmtime(getSecondSinceEpoch());
	if (stTm != NULL)
	{
		_eTmUsed = TmUse_UTC;
		memcpy(&_stTm, pTm, sizeof(_stTm));
		return true;
	}
	return false;
}