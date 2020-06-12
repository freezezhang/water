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
	int tm_sec;     /* 秒 – 取值区间为[0,59] */
	int tm_min;     /* 分 - 取值区间为[0,59] */
	int tm_hour;    /* 时 - 取值区间为[0,23] */
	int tm_mday;    /* 一个月中的日期 - 取值区间为[1,31] */
	int tm_mon;     /* 月份（从一月开始，0代表一月） - 取值区间为[0,11] */
	int tm_year;    /* 年份，其值等于实际年份减去1900 */
	int tm_wday;    /* 星期 – 取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推 */
	int tm_yday;    /* 从每年的1月1日开始的天数 – 取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推 */
	int tm_isdst;   /* 夏令时标识符，实行夏令时的时候，tm_isdst为正。不实行夏令时的进候，tm_isdst为0；不了解情况时，tm_isdst()为负。*/
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