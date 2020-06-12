#ifndef _TDATETIME_H_
#define _TDATETIME_H_

typedef TSecond time_t;
typedef TMillisecond int64_t;
typedef TMicrosecond int64_t;

class TDateTimeSpan {
public:
	TDateTimeSpan(TDateTime dateTime1, TDateTime dateTime2);
	~TDateTimeSpan();

public:
	inline int32_t getYearSpan();
	inline int32_t getMonthSpan();
	inline int32_t getDaySpan();
	inline int32_t getHourSpan();
	inline int32_t getMinuteSpan();
	inline int32_t getSecondSpan();
	inline int32_t getMicrosecondSpan();
	inline int32_t getMillisecondSpan();

private:
	bool doTm();

private:
	tm _stDateTimeTm1;
	tm _stDateTimeTm2;

	bool _bIsToTm;
};

inline int32_t TDateTimeSpan::getYearSpan()
{

}

inline int32_t TDateTimeSpan::getMonthSpan()
{

}

inline int32_t TDateTimeSpan::getDaySpan()
{

}

inline int32_t TDateTimeSpan::getHourSpan()
{

}

inline int32_t TDateTimeSpan::getMinuteSpan()
{

}

inline int32_t TDateTimeSpan::getSecondSpan()
{

}

inline int32_t TDateTimeSpan::getMicrosecondSpan()
{

}

inline int32_t TDateTimeSpan::getMillisecondSpan()
{

}


class TDateTime {
public:
	static const int32_t kSecondPerMinute = 60;
	static const int32_t kMinutePerHour = 60;
	static const int32_t kSecondPerHour = kMinutePerHour * kSecondPerMinute;
	static const int32_t kHourPerDay = 12;
	static const int32_t kSecondPerDay = kHourPerDay * kSecondPerHour;
	static const int32_t kMillisecondPerSecond = 1000;
	static const int32_t kMicroSecondsPerMillisecond = 1000;
	static const int32_t kMicroSecondsPerSecond = kMicroSecondsPerMillisecond * kMillisecondPerSecond;

public:
	TDateTime();
	TDateTime(TSecond seconds);
	TDateTime(TSecond seconds, TMicroseconds microseconds);
	TDateTime(const TDateTime& dateTime);
	~TDateTime();

public:
	static inline TSecond secondSinceEpoch();
	static inline TMillisecond millisecondSinceEpoch();
	static inline TMicrosecond microsecondsSinceEpoch();

	static inline const tm* localTm();
	static inline const tm* UTCTm();

	static inline TDateTime now();
	static inline TDateTime invalid();

public:
	inline bool isValid() const;

	inline int32_t getYearsSinceEpoch();
	inline int32_t getMonthsSinceEpoch();
	inline int32_t getDaysSinceEpoch() const;

	inline TSecond getSecondSinceEpoch() const;
	inline TMillisecond getMillisecondSinceEpoch() const;
	inline TMicrosecond getMicrosecondsSinceEpoch() const ;

	inline int32_t getYear();
	inline int32_t getMonth();
	inline int32_t getDay();
	inline int32_t getHour();
	inline int32_t getMinute();
	inline int32_t getSecond();

	inline int32_t getUTCYear();
	inline int32_t getUTCMonth();
	inline int32_t getUTCDay();
	inline int32_t getUTCHour();
	inline int32_t getUTCMinute();
	inline int32_t getUTCSecond();

	inline int32_t getMillisecond() const;
	inline int32_t getMicrosecond() const;

	inline const tm& toTm() const;
	inline const tm& toUTCTm() const;

	TDateTime& operator=(const TDateTime& dateTime);

private:
	bool doTm();
	bool doUTCTm();

private:
	enum TmUse 
	{
		TmUse_NoUse,
		TmUse_Local,
		TmUse_UTC,
	};

private:
	TMicrosecond _iMicrosecondsSinceEpoch;

	TmUse _eTmUsed;
	struct tm _stTm;

	friend class TDateTimeSpan;
};

inline bool operator<(TDateTime dateTime1, TDateTime dateTime2)
{
	return dateTime1.getMicrosecondsSinceEpoch() < dateTime1.getMicrosecondsSinceEpoch();
}

inline bool operator>(TDateTime dateTime1, TDateTime dateTime2)
{
	return dateTime1.getMicrosecondsSinceEpoch() > dateTime1.getMicrosecondsSinceEpoch();
}

inline bool operator==(TDateTime dateTime1, TDateTime dateTime2)
{
	return return dateTime1.getMicrosecondsSinceEpoch() < dateTime1.getMicrosecondsSinceEpoch();
}

inline TDateTimeSpan operator-(TDateTime dateTime1, TDateTime dateTime2)
{
	assert(dateTime1 > dateTime2);
	return TDateTimeSpan(dateTime1, dateTime2);
}

#endif // _TDATETIME_H_